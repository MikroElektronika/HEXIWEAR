/**
 * general I2C info
 * Project HEXIWEAR, 2015
 */

#ifndef HG_GENERIC_I2C_INFO
#define HG_GENERIC_I2C_INFO

#include "MK64F12.h"

// interrupt numbers and values
#define FSL_I2C_IRQn      ( I2C0_IRQn )
#define FSL_I2C_IRQ_PRIO ( 0 )

// total number of I2C modules
#define I2C_NUM_MAX (3)

// I2C timeout value
#define I2C_TIMEOUT (100)

// I2C baud-rate
#define I2C_BAUDRATE (400ul)


#endif
