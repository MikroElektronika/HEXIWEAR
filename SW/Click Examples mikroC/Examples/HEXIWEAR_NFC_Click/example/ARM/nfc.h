/****************************************************************************
* Title                 :   NFC Nxp Near Field Communication
* Filename              :   nfc.h
* Author                :   RBL
* Origin Date           :   20/02/2016
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description
*  20/02/16         .1             RBL      Interface Created.
*
*****************************************************************************/
/**
 * @file nfc.h
 * @brief API layer for NXP 7201 NFC chip
 *
 *  @date 20 Feb 2016
 *  @author Richard Lowe
 *  @copyright GNU Public License
 *
 *  @version .1 - Initial testing and verification
 *
 *  @note Test configuration:
 *   MCU:             STM32F107VC
 *   Dev.Board:       EasyMx Pro v7
 *   Oscillator:      72 Mhz internal
 *   Ext. Modules:    GPS Click
 *   SW:              ARM 4.7.1
 *
 */
#ifndef NFC_H_
#define NFC_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
#define NFC_SUCCESS         0
#define NFC_ERROR           -1

#define NFC_I2C_SLAVE       0x28
#define NFC_I2C_SLAVE_ALT   0x29

#define INTF_UNDETERMINED   0x0
#define INTF_FRAME          0x1
#define INTF_ISODEP         0x2
#define INTF_NFCDEP         0x3

#define PROT_UNDETERMINED   0x0
#define PROT_T1T            0x1
#define PROT_T2T            0x2
#define PROT_T3T            0x3
#define PROT_ISODEP         0x4
#define PROT_NFCDEP         0x5
#define PROT_MIFARE         0x80

#define MODE_POLL           0x00
#define MODE_LISTEN         0x80
#define MODE_MASK           0xF0

#define TECH_PASSIVE_NFCA   0
#define TECH_PASSIVE_NFCB   1
#define TECH_PASSIVE_NFCF   2
#define TECH_ACTIVE_NFCA    3
#define TECH_ACTIVE_NFCF    5
#define TECH_PASSIVE_15693  6

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct
{
    uint8_t interface;
    uint8_t protocol;
    uint8_t mode_tech;
} nfc_interface_t;

typedef enum
{
    NFC_MODE_NONE    = 0,
    NFC_MODE_CARDEMU = 0x01,
    NFC_MODE_P2P     = 0x02,
    NFC_MODE_RW      = 0x04
} nfc_mode_t;

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @defgroup General_Usage
 *
 */
/**
 * @brief NFC initialization
 * @ingroup General_Usage
 * @param uint8_t - I2C slave address
 * @return int - 0 success, -1 error
 */
int nfc_init( uint8_t slave_address );

void nfc_rx_ready( void );

void nfc_timer_tick( void );

/**
 * @brief Configure the mode of NFC
 * @ingroup General_Usage
 * @param mode
 * @return int - 0 success, -1 error
 */
int nfc_configure( nfc_mode_t mode );

/**
 * @brief nfc_start_discovery
 * @ingroup General_Usage
 * @param p_tech_tab
 * @param tech_tab_size
 * @return int - 0 success, -1 error
 */
int nfc_start_discovery( uint8_t *p_tech_tab, uint8_t tech_tab_size );

/**
 * @brief nfc_wait_for_discovery_notification
 * @ingroup General_Usage
 * @param p_rf_intf
 */
void nfc_wait_for_discovery_notification( nfc_interface_t *p_rf_intf );

/**
 * @brief nfc_process
 * @ingroup General_Usage
 * @param mode
 * @param rf_intf
 */
void nfc_process( uint8_t mode, nfc_interface_t *rf_intf );

/**
 * @brief nfc_restart_discovery
 * @ingroup General_Usage
 * @return int - 0 success, -1 error
 */
int nfc_restart_discovery( void );

/**
 * @brief nfc_stop_discovery
 * @ingroup General_Usage
 * @return int - 0 success, -1 error
 */
int nfc_stop_discovery( void );

#ifdef RW_SUPPORT
/**
 * @brief nfc_reader_tag_cmd
 * @ingroup General_Usage
 * @param command
 * @param command_size
 * @param answer
 * @param answer_size
 * @return int - 0 success, -1 error
 */
int nfc_reader_tag_cmd( uint8_t *command, uint8_t command_size,
                         uint8_t *answer, uint8_t *answer_size );
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*File_H_*/

/*** End of File **************************************************************/