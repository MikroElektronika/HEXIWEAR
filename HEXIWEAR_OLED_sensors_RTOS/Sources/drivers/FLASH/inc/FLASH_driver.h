/**
 * FLASH driver functions
 * Project HEXIWEAR, 2015
 */

#ifndef HG_FLASH_DRIVER
#define HG_FLASH_DRIVER

#include "FLASH_defs.h"

/**
 * initialize FLASH
 */
statusFLASH_t FLASH_Init(
                            handleFLASH_t* self,
                          settingsFLASH_t* settings
                        );

/**
 * deinitialize the protocol FLASH uses
 */
statusFLASH_t FLASH_Deinit();

/**
 * write data to FLASH
 */
statusFLASH_t FLASH_WriteData (
                                const uint32_t flashAddress,
                                const uint8_t* dataToSend,
                                      uint32_t dataSize
                              );

/**
 * read FLASH status register
 */
statusFLASH_t FLASH_ReadStatus(
                                uint8_t* flashStatus
                              );

/**
 * read data from FLASH
 */
statusFLASH_t FLASH_ReadData(
                              uint32_t flashAddress,
                              uint8_t* dataToRead,
                              uint32_t dataSize
                            );

#endif
