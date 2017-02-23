/*
 * hal_ac_current.c
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * 0.0.1 (Sep/2016) Module created                          Stefan Popovic
 *
 * 
 ******************************************************************************/

#include "hal_ac_current.h"
#include "ac_current.h"

/*                 Preprocessors
 ******************************************************************************/

#define ADC_12_BIT             12
#define ADC_10_BIT             10
#define ADC_8_BIT               8

#define ADC_12_BIT_MSB_MASK  0x1F
#define ADC_10_BIT_MSB_MASK  0x03
#define ADC_8_BIT_MSB_MASK   0x00

#define ADC_ITERATIONS         10

#define ADC_CONVERSION_SIZE                         ADC_12_BIT
#define ADC_ITERATION_SIZE                      ADC_ITERATIONS
#define FACTOR               8.25

/*                Typedefs
 ******************************************************************************/


/*                Variables
 ******************************************************************************/

extern sfr sbit AC_CURRENT_CS;
 
void ac_current_init ()
{
  hal_ac_current_init();
  AC_CURRENT_CS = 1;
}


float ac_current_get_mA( uint8_t voltage_supply )
{
  // Local variables
  uint8_t i;
  uint8_t buffer[ 10 ];
  uint8_t readLSB;
  uint8_t readMSB;
  uint8_t MSB_mask;
  uint16_t max_val;
  uint16_t tmp;
  float avg;
  uint16_t sum;

  // Initialize variables
  MSB_mask = 0x00;
  tmp = 0;
  avg = 0;
  sum = 0;
  max_val = 0;

  // Setting appropriate MSB mask
  if ( ADC_CONVERSION_SIZE == ADC_12_BIT )
  {
    MSB_mask = ADC_12_BIT_MSB_MASK;
    max_val = 4095;
  }
  else if ( ADC_CONVERSION_SIZE == ADC_10_BIT )
  {
    MSB_mask = ADC_10_BIT_MSB_MASK;
    max_val = 1024;
  }
  else if ( ADC_CONVERSION_SIZE == ADC_8_BIT )
    {
    MSB_mask = ADC_8_BIT_MSB_MASK;
    max_val = 255;
    }
  else return 0.0;
    
  // SPI reading
  for( i = 0; i < ADC_ITERATION_SIZE; i++ )
  {
    AC_CURRENT_CS = 0;                          // Select MCP3201
    
    hal_ac_current_read( buffer, 2 );               

    AC_CURRENT_CS = 1;                          // Deselect MCP3201
    
    // Reading most significant and least significant bytes
    readMSB = buffer[ 0 ] & MSB_mask;
    readLSB = buffer[ 1 ];
    
    // Forming ADC_CONVERSION_SIZE
    tmp = ( ( readMSB & MSB_mask ) << 8 );
    tmp =  tmp | readLSB;
    
    sum = sum + tmp;                            // Sum of the ADC readings
  }
  
  // Average ADC value based on sum of the ADC readings
  avg = ( float ) (sum / ADC_ITERATION_SIZE ); 
  avg = ( avg / max_val ) * FACTOR * 1000;

  return avg;                                   // Returns the average ADC value
}

float ac_current_get_A( uint8_t voltage_supply )
{
  // Local variables
  uint8_t i;
  uint8_t buffer[ 10 ];
  uint8_t readLSB;
  uint8_t readMSB;
  uint8_t MSB_mask;
  uint16_t max_val;
  uint16_t tmp;
  float avg;
  uint16_t sum;

  // Initialize variables
  MSB_mask = 0x00;
  tmp = 0;
  avg = 0;
  sum = 0;
  max_val = 0;

  // Setting appropriate MSB mask
  if ( ADC_CONVERSION_SIZE == ADC_12_BIT )
  {
    MSB_mask = ADC_12_BIT_MSB_MASK;
    max_val = 4095;
  }
  else if ( ADC_CONVERSION_SIZE == ADC_10_BIT )
  {
    MSB_mask = ADC_10_BIT_MSB_MASK;
    max_val = 1024;
  }
  else if ( ADC_CONVERSION_SIZE == ADC_8_BIT )
    {
    MSB_mask = ADC_8_BIT_MSB_MASK;
    max_val = 255;
    }
  else return 0.0;
    
  // SPI reading
  for( i = 0; i < ADC_ITERATION_SIZE; i++ )
  {
    AC_CURRENT_CS = 0;                          // Select MCP3201
    
    hal_ac_current_read( buffer, 2 );               

    AC_CURRENT_CS = 1;                          // Deselect MCP3201
    
    // Reading most significant and least significant bytes
    readMSB = buffer[ 0 ] & MSB_mask;
    readLSB = buffer[ 1 ];
    
    // Forming ADC_CONVERSION_SIZE
    tmp = ( ( readMSB & MSB_mask ) << 8 );
    tmp =  tmp | readLSB;
    
    sum = sum + tmp;                            // Sum of the ADC readings
  }
  
  // Average ADC value based on sum of the ADC readings
  avg = ( float ) (sum / ADC_ITERATION_SIZE ); 
  avg = ( avg / max_val ) * FACTOR;

  return avg;                                   // Returns the average ADC value
}
/*                                                                 End of File
 ******************************************************************************/