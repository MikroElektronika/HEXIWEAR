/**
 * EEPROM-related data types
 * Project HEXIWEAR, 2015
 */

#ifndef HG_EEPROM_TYPES
#define HG_EEPROM_TYPES

typedef enum
{
  STATUS_EEPROM_SUCCESS,        // success
  STATUS_EEPROM_ERROR,          // fail
  STATUS_EEPROM_PROTOCOL_ERROR, // SPI failure
  STATUS_EEPROM_INIT_ERROR,     // initialization error
  STATUS_EEPROM_DEINIT_ERROR    // deinitialization error

} statusEEPROM_t;


#endif
