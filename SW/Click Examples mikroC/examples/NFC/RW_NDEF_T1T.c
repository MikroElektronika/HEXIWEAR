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
/** @file RW_NDEF_T1T.c
 *  @brief This module contains the
 */
/******************************************************************************
* Includes
*******************************************************************************/
#ifdef RW_SUPPORT
#include <string.h>
#include <stddef.h>
#include "RW_NDEF.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define T1T_MAGIC_NUMBER    0xE1
#define T1T_NDEF_TLV        0x03

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/
typedef enum
{
    INITIAL,
    GETTING_ID,
    READING_CARD_CONTENT,
    READING_NDEF
} rw_ndef_t1t_state_t;

typedef struct
{
    uint8_t hr0;
    uint8_t hr1;
    uint8_t uid[4];
    uint8_t blk_nb;
    uint16_t record_ptr;
    uint16_t record_size;
    uint8_t *p_record;
} rw_ndef_t1t_ndef_t;

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static const uint8_t T1T_RID[]   = {0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t T1T_RALL[]  = {0x00, 0x00, 0x00};
static const uint8_t T1T_READ8[] =
{
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static rw_ndef_t1t_state_t e_rw_ndef_t1t_state = INITIAL;
static rw_ndef_t1t_ndef_t rw_ndef_t1t_ndef;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void rw_ndef_t1t_reset( void )
{
    e_rw_ndef_t1t_state = INITIAL;
    rw_ndef_t1t_ndef.p_record = ndef_buffer;
}

void rw_ndef_t1t_read_next( uint8_t *p_cmd, uint16_t cmd_size,
                            uint8_t *rsp, uint16_t *p_rsp_size )
{
    /* By default no further command to be sent */
    *p_rsp_size = 0;

    switch( e_rw_ndef_t1t_state )
    {
    case INITIAL:
        /* Send T1T_RID */
        memcpy( rsp, ( uint8_t * )T1T_RID, sizeof( T1T_RID ) );
        *p_rsp_size = 7;
        e_rw_ndef_t1t_state = GETTING_ID;
        break;

    case GETTING_ID:
        /* Is CC Read and Is Ndef ?*/
        if ( ( cmd_size == 7 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
        {
            /* Fill File structure */
            rw_ndef_t1t_ndef.hr0 = p_cmd[0];
            rw_ndef_t1t_ndef.hr1 = p_cmd[1];
            memcpy( rw_ndef_t1t_ndef.uid, &p_cmd[2], sizeof( rw_ndef_t1t_ndef.uid ) );

            /* Read full card content */
            memcpy( rsp, ( uint8_t * )T1T_RALL, sizeof( T1T_RALL ) );
            memcpy( &rsp[3], rw_ndef_t1t_ndef.uid, sizeof( rw_ndef_t1t_ndef.uid ) );
            *p_rsp_size = sizeof( T1T_RALL ) + sizeof( rw_ndef_t1t_ndef.uid );
            e_rw_ndef_t1t_state = READING_CARD_CONTENT;
        }
        break;

    case READING_CARD_CONTENT:
        /* Is Read success ?*/
        if ( ( cmd_size == 123 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
        {
            /* Check CC */
            if ( p_cmd[10] == T1T_MAGIC_NUMBER )
            {
                uint8_t tmp = 14;
                uint8_t data_size;

                /* If not NDEF Type skip TLV */
                while ( p_cmd[tmp] != T1T_NDEF_TLV )
                {
                    tmp += 2 + p_cmd[tmp + 1];
                    if ( tmp > cmd_size ) return;
                }

                rw_ndef_t1t_ndef.record_size = p_cmd[tmp + 1];
                data_size = ( cmd_size - 1 ) - 16 - tmp - 2;

                /* Is NDEF read already completed ? */
                if( rw_ndef_t1t_ndef.record_size <= data_size )
                {
                    memcpy( rw_ndef_t1t_ndef.p_record, &p_cmd[tmp + 2],
                            rw_ndef_t1t_ndef.record_size );

                    /* Notify application of the NDEF reception */
                    if( p_rw_ndef_pull_cb != NULL )
                        p_rw_ndef_pull_cb( rw_ndef_t1t_ndef.p_record,
                                           rw_ndef_t1t_ndef.record_size );
                } else {
                    rw_ndef_t1t_ndef.record_ptr = data_size;
                    memcpy( rw_ndef_t1t_ndef.p_record, &p_cmd[tmp + 2],
                            rw_ndef_t1t_ndef.record_ptr );
                    rw_ndef_t1t_ndef.blk_nb = 0x10;

                    /* Read NDEF content */
                    memcpy( rsp, ( uint8_t * )T1T_READ8, sizeof( T1T_READ8 ) );
                    rsp[1] = rw_ndef_t1t_ndef.blk_nb;
                    memcpy( &rsp[10], rw_ndef_t1t_ndef.uid, sizeof( rw_ndef_t1t_ndef.uid ) );
                    *p_rsp_size = sizeof( T1T_READ8 ) + sizeof( rw_ndef_t1t_ndef.uid );

                    e_rw_ndef_t1t_state = READING_NDEF;
                }
            }
        }
        break;

    case READING_NDEF:
        /* Is Read success ?*/
        if ( ( cmd_size == 10 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
        {
            /* Is NDEF read already completed ? */
            if ( ( rw_ndef_t1t_ndef.record_size - rw_ndef_t1t_ndef.record_ptr ) < 8 )
            {
                memcpy ( &rw_ndef_t1t_ndef.p_record[rw_ndef_t1t_ndef.record_ptr], &p_cmd[1],
                         rw_ndef_t1t_ndef.record_size - rw_ndef_t1t_ndef.record_ptr );

                /* Notify application of the NDEF reception */
                if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t1t_ndef.p_record,
                            rw_ndef_t1t_ndef.record_size );
            }
            else
            {
                memcpy ( &rw_ndef_t1t_ndef.p_record[rw_ndef_t1t_ndef.record_ptr], &p_cmd[1], 8 );
                rw_ndef_t1t_ndef.record_ptr += 8;
                rw_ndef_t1t_ndef.blk_nb++;

                /* Read NDEF content */
                memcpy ( rsp, ( uint8_t * )T1T_READ8, sizeof( T1T_READ8 ) );
                rsp[1] = rw_ndef_t1t_ndef.blk_nb;
                memcpy ( &rsp[10], rw_ndef_t1t_ndef.uid, sizeof( rw_ndef_t1t_ndef.uid ) );
                *p_rsp_size = sizeof( T1T_READ8 ) + sizeof( rw_ndef_t1t_ndef.uid );
            }
        }
        break;

    default:
        break;
    }
}
#endif

/*************** END OF FUNCTIONS ***************************************************************************/
