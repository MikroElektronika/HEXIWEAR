/**
 * generic I2C data structures
 */

#include <stdint.h>
#include <stdbool.h>

#include "fsl_i2c_master_driver.h"

#ifndef HG_GENERIC_I2C_TYPES
#define HG_GENERIC_I2C_TYPES

typedef struct
{
  /**
   * general I2C information
   */
            uint32_t instance; // I2C instance
        i2c_device_t device;   // I2C device setting
  i2c_master_state_t state;    // I2C internal state space
            uint32_t timeout;  // I2C timeout

  /**
   * specific I2C information can go below this
   */

} genericI2cHandle_t;

typedef enum
{
  STATUS_I2C_SUCCESS,      // success
  STATUS_I2C_ERROR,        // fail
  STATUS_I2C_INIT_ERROR,   // initialization error
  STATUS_I2C_DEINIT_ERROR, // deinitialization error
  STATUS_I2C_TIMEOUT_ERROR // timeout occured

} statusI2C_t;

#endif
