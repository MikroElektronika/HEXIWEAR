/*******************************************************************************
* Title                 :   System Initialization
* Filename              :   sys_init.c
* Author                :   RBL
* Origin Date           :   04/23/2012
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description
*  20/02/16           .1         RBL      Module Created.
*
*******************************************************************************/
/** @file P2P_NDEF.c
 *  @brief This module contains the
 */
/******************************************************************************
* Includes
*******************************************************************************/
#ifdef P2P_SUPPORT
#include <string.h>
#include <stddef.h>
#include "P2P_NDEF.h"
#include "nfc_hal.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
/* Well-known LLCP SAP Values */
#define SAP_SDP         1
#define SAP_SNEP        4

/* SNEP codes */
#define SNEP_VER10      0x10
#define SNEP_PUT        0x2
#define SNEP_SUCCESS    0x81

/* LLCP PDU Types */
#define SYMM            0x0
#define PAX             0x1
#define AGF             0x2
#define UI              0x3
#define CONNECT         0x4
#define DISC            0x5
#define CC              0x6
#define DM              0x7
#define FRMR            0x8
#define SNL             0x9
#define reservedA       0xA
#define reservedB       0xB
#define I               0xC
#define RR              0xD
#define RNR             0xE
#define reservedF       0xF

/* Defines the number of symmetry exchanges is expected before initiating the NDEF push (to allow a remote phone to beam an NDEF message first) */
#define NDEF_PUSH_DELAY_COUNT   1

/* Defines at which frequency the symmetry is exchange (in ms) */
#define SYMM_FREQ   500

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/
typedef enum
{
    IDLE_STATE,
    INITIAL,
    DELAYING_PUSH,
    INITIATE_PUSH,
    SNEP_CLIENT_CONNECTING,
    SNEP_CLIENT_CONNECTED,
    NDEF_MSG_SENT
} p2p_snep_client_state_t;

typedef struct
{
    uint8_t dsap;
    uint8_t pdu;
    uint8_t ssap;
} p2p_ndef_llcp_header_t;

typedef void p2p_ndef_callback_t ( uint8_t *, uint16_t );

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static const uint8_t SNEP_PUT_SUCCESS[] = {SNEP_VER10, SNEP_SUCCESS, 0x00, 0x00, 0x00, 0x00};
static const uint8_t LLCP_CONNECT_SNEP[] = {0x11, 0x20};
static const uint8_t LLCP_I_SNEP_PUT_HEADER[] = {SNEP_VER10, SNEP_PUT, 0x00, 0x00, 0x00, 0x00};
static const uint8_t LLCP_SYMM[] = {0x00, 0x00};

static uint8_t *p_ndef_record;
static uint16_t ndef_record_size = 0;

static p2p_snep_client_state_t e_p2p_snep_client_state = INITIAL;
static p2p_ndef_callback_t *p_p2p_ndef_push_cb = NULL;
static p2p_ndef_callback_t *p_p2p_ndef_pull_cb = NULL;
static uint16_t p2p_snep_client_delay_count = NDEF_PUSH_DELAY_COUNT;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void parse_llcp( uint8_t *p_buf,
                        p2p_ndef_llcp_header_t *p_llcp_header );

static void fill_llcp( p2p_ndef_llcp_header_t llcp_header, uint8_t *p_buf );

/******************************************************************************
* Function Definitions
*******************************************************************************/
static void parse_llcp( uint8_t *p_buf,
                        p2p_ndef_llcp_header_t *p_llcp_header )
{
    p_llcp_header->dsap = p_buf[0] >> 2;
    p_llcp_header->pdu = ( ( p_buf[0] & 3 ) << 2 ) + ( p_buf[1] >> 6 );
    p_llcp_header->ssap = p_buf[1] & 0x3F;
}

static void fill_llcp( p2p_ndef_llcp_header_t llcp_header, uint8_t *p_buf )
{
    p_buf[0] = ( llcp_header.ssap << 2 ) + ( ( llcp_header.pdu >> 2 ) & 3 );
    p_buf[1] = ( llcp_header.pdu << 6 ) + llcp_header.dsap;
}

bool p2p_ndef_set_record( uint8_t *p_record,
                          uint16_t record_size, void *cb )
{
    if ( record_size <= P2P_NDEF_MAX_NDEF_RECORD_SIZE )
    {
        p_ndef_record = p_record;
        ndef_record_size = record_size;
        p_p2p_ndef_push_cb = ( p2p_ndef_callback_t * ) cb;
        return true;
    }
    else
    {
        ndef_record_size = 0;
        p_p2p_ndef_push_cb = NULL;
        return false;
    }
}

