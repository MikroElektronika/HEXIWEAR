/**
 * @file                                                        nfc_tag2.h
 * @brief                   NFC tag 2 driver
 *
 * @defgroup NT2 NFC Tag 2
 * @brief NFC Tag 2 click driver
 *
 * Driver for NFC Tag click board which caries NT3H1101 energy harvesting
 * NFC Forum Type 2 Tag with field detection pin and I2C interface.
 *
 * @{
 *
 * ### Device Description ###
 *
 * @par
 * The NTAG I2C is the first product of NXP’s NTAG family offering both
 * contactless and contact interfaces. In addition to the
 * passive NFC Forum compliant contactless interface, the IC features an I2C
 * contact interface, which can communicate with a microcontroller if the
 * NTAG I2C is powered from an external power supply. An additional externally
 * powered SRAM mapped into the memory allows a fast data transfer between the
 * RF and I2C interfaces and vice versa, without the write cycle limitations
 * of the EEPROM memory.
 *
 * @par
 * The NTAG I2C product features a configurable field detection pin, which
 * provides a trigger to an external device depending on the activities at the
 * RF interface.
 *
 * @par
 * The NTAG I2C product can also supply power to external (low power) devices
 * (e.g. a microcontroller) via the embedded energy harvesting circuitry.
 *
 * ### Features ###
 *
 * @par
 * - RF interface NFC Forum Type 2 Tag compliant
 * - I2C interface
 * - Configurable field detection pin based on open drain implementation that
 * can be triggered upon the following events:
 *  + RF field presence
 *  + First start of communication
 *  + Selection of the tag only
 * - 64 byte SRAM buffer for fast transfer of data (Pass-through mode) between
 * the RF and the I2C interfaces located outside the User Memory
 * - Wake up signal at the field detect pin when:
 *  + New data has arrived from one interface
 *  + Data has been read by the receiving interface
 * - Clear arbitration between RF and I2C interfaces:
 *  + First come, first serve strategy
 *  + Status flag bits to signal if one interface is busy writing to or reading
 * data from the EEPROM
 * - Energy harvesting functionality to power external devices
 *
 * ### Library Desription ###
 *
 * @par
 * Library proveds routines for easy building of the higher layers and control
 * of the NT3H1101 module.
 *
 * @example NFC_Tag2_ARM.c
 * @example NFC_Tag2_PIC.c
 * @example NFC_Tag2_PIC32.c
 * @example NFC_Tag2_dsPIC.c
 * @example NFC_Tag2_AVR.c
 * 
 ******************************************************************************/

#ifndef NFC_TAG2_H
#define NFC_TAG2_H

#include <stdbool.h>
#include <string.h>
#include "nfc_tag2_hal.h"

/**
 * @name    Device Properties
 *
 ******************************************************************************/
///@{
#define NT2_SERIAL_NUM_SIZE                         7
#define NT2_STATIC_LOCK_SIZE                        2
#define NT2_CAP_CONTAINER_SIZE                      4
#define NT2_DYNAMIC_LOCK_SIZE                       3
#define NT2_USER_CONFIG_SIZE                        8
#define NT2_SRAM_SIZE                               64
#define NT2_USER_MEMORY_SIZE                        888
///@}
/**
 * @name    Return values
 *
 ******************************************************************************/
 ///@{
#define NT2_OK                                      0
#define NT2_BLOCK_READ_ERR                          (-2)
#define NT2_BLOCK_WRITE_ERR                         (-3)
#define NT2_INVALID_MEMORY_ENTRY                    (-4)
///@}

/**
 * @name    Common Configuration Values
 *
 ******************************************************************************/
