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
/** @file RW_NDEF_T4T.c
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


/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/
typedef enum
{
    INITIAL,
    SELECTING_NDEF_APPLICATION20,
    SELECTING_NDEF_APPLICATION10,
    SELECTING_CC,
    READING_CC,
    SELECTING_NDEF,
    READING_NDEF_SIZE,
    READING_NDEF
} rw_ndef_t4t_state_t;

typedef struct
{
    uint8_t mapping_version;
    uint16_t mle;
    uint16_t mlc;
    uint8_t file_id[2];
    uint16_t max_ndef_file_size;
    uint8_t rd_access;
    uint8_t wr_access;
    uint16_t record_ptr;
    uint16_t record_size;
    uint8_t *p_record;
} rw_ndef_t4t_ndef_t;

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static const uint8_t RW_NDEF_T4T_APP_SELECT[] =
{
    0x00, 0xA4, 0x04, 0x00, 0x07, 0xD2, 0x76, 0x00, 0x00, 0x85, 0x01, 0x01
};
static const uint8_t RW_NDEF_T4T_CC_SELECT[] =
{
    0x00, 0xA4, 0x00, 0x0C, 0x02, 0xE1, 0x03
};
static const uint8_t RW_NDEF_T4T_NDEF_SELECT[] =
{
    0x00, 0xA4, 0x00, 0x0C, 0x02, 0xE1, 0x04
};
static const uint8_t RW_NDEF_T4T_READ[] =
{
    0x00, 0xB0, 0x00, 0x00, 0x0F
};

static const uint8_t RW_NDEF_T4T_OK[] = {0x90, 0x00};

static rw_ndef_t4t_state_t e_rw_ndef_t4t_state = INITIAL;
static rw_ndef_t4t_ndef_t rw_ndef_t4t_ndef;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void rw_ndef_t4t_reset( void )
{
    e_rw_ndef_t4t_state = INITIAL;
    rw_ndef_t4t_ndef.p_record = ndef_buffer;
}

void rw_ndef_t4t_read_next(uint8_t *p_cmd, uint16_t cmd_size,
                           uint8_t *rsp, uint16_t *p_rsp_size )
{
    /* By default no further command to be sent */
    *p_rsp_size = 0;

    switch( e_rw_ndef_t4t_state )
    {
    case INITIAL:
        /* Select NDEF Application in version 2.0 */
        memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_APP_SELECT, sizeof( RW_NDEF_T4T_APP_SELECT ) );
        *p_rsp_size = sizeof( RW_NDEF_T4T_APP_SELECT );
        e_rw_ndef_t4t_state = SELECTING_NDEF_APPLICATION20;
        break;

    case SELECTING_NDEF_APPLICATION20:
        /* Is NDEF Application Selected ?*/
        if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
                      sizeof( RW_NDEF_T4T_OK ) ) )
        {
            /* Select CC */
            memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_CC_SELECT, sizeof( RW_NDEF_T4T_CC_SELECT ) );
            *p_rsp_size = sizeof( RW_NDEF_T4T_CC_SELECT );
            e_rw_ndef_t4t_state = SELECTING_CC;
        }
        else
        {
            /* Select NDEF Application in version 1.0 */
            memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_APP_SELECT, sizeof( RW_NDEF_T4T_APP_SELECT ) );
            rsp[11] = 0x0;
            *p_rsp_size = sizeof( RW_NDEF_T4T_APP_SELECT );
            e_rw_ndef_t4t_state = SELECTING_NDEF_APPLICATION10;
        }
        break;

    case SELECTING_NDEF_APPLICATION10:
        /* Is NDEF Application Selected ?*/
        if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
                      sizeof( RW_NDEF_T4T_OK ) ) )
        {
            /* Select CC */
            memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_CC_SELECT, sizeof( RW_NDEF_T4T_CC_SELECT ) );
            rsp[3] = 0x00;
            *p_rsp_size = sizeof( RW_NDEF_T4T_CC_SELECT );
            e_rw_ndef_t4t_state = SELECTING_CC;
        }
        break;

    case SELECTING_CC:
        /* Is CC Selected ?*/
        if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
                      sizeof( RW_NDEF_T4T_OK ) ) )
        {
            /* Read CC */
            memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_READ, sizeof( RW_NDEF_T4T_READ ) );
            *p_rsp_size = sizeof( RW_NDEF_T4T_READ );
            e_rw_ndef_t4t_state = READING_CC;
        }
        break;

    case READING_CC:
        /* Is CC Read ?*/
        if ( ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
                        sizeof( RW_NDEF_T4T_OK ) ) ) && ( cmd_size == 15 + 2 ) )
        {
            /* Fill CC structure */
            rw_ndef_t4t_ndef.mapping_version = p_cmd[2];
            rw_ndef_t4t_ndef.mle = ( p_cmd[3] << 8 ) + p_cmd[4];
            rw_ndef_t4t_ndef.mlc = ( p_cmd[5] << 8 ) + p_cmd[6];
            rw_ndef_t4t_ndef.file_id[0] = p_cmd[9];
            rw_ndef_t4t_ndef.file_id[1] = p_cmd[10];
            rw_ndef_t4t_ndef.max_ndef_file_size = ( p_cmd[11] << 8 ) + p_cmd[12];
            rw_ndef_t4t_ndef.rd_access = p_cmd[13];
            rw_ndef_t4t_ndef.wr_access = p_cmd[14];

            /* Select NDEF */
            memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_NDEF_SELECT, sizeof( RW_NDEF_T4T_NDEF_SELECT ) );
            if ( rw_ndef_t4t_ndef.mapping_version == 0x10 ) rsp[3] = 0x00;
            rsp[5] = rw_ndef_t4t_ndef.file_id[0];
            rsp[6] = rw_ndef_t4t_ndef.file_id[1];
            *p_rsp_size = sizeof( RW_NDEF_T4T_NDEF_SELECT );
            e_rw_ndef_t4t_state = SELECTING_NDEF;
        }
        break;

    case SELECTING_NDEF:
        /* Is NDEF Selected ?*/
        if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
                      sizeof( RW_NDEF_T4T_OK ) ) )
        {
            /* Get NDEF file size */
            memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_READ, sizeof( RW_NDEF_T4T_READ ) );
            *p_rsp_size = sizeof( RW_NDEF_T4T_READ );
            rsp[4] = 2;
            e_rw_ndef_t4t_state = READING_NDEF_SIZE;
        }
        break;

    case READING_NDEF_SIZE:
        /* Is Read Success ?*/
        if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
                      sizeof( RW_NDEF_T4T_OK ) ) )
        {
            rw_ndef_t4t_ndef.record_size = ( p_cmd[0] << 8 ) + p_cmd[1];
            if( rw_ndef_t4t_ndef.record_size > RW_MAX_NDEF_FILE_SIZE )
            {
                /* NDEF record is too large, Abort */
            }
            else
            {
                rw_ndef_t4t_ndef.record_ptr = 0;

                /* Read NDEF data */
                memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_READ, sizeof( RW_NDEF_T4T_READ ) );
                rsp[3] =  2;
                rsp[4] = ( rw_ndef_t4t_ndef.record_size > rw_ndef_t4t_ndef.mle - 1 ) ?
                         rw_ndef_t4t_ndef.mle - 1 : ( uint8_t ) rw_ndef_t4t_ndef.record_size;
                *p_rsp_size = sizeof( RW_NDEF_T4T_READ );
                e_rw_ndef_t4t_state = READING_NDEF;
            }
        }
        break;

    case READING_NDEF:
        /* Is Read Success ?*/
        if ( !memcmp( &p_cmd[cmd_size - 2], ( uint8_t * )RW_NDEF_T4T_OK,
                      sizeof( RW_NDEF_T4T_OK ) ) )
        {
            memcpy( &rw_ndef_t4t_ndef.p_record[rw_ndef_t4t_ndef.record_ptr], p_cmd,
                    cmd_size - 2 );
            rw_ndef_t4t_ndef.record_ptr += cmd_size - 2;

            /* Is NDEF record read completed ?*/
            if ( rw_ndef_t4t_ndef.record_ptr == rw_ndef_t4t_ndef.record_size )
            {
                /* Notify application of the NDEF reception */
                if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t4t_ndef.p_record,
                            rw_ndef_t4t_ndef.record_size );
            }
            else
            {
                /* Read NDEF data */
                memcpy( rsp, ( uint8_t * )RW_NDEF_T4T_READ, sizeof( RW_NDEF_T4T_READ ) );
                rsp[3] =  rw_ndef_t4t_ndef.record_ptr + 2;
                rsp[4] = ( ( rw_ndef_t4t_ndef.record_size - rw_ndef_t4t_ndef.record_ptr ) >
                           rw_ndef_t4t_ndef.mle - 1 ) ? rw_ndef_t4t_ndef.mle - 1 : ( uint8_t ) (
                             rw_ndef_t4t_ndef.record_size - rw_ndef_t4t_ndef.record_ptr );
                *p_rsp_size = sizeof( RW_NDEF_T4T_READ );
            }
        }
        break;

    default:
        break;
    }
}
#endif


/*************** END OF FUNCTIONS ***************************************************************************/