void p2p_ndef_register_pull_callback( void *p_cb )
{
    p_p2p_ndef_pull_cb = ( p2p_ndef_callback_t * ) p_cb;
}

void p2p_ndef_reset( void )
{
    if ( ndef_record_size != 0 )
        e_p2p_snep_client_state = INITIAL;
    else
        e_p2p_snep_client_state = IDLE_STATE;
}

void p2p_ndef_next( uint8_t *p_cmd, uint16_t cmd_size,
                    uint8_t *p_rsp, uint16_t *p_rsp_size )
{
    p2p_ndef_llcp_header_t llcp_header;

    /* Initialize answer */
    *p_rsp_size = 0;

    parse_llcp( p_cmd, &llcp_header );

    switch ( llcp_header.pdu )
    {
    case CONNECT:
        /* Is connection from SNEP Client ? */
        if ( llcp_header.dsap == SAP_SNEP )
        {
            /* Only accept the connection is application is registered for NDEF reception */
            if( p_p2p_ndef_pull_cb != NULL )
            {
                llcp_header.pdu = CC;
                fill_llcp( llcp_header, p_rsp );
                *p_rsp_size = 2;
            }
        } else {
            /* Refuse any other connection request */
            llcp_header.pdu = DM;
            fill_llcp( llcp_header, p_rsp );
            *p_rsp_size = 2;
        }
        break;
    case I:
        /* Is SNEP PUT ? */
        if ( ( p_cmd[3] == SNEP_VER10 ) && ( p_cmd[4] == SNEP_PUT ) )
        {
            /* Notify application of the NDEF reception */
            if( p_p2p_ndef_pull_cb != NULL ) p_p2p_ndef_pull_cb( &p_cmd[9], p_cmd[8] );

            /* Acknowledge the PUT request */
            llcp_header.pdu = I;
            fill_llcp( llcp_header, p_rsp );
            p_rsp[2] = ( p_cmd[2] >> 4 ) + 1; // N(R)
            memcpy( &p_rsp[3], ( uint8_t * )SNEP_PUT_SUCCESS, sizeof( SNEP_PUT_SUCCESS ) );
            *p_rsp_size = 9;
        }
        break;
    case CC:
        /* Connection to remote SNEP server completed, send NDEF record inside SNEP PUT request */
        e_p2p_snep_client_state = SNEP_CLIENT_CONNECTED;
        break;
    default:
        break;

    }

    /* No anwsers was set */
    if( *p_rsp_size == 0 )
    {
        switch( e_p2p_snep_client_state )
        {
        case INITIATE_PUSH:
            memcpy( p_rsp, ( uint8_t * )LLCP_CONNECT_SNEP, sizeof( LLCP_CONNECT_SNEP ) );
            *p_rsp_size = sizeof( LLCP_CONNECT_SNEP );
            e_p2p_snep_client_state = SNEP_CLIENT_CONNECTING;
            break;

        case SNEP_CLIENT_CONNECTED:
            llcp_header.pdu = I;
            fill_llcp( llcp_header, p_rsp );
            p_rsp[2] = 0; // N(R)
            p_rsp[3] = SNEP_VER10;
            p_rsp[4] = SNEP_PUT;
            p_rsp[5] = 0;
            p_rsp[6] = 0;
            p_rsp[7] = 0;
            p_rsp[8] = ndef_record_size;
            memcpy( &p_rsp[9], p_ndef_record, ndef_record_size );
            *p_rsp_size = 9 + ndef_record_size;
            e_p2p_snep_client_state = NDEF_MSG_SENT;
            /* Notify application of the NDEF push */
            if( p_p2p_ndef_push_cb != NULL ) 
                p_p2p_ndef_push_cb( p_ndef_record,
                                    ndef_record_size );
            break;
        case DELAYING_PUSH:
            p2p_snep_client_delay_count++;
            if( p2p_snep_client_delay_count == NDEF_PUSH_DELAY_COUNT )
                e_p2p_snep_client_state = INITIATE_PUSH;
            /* send a SYMM */
            nfc_hal_delay( 1000 );
            memcpy( p_rsp, ( uint8_t * )LLCP_SYMM, sizeof( LLCP_SYMM ) );
            *p_rsp_size = sizeof( LLCP_SYMM );
            break;

        case INITIAL:
            p2p_snep_client_delay_count = 0;
            e_p2p_snep_client_state = DELAYING_PUSH;
        default:
            /* send a SYMM */
            nfc_hal_delay ( SYMM_FREQ );
            memcpy( p_rsp, ( uint8_t * )LLCP_SYMM, sizeof( LLCP_SYMM ) );
            *p_rsp_size = sizeof( LLCP_SYMM );
            break;
        }
    }
}
#endif

/*************** END OF FUNCTIONS ***************************************************************************/