///@{
#define NT2_I2C_RST_ON                              0x80
#define NT2_I2C_RST_OFF                             0x00
#define NT2_FD_OFF_MODE_0                           0x00
#define NT2_FD_OFF_MODE_1                           0x10
#define NT2_FD_OFF_MODE_2                           0x20
#define NT2_FD_OFF_MODE_3                           0x30
#define NT2_FD_ON_MODE_0                            0x00
#define NT2_FD_ON_MODE_1                            0x04
#define NT2_FD_ON_MODE_2                            0x08
#define NT2_FD_ON_MODE_3                            0x0C
#define NT2_DIRECTION_RF_TO_I2C                     0x01
#define NT2_DIRECTION_I2C_TO_RF                     0x00

#define NT2_I2C_CLK_STR_ON                          0x01
#define NT2_I2C_CLK_STR_OFF                         0x00
///@}

/**
 * @name    Session Configuration Masks
 *
 ******************************************************************************/
///@{
#define NT2_MASK_NC_I2C_RST                         0x80
#define NT2_MASK_NC_PTHRU                           0x40
#define NT2_MASK_NC_FD_OFF                          0x30
#define NT2_MASK_NC_FD_ON                           0x0C
#define NT2_MASK_NC_SRAM_MIRROR                     0x02
#define NT2_MASK_NC_DIRECTION_MASK                  0x01
///@}

/**
 * @name    Session Configuration Values for NS reg
 *
 ******************************************************************************/
///@{
#define NT2_SESSION_PTHRU_ON                        0x40
#define NT2_SESSION_PTHRU_OFF                       0x00
#define NT2_SESSION_SRAM_MIRROR_ON                  0x20
#define NT2_SESSION_SRAM_MIRROR_OFF                 0x00
///@}

/**
 * @name    NS Configuration Masks
 *
 ******************************************************************************/
///@{
#define NT2_MASK_NS_I2C_LOCK_MASK                   0x40
#define NT2_MASK_NS_EEPROM_MASK                     0x04
///@}

/**
 * @name    NS Configuraton Values
 *
 ******************************************************************************/
///@{
#define NT2_EEPROM_ERR_CLEAR                        0x00
#define NT2_I2C_LOCK_ON                             0x40
#define NT2_I2C_LOCK_OFF                            0x00
///@}

/**
 * @name    NS Status Values
 *
 ******************************************************************************/
///@{
#define NT2_STATUS_NDEF_DATA                        0x80
#define NT2_STATUS_I2C_LOCK                         0x40
#define NT2_STATUS_RF_LOCK                          0x20
#define NT2_STATUS_SRAM_I2C_READY                   0x10
#define NT2_STATUS_SRAM_RF_READY                    0x08
#define NT2_STATUS_EPPROM_ERR                       0x04
#define NT2_STATUS_EEPROM_BUSY                      0x02
#define NT2_STATUS_RF_FIELD_DETECTED                0x01
///@}

/**
 * @name    Types
 *
 ******************************************************************************/
///@{
/**
 * @enum NFCTAG2_SET
 * @brief NFC Tag 2 Setable Registers
 *
 * Enum is usable as first argument with functions :
 *  + @link nfctag2_get @endlink
 *  + @link nfctag2_get @endlink
 *
 * Additional infromations about @c NT2_USER_CONFIG register can be found in
 * @link Configuration values @endlink part related to this module.
 * For even more informations about registers and how to manipulate with them
 * check the NT3H1101 datasheet.
 */
typedef enum {

    NT2_SET_SERIAL_NO           = 0,
    NT2_SET_STATIC_LOCK         = 1,
    NT2_SET_CAP_CONTAINER       = 2,
    NT2_SET_DYNAMIC_LOCK        = 3,
    NT2_SET_SRAM_MEMORY         = 4

}NFCTAG2_SET;

/**
 * @enum NFCTAG2_CFG
 * @brief NFC Tag 2 User Configuration
 *
 * Enum is usable as first argument with functions :
 *  + @link nfctag2_config_get @endlink
 *  + @link nfctag2_config_set @endlink
 *  + @link nfctag2_session_get @endlink
 *  + @link nfctag2_session_set @endlink
 *
 * Value represents the register offset inside the block for the config and
 * session function calls.
 *
 * @note
 * @c NT2_SES_NS_REG should be used only in case of config function call
 * @c NT2_CFG_LOCK should be used only in case of session function call
 *
 * Additional infromations about function descriptions.
 * For even more informations about registers and how to manipulate with them
 * check the NT3H1101 datasheet.
 */
