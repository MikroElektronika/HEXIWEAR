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
/** @file RW_NDEF_T2T.c
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
/* TODO: No support for tag larger than 1024 bytes (requiring SECTOR_SELECT command use) */

#define T2T_MAGIC_NUMBER    0xE1
#define T2T_NDEF_TLV        0x03

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/
typedef enum
{
    INITIAL,
    READING_CC,
    READING_DATA,
    READING_NDEF
} rw_ndef_t2t_state_t;

typedef struct
{
    uint8_t blk_nb;
    uint16_t record_ptr;
    uint16_t record_size;
    uint8_t *p_record;
} rw_ndef_t2t_ndef_t;

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static rw_ndef_t2t_state_t e_rw_ndef_t2t_state = INITIAL;
static rw_ndef_t2t_ndef_t rw_ndef_t2t_ndef;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void rw_ndef_t2t_reset( void )
{
    e_rw_ndef_t2t_state = INITIAL;
    rw_ndef_t2t_ndef.p_record = ndef_buffer;
}

void rw_ndef_t2t_read_next(uint8_t *p_cmd, uint16_t cmd_size,
                           uint8_t *rsp, uint16_t *p_rsp_size )
{
    /* By default no further command to be sent */
    *p_rsp_size = 0;

    switch( e_rw_ndef_t2t_state )
    {
    case INITIAL:
        /* Read CC */
        rsp[0] = 0x30;
        rsp[1] = 0x03;
        *p_rsp_size = 2;
        e_rw_ndef_t2t_state = READING_CC;
        break;

    case READING_CC:
        /* Is CC Read and Is Ndef ?*/
        if ( ( cmd_size == 17 ) && ( p_cmd[cmd_size - 1] == 0x00 ) &&
                ( p_cmd[0] == T2T_MAGIC_NUMBER ) )
        {
            /* Read First data */
            rsp[0] = 0x30;
            rsp[1] = 0x04;
            *p_rsp_size = 2;

            e_rw_ndef_t2t_state = READING_DATA;
        }
        break;

    case READING_DATA:
        /* Is Read success ?*/
        if ( ( cmd_size == 17 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
        {
            uint8_t Tmp = 0;
            /* If not NDEF Type skip TLV */
            while ( p_cmd[Tmp] != T2T_NDEF_TLV )
            {
                Tmp += 2 + p_cmd[Tmp + 1];
                if ( Tmp > cmd_size ) return;
            }

            if( p_cmd[Tmp + 1] == 0xFF ) rw_ndef_t2t_ndef.record_size =
                    ( p_cmd[Tmp + 2] << 8 ) + p_cmd[Tmp + 3];
            else rw_ndef_t2t_ndef.record_size = p_cmd[Tmp + 1];

            /* Is NDEF read already completed ? */
            if ( rw_ndef_t2t_ndef.record_size <= ( ( cmd_size - 1 ) - Tmp - 2 ) )
            {
                memcpy ( rw_ndef_t2t_ndef.p_record, &p_cmd[Tmp + 2],
                         rw_ndef_t2t_ndef.record_size );

                /* Notify application of the NDEF reception */
                if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t2t_ndef.p_record,
                            rw_ndef_t2t_ndef.record_size );
            }
            else
            {
                rw_ndef_t2t_ndef.record_ptr = ( cmd_size - 1 ) - Tmp - 2;
                memcpy ( rw_ndef_t2t_ndef.p_record, &p_cmd[Tmp + 2],
                         rw_ndef_t2t_ndef.record_ptr );
                rw_ndef_t2t_ndef.blk_nb = 8;

                /* Read NDEF content */
                rsp[0] = 0x30;
                rsp[1] = rw_ndef_t2t_ndef.blk_nb;
                *p_rsp_size = 2;
                e_rw_ndef_t2t_state = READING_NDEF;
            }
        }
        break;

    case READING_NDEF:
        /* Is Read success ?*/
        if ( ( cmd_size == 17 ) && ( p_cmd[cmd_size - 1] == 0x00 ) )
        {
            /* Is NDEF read already completed ? */
            if ( ( rw_ndef_t2t_ndef.record_size - rw_ndef_t2t_ndef.record_ptr ) < 16 )
            {
                memcpy ( &rw_ndef_t2t_ndef.p_record[rw_ndef_t2t_ndef.record_ptr], p_cmd,
                         rw_ndef_t2t_ndef.record_size - rw_ndef_t2t_ndef.record_ptr );

                /* Notify application of the NDEF reception */
                if( p_rw_ndef_pull_cb != NULL ) p_rw_ndef_pull_cb( rw_ndef_t2t_ndef.p_record,
                            rw_ndef_t2t_ndef.record_size );
            }
            else
            {
                memcpy ( &rw_ndef_t2t_ndef.p_record[rw_ndef_t2t_ndef.record_ptr], p_cmd, 16 );
                rw_ndef_t2t_ndef.record_ptr += 16;
                rw_ndef_t2t_ndef.blk_nb += 4;

                /* Read NDEF content */
                rsp[0] = 0x30;
                rsp[1] = rw_ndef_t2t_ndef.blk_nb;
                *p_rsp_size = 2;
            }
        }
        break;

    default:
        break;
    }
}
#endif

/*************** END OF FUNCTIONS ***************************************************************************/