typedef enum {

    NT2_CFG_NC_REG              = 0,
    NT2_CFG_LAST_NDEF           = 1,
    NT2_CFG_SRAM_MIRROR         = 2,
    NT2_CFG_WDT_LS              = 3,
    NT2_CFG_WDT_MS              = 4,
    NT2_CFG_STR                 = 5,
    NT2_CFG_LOCK                = 6,
    NT2_SES_NS_REG              = 6,

}NFCTAG2_CFG;

/**
 * @struct nfctag2_click
 * @brief NFC Tag 2 click
 *
 * @par
 * Every structure member represents some memory area inside device. It is not
 * necessary to use this struct inside your implementation of the higher layers.
 */
typedef struct {

    /**
     * @brief Device Hardware Address */
    uint8_t     i2c_address;
    /**
     * @brief Device Serial Number */
    uint8_t     serial_num[ NT2_SERIAL_NUM_SIZE ];
    /**
     * @brief Device Static Lock */
    uint8_t     static_lock[ NT2_STATIC_LOCK_SIZE ];
    /**
     * @brief Device Dynamic Lock */
    uint8_t     dynamic_lock[ NT2_DYNAMIC_LOCK_SIZE ];
    /**
     * @brief Capability Container */
    uint8_t     cap_containter[ NT2_CAP_CONTAINER_SIZE ];
    /**
     * @brief SRAM Memory */
    uint8_t     sram_memory[ NT2_SRAM_SIZE ];
    /**
     * @brief Device Configuration */
    uint8_t     config[ NT2_USER_CONFIG_SIZE ];
    /**
     * @brief Device Session Settings */
    uint8_t     session[ NT2_USER_CONFIG_SIZE ];
    /**
     * @brief Device User Memory */
    uint8_t     user_memory[ NT2_USER_MEMORY_SIZE ];

}nfctag2_click;


///@}
/**
 * @name    Functions
 ******************************************************************************/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief NFC Tag 2 Initialization
 * 
 * @retval NT2_OK                   - Success
 * @retval NT2_INVALID_BLOCK_READ   - Read Error
 * @retval NT2_INVALID_BLOCK_WRITE  - Write Error
 *
 * Initializes the library. Executes HAL initialization and assigns the provided
 * I2C address to the private variable. Function must be called before any other
 * function which uses device.
 */
int nfctag2_init( uint8_t i2c_address );

/**
 * @brief Change Device I2C Address
 *
 * @param[in]   uint8_t     new_address
 *
 * @retval NT2_OK                   - Success
 * @retval NT2_INVALID_BLOCK_READ   - Read Error
 * @retval NT2_INVALID_BLOCK_WRITE  - Write Error
 *
 * Function dynamicly changes the device I2C address.
 *
 * @warning
 * Changes are writen inside non volatile memory so device will have new address
 * which can not be read because the reading of the first byte of the device
 * EEPROM always returns 04.
 */
int nfctag2_i2c_addres( uint8_t new_address );

/**
 * @brief Common Get Function
 *
 * @param[in]   NFCTAG2_SET     setting -   setting
 * @param[out]  uint8_t*        output -    buffer
 *
 * @retval NT2_OK                   - Success
 * @retval NT2_INVALID_BLOCK_READ   - Read Error
 * @retval NT2_INVALID_BLOCK_WRITE  - Write Error
 *
 * @par
 * Get (Read) function usable for settings defined by
 * @link NFCTAG2_SET @endlink enum. Depend on the size of the registers buffer
 * with the proper size should be pointed with output argument.
 */
int nfctag2_get( NFCTAG2_SET setting, uint8_t *output );

/**
 * @brief Common Get Function
 *
 * @param[in]   NFCTAG2_SET setting
 * @param[out]  uint8_t*    output
 *
 * @retval NT2_OK                   - Success
 * @retval NT2_INVALID_BLOCK_READ   - Read Error
 * @retval NT2_INVALID_BLOCK_WRITE  - Write Error
 *
 * @par
 * Set (Write) function usable for settings defined by
 * @link NFCTAG2_SET @endlink enum. Depend on the size of the registers buffer
 * with the proper size should be pointed with output argument.
 *
 * @bug
 * After the execution of this function HW address is changed to 0x04.
 *
 * @todo
 * Block writting of the 0 byte.
 */
int nfctag2_set( NFCTAG2_SET setting, uint8_t *input );

/**
 * @brief Configuration Read Function
 *
 * @param[in]   NFCTAG2_CFG reg
 *
 * @return uint8_t Content of the specific configuration register
 *
 * @par
 * Reads the content of the specified configuration register.
 */
uint8_t nfctag2_config_get( NFCTAG2_CFG reg );

/**
 * @brief Configuration Write Function
 *
 * @param[in]   NFCTAG2_CFG reg
 * @param[in]   uint8_t     input
 *
 * @retval NT2_OK                   - Success
 * @retval NT2_INVALID_BLOCK_READ   - Read Error
 * @retval NT2_INVALID_BLOCK_WRITE  - Write Error
 *
 * @par
 * Writes new data to specified configuration register.
 */
int nfctag2_config_set( NFCTAG2_CFG reg, uint8_t input );

/**
 * @brief Session Configuration Read Function
 *
 * @param[in] NFCTAG2_CFG reg
 *
 * @return uint8_t Content of the specific session register
 *
 * Reads the status of session registers. NS reg is mostly status register
 * which can be used to read current status of the device.
 */
uint8_t nfctag2_session_get( NFCTAG2_CFG reg );

/**
 * @brief Session Configuration Write Function
 *
 * @param[in]   NFCTAG2_CFG reg
 * @param[in]   uint8_t     mask
 * @param[in]   uint8_t     value
 *
 * @retval NT2_OK                   - Success
 * @retval NT2_INVALID_BLOCK_READ   - Read Error
 * @retval NT2_INVALID_BLOCK_WRITE  - Write Error
 *
 * @par
 * Session configuration setup. Writes data to provided seesion register. Usage
 * of mask is needed in case of NC and NS reg setup.
 */
int nfctag2_session_set( NFCTAG2_CFG reg, uint8_t mask, uint8_t value );

/**
 * @brief Read User Memory
 *
 * @param[in]   uint16_t    mem_offset
 * @param[out]  uint8_t*    buffer
 * @param[in]   uint8_t     count
 *
 * @retval NT2_OK                   - Success
 * @retval NT2_INVALID_BLOCK_READ   - Read Error
 * @retval NT2_INVALID_BLOCK_WRITE  - Write Error
 *
 * @par
 * Reads user memory area. Buffer size must not exceed @c NT2_USER_MEMORY_SIZE,
 * also ( mem_offset + count ) must not be bigger than NT2_USER_MEMORY_SIZE.
 */
int nfctag2_memory_read( uint16_t mem_offset, uint8_t *buffer, uint16_t count );

/**
 * @brief Write User Memory
 *
 * @param[in]   uint16_t    mem_offset
 * @param[in]   uint8_t*    buffer
 * @param[in]   uint8_t     count
 *
 * @retval NT2_OK                   - Success
 * @retval NT2_INVALID_BLOCK_READ   - Read Error
 * @retval NT2_INVALID_BLOCK_WRITE  - Write Error
 *
 * @par
 * Writes user memory area. Buffer size must not exceed @c NT2_USER_MEMORY_SIZE,
 * also ( mem_offset + count ) must not be bigger than NT2_USER_MEMORY_SIZE.
 */
int nfctag2_memory_write( uint16_t mem_offset, uint8_t *buffer, uint16_t count );


#ifdef __cplusplus
} // extern "C"
#endif

#endif
///@}

/**
 * @}                                                            End of File
 ******************************************************************************/
