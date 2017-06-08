/*
 * smoke.c
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * 0.0.1 (Jan/2017) Module created                          Stefan Popovic
 *
 *
 ******************************************************************************/
 /*                Includes
 ******************************************************************************/
 #include "smoke.h"
 #include "hal_smoke.h"
  
 /*                Typedefs
 ******************************************************************************/

 /*                Variables
 ******************************************************************************/

  uint32_t red_val = 0;
  uint32_t IR_val = 0;
  uint32_t green_val = 0;
  uint8_t num_of_LEDs = 0;   // Controls how many bytes to read from FIFO buffer

 /*                Function Definitions
 ******************************************************************************/

//
// Configuration
//

// Begin Interrupt configuration
uint8_t smoke_get_INT1( void ) 
{
  return ( smoke_read_byte( SMOKE_ADDRESS, SMOKE_INTSTAT1 ) );
}
uint8_t smoke_get_INT2( void ) 
{
  return ( smoke_read_byte( SMOKE_ADDRESS, SMOKE_INTSTAT2 ) );
}

void smoke_enable_AFULL( void ) 
{
  smoke_set_new_value( SMOKE_INTENABLE1, 
                       SMOKE_INT_A_FULL_MASK, 
                       SMOKE_INT_A_FULL_ENABLE );
}
void smoke_disable_AFULL( void ) 
{
  smoke_set_new_value( SMOKE_INTENABLE1, 
                       SMOKE_INT_A_FULL_MASK, 
                       SMOKE_INT_A_FULL_DISABLE );
}

void smoke_enable_DATARDY( void ) 
{
  smoke_set_new_value( SMOKE_INTENABLE1, 
                       SMOKE_INT_DATA_RDY_MASK, 
                       SMOKE_INT_DATA_RDY_ENABLE );
}
void smoke_disable_DATARDY( void ) 
{
  smoke_set_new_value( SMOKE_INTENABLE1, 
                       SMOKE_INT_DATA_RDY_MASK, 
                       SMOKE_INT_DATA_RDY_DISABLE );
}

void smoke_enable_ALCOVF( void ) 
{
  smoke_set_new_value( SMOKE_INTENABLE1, 
                       SMOKE_INT_ALC_OVF_MASK, 
                       SMOKE_INT_ALC_OVF_ENABLE );
}
void smoke_disable_ALCOVF( void ) 
{
  smoke_set_new_value( SMOKE_INTENABLE1, 
                       SMOKE_INT_ALC_OVF_MASK, 
                       SMOKE_INT_ALC_OVF_DISABLE );
}

void smoke_enable_PROXINT( void ) 
{
  smoke_set_new_value( SMOKE_INTENABLE1, 
                       SMOKE_INT_PROX_INT_MASK, 
                       SMOKE_INT_PROX_INT_ENABLE );
}
void smoke_disable_PROXINT( void ) 
{
  smoke_set_new_value( SMOKE_INTENABLE1, 
                       SMOKE_INT_PROX_INT_MASK, 
                       SMOKE_INT_PROX_INT_DISABLE );
}

void smoke_enable_DIETEMPRDY( void ) 
{
  smoke_set_new_value( SMOKE_INTENABLE2, 
                       SMOKE_INT_DIE_TEMP_RDY_MASK, 
                       SMOKE_INT_DIE_TEMP_RDY_ENABLE );
}
void smoke_disable_DIETEMPRDY( void ) 
{
  smoke_set_new_value( SMOKE_INTENABLE2, 
                       SMOKE_INT_DIE_TEMP_RDY_MASK, 
                       SMOKE_INT_DIE_TEMP_RDY_DISABLE );
}

// End Interrupt configuration

void smoke_shutdown( void ) 
{
  // Put IC into low power mode 
  // During smoke_shutdown the IC will continue to respond to I2C commands but will
  // not update with or take new readings (such as temperature)
  smoke_set_new_value( SMOKE_MODECONFIG, 
                       SMOKE_SHUTDOWN_MASK, 
                       SMOKE_SHUTDOWN );
}

void smoke_wakeup( void ) 
{
  // Pull IC out of low power mode 
  smoke_set_new_value( SMOKE_MODECONFIG, 
                       SMOKE_SHUTDOWN_MASK, 
                       SMOKE_WAKEUP );
}

void smoke_set_LED_mode( uint8_t mode ) 
{
  // Set which LEDs are used for sampling 
  smoke_set_new_value( SMOKE_MODECONFIG, 
                       SMOKE_MODE_MASK, 
                       mode );
}

void smoke_set_ADC_range( uint8_t adc_range ) 
{
  smoke_set_new_value( SMOKE_PARTICLECONFIG, 
                       SMOKE_ADCRANGE_MASK, 
                       adc_range );
}

void smoke_set_sample_rate( uint8_t sample_rate ) 
{
  smoke_set_new_value( SMOKE_PARTICLECONFIG, 
                       SMOKE_SAMPLERATE_MASK, 
                       sample_rate );
}

void smoke_set_pulse_width( uint8_t pulse_width ) 
{
  smoke_set_new_value( SMOKE_PARTICLECONFIG, 
                       SMOKE_PULSEWIDTH_MASK, 
                       pulse_width );
}

void smoke_set_pulse_amplitude_red( uint8_t amplitude ) 
{
  smoke_write_byte( SMOKE_ADDRESS, SMOKE_LED1_PULSEAMP, amplitude );
}

void smoke_set_pulse_amplitude_IR( uint8_t amplitude ) 
{
  smoke_write_byte( SMOKE_ADDRESS, SMOKE_LED2_PULSEAMP, amplitude );
}

void smoke_set_pulse_amplitude_green( uint8_t amplitude ) 
{
  smoke_write_byte( SMOKE_ADDRESS, SMOKE_LED3_PULSEAMP, amplitude );
}

void smoke_set_pulse_amplitude_proximity( uint8_t amplitude ) 
{
  smoke_write_byte( SMOKE_ADDRESS, SMOKE_LED_PROX_AMP, amplitude );
}

void smoke_set_proximity_threshold( uint8_t thresh_MSB ) 
{
  // Set the IR ADC count that will trigger the beginning of particle-sensing mode.
  // The thresh_MSB signifies only the 8 most significant-bits of the ADC count.
  smoke_write_byte( SMOKE_ADDRESS, SMOKE_PROXINTTHRESH, thresh_MSB );
}

// Given a slot number assign a thing to it
void smoke_enable_slot( uint8_t slot_number, uint8_t device ) 
{

  switch ( slot_number ) {
    case (1):
      smoke_set_new_value( SMOKE_MULTILEDCONFIG1, 
                           SMOKE_SLOT1_MASK, 
                           device );
      break;
    case (2):
      smoke_set_new_value( SMOKE_MULTILEDCONFIG1, 
                           SMOKE_SLOT2_MASK, 
                           device << 4 );
      break;
    case (3):
      smoke_set_new_value( SMOKE_MULTILEDCONFIG2, 
                           SMOKE_SLOT3_MASK, 
                           device );
      break;
    case (4):
      smoke_set_new_value( SMOKE_MULTILEDCONFIG2, 
                           SMOKE_SLOT4_MASK, 
                           device << 4 );
      break;
    default:
      // Shouldn't be here!
      break;
  }
}

// Clears all slot assignments
void smoke_disable_slots( void ) 
{
  smoke_write_byte( SMOKE_ADDRESS, SMOKE_MULTILEDCONFIG1, 0 );
  smoke_write_byte( SMOKE_ADDRESS, SMOKE_MULTILEDCONFIG2, 0 );
}

//
// FIFO Configuration
//

// Set sample average 
void smoke_set_FIFO_Average( uint8_t number_of_samples ) 
{
  smoke_set_new_value( SMOKE_FIFOCONFIG, 
                       SMOKE_SAMPLEAVG_MASK, 
                       number_of_samples );
}

// Resets all points to start in a known state
void smoke_clear_FIFO( void ) 
{
  smoke_write_byte( SMOKE_ADDRESS, SMOKE_FIFOWRITEPTR, 0 );
  smoke_write_byte( SMOKE_ADDRESS, SMOKE_FIFOOVERFLOW, 0 );
  smoke_write_byte( SMOKE_ADDRESS, SMOKE_FIFOREADPTR, 0 );
}

// Enable roll over if FIFO over flows
void smoke_enable_FIFO_rollover( void ) 
{
  smoke_set_new_value( SMOKE_FIFOCONFIG, 
                       SMOKE_ROLLOVER_MASK, 
                       SMOKE_ROLLOVER_ENABLE );
}

// Disable roll over if FIFO over flows
void smoke_disable_FIFO_rollover( void ) 
{
  smoke_set_new_value( SMOKE_FIFOCONFIG, 
                       SMOKE_ROLLOVER_MASK, 
                       SMOKE_ROLLOVER_DISABLE );
}

// Set number of samples to trigger the almost full interrupt (Page 18)
// Power on default is 32 samples
// Note it is reverse: 0x00 is 32 samples, 0x0F is 17 samples
void smoke_set_FIFO_almost_full( uint8_t number_Of_samples ) 
{
  smoke_set_new_value( SMOKE_FIFOCONFIG, 
                       SMOKE_A_FULL_MASK, 
                       number_Of_samples );
}

// Read the FIFO Write Pointer
uint8_t smoke_get_write_pointer( void ) 
{
  return ( smoke_read_byte( SMOKE_ADDRESS, SMOKE_FIFOWRITEPTR ) );
}

// Read the FIFO Read Pointer
uint8_t smoke_get_read_pointer( void ) 
{
  return ( smoke_read_byte( SMOKE_ADDRESS, SMOKE_FIFOREADPTR ) );
}


//
// Die Temperature
// Returns temp in C
//
float smoke_read_temp( void ) 
{
  uint8_t temp_response;
  uint8_t temp_int;
  uint8_t temp_frac;

  // Step 1: Config die temperature register to take 1 temperature sample
  smoke_write_byte(SMOKE_ADDRESS, SMOKE_DIETEMPCONFIG, 0x01);

 while ( true )
  {
    temp_response = smoke_read_byte( SMOKE_ADDRESS, SMOKE_DIETEMPCONFIG );
    if ( ( temp_response & 0x01 ) == 0 ) break; //We're done!
    hal_smoke_delay( 1 ); //Let's not over burden the I2C bus
  }
  
  // Step 2: Read die temperature register (integer)
  temp_int = smoke_read_byte( SMOKE_ADDRESS, SMOKE_DIETEMPINT );
  temp_frac = smoke_read_byte( SMOKE_ADDRESS, SMOKE_DIETEMPFRAC );

  // Step 3: Calculate temperature (datasheet pg. 23)
  return ( float )temp_int + ( ( float )temp_frac * 0.0625 );
}

// Returns die temp in F
float smoke_read_tempF( void ) 
{
  float temp = smoke_read_temp();

  if ( temp != -999.0 ) 
     temp = temp * 1.8 + 32.0;

  return ( temp );
}

// Set the PROX_INT_THRESHold
void smoke_set_PROXINTTHRESH( uint8_t val ) 
{
  smoke_write_byte( SMOKE_ADDRESS, SMOKE_PROXINTTHRESH, val );
}


//
// Device ID and Revision
//
uint8_t smoke_read_partID( void ) 
{
  return smoke_read_byte( SMOKE_ADDRESS, SMOKE_PARTID );
}


////////////////////////////////////////////////////////////////////////////////
//
// Data Collection
//

// Report oldest Red value
uint32_t smoke_get_red( void )
{
  return red_val;
}

// Report oldest IR value
uint32_t smoke_get_IR( void )
{ 
  return IR_val;
}

// Report oldest Green value
uint32_t smoke_get_green( void )
{
  return green_val;
}

void smoke_read_data( void )
{
  uint8_t temp_red[ 4 ];
  uint8_t temp_IR[ 4 ];
  uint8_t temp_green[ 4 ];
  
  uint8_t temp[ 9 ] = { 0 };
 
  temp[ 0 ] = SMOKE_FIFODATA;
  
  hal_smoke_read ( SMOKE_ADDRESS, &temp, 3 * num_of_LEDs );
 
  temp_red[ 3 ] = 0;
  temp_red[ 2 ] = temp[ 0 ];
  temp_red[ 1 ] = temp[ 1 ];
  temp_red[ 0 ] = temp[ 2 ];

  if ( num_of_LEDs > 1 ) 
  {

  temp[ 0 ] = SMOKE_FIFODATA;
  
  hal_smoke_read ( SMOKE_ADDRESS, &temp, 3 * num_of_LEDs );
  
  temp_IR[ 3 ] = 0;
  temp_IR[ 2 ] = temp[ 3 ];
  temp_IR[ 1 ] = temp[ 4 ];
  temp_IR[ 0 ] = temp[ 5 ];

  }

  if( num_of_LEDs > 2 ) 
  {
    
  temp[ 0 ] = SMOKE_FIFODATA;
  
  hal_smoke_read ( SMOKE_ADDRESS, &temp, 9 );

  temp_green[ 3 ] = 0;
  temp_green[ 2 ] = temp[ 6 ];
  temp_green[ 1 ] = temp[ 7 ];
  temp_green[ 0 ] = temp[ 8 ];
  }
  

  // Convert array to uint32
  memcpy( &red_val, temp_red, 4 );
  memcpy( &IR_val, temp_IR, 4 );
  memcpy( &green_val, temp_green, 4 ); 
}


 ///////////////////////////////////////////////////////////////////////////////
 void smoke_write_byte( uint8_t address, uint8_t reg, uint8_t value ) 
 {
  
  uint8_t buffer[ 2 ];

  buffer[ 0 ] = reg;
  buffer[ 1 ] = value;
  
  hal_smoke_write( SMOKE_ADDRESS, &buffer, 2 );
}

uint8_t smoke_read_byte( uint8_t address, uint8_t reg ) 
{
  uint8_t buffer;
  uint8_t value;

  buffer = reg;

  hal_smoke_read( address, &buffer, 1 );
  return buffer;
}

 void smoke_set_new_value( uint8_t reg, uint8_t mask, uint8_t value )
  {
    uint8_t old_value;   
    // Grab current register context
    old_value = smoke_read_byte( SMOKE_ADDRESS, reg );

    // Zero-out the portions of the register we're interested in
    old_value = old_value & mask;

    // Change value of reg
    smoke_write_byte( SMOKE_ADDRESS, reg, old_value | value );
  }

 
 void smoke_reset()
 {
   uint8_t buffer;
   int response;

   smoke_set_new_value( SMOKE_MODECONFIG, 
                        SMOKE_RESET_MASK, 
                        SMOKE_RESET );
   
    buffer = SMOKE_MODECONFIG;
    response = hal_smoke_read( SMOKE_ADDRESS, &buffer, 1 );
    
    while ( true ) 
    {
    if ( ( buffer & SMOKE_RESET ) == 0) break; // We're done!
    hal_smoke_delay( 1 );
    }

 }
 
 
 void smoke_init()
 {
    uint8_t buffer[ 4 ] = { 0 };

    hal_smoke_init();
    
    // Reset all configuration, threshold, and data registers to POR values
    smoke_reset();
    
    hal_smoke_delay( 100 );         
 }
 
 void smoke_set_registers_default()
 {
    num_of_LEDs = 3;
    // FIFO Configuration
    smoke_set_FIFO_average( SMOKE_SAMPLEAVG_4 );
    smoke_enable_FIFO_rollover(); // Allow FIFO to wrap/roll over
    
    // Mode Configuration  
    smoke_set_LED_mode( SMOKE_MODE_MULTILED ); // Watch all three LED channels

    // Particle Sensing Configuration
    smoke_set_ADC_range( SMOKE_ADCRANGE_16384 ); // 62.5pA per LSB

    smoke_set_sample_rate( SMOKE_SAMPLERATE_50 ); // Take 50 samples per second

    // The longer the pulse width the longer range of detection you'll have
    smoke_set_pulse_width( SMOKE_PULSEWIDTH_411 ); // 18 bit resolution
  
    // LED Pulse Amplitude Configuration
    smoke_set_pulse_amplitude_red( SMOKE_MAX_POWER_LEVEL );
    smoke_set_pulse_amplitude_IR( SMOKE_MAX_POWER_LEVEL );
    smoke_set_pulse_amplitude_green( SMOKE_MAX_POWER_LEVEL );
    smoke_set_pulse_amplitude_proximity( SMOKE_MAX_POWER_LEVEL );

    // Multi-LED Mode Configuration, Enable the reading of the three LEDs
    smoke_disable_slots();
    smoke_enable_slot( 1, SMOKE_SLOT_RED_LED );
    smoke_enable_slot( 3, SMOKE_SLOT_IR_LED );
    smoke_enable_slot( 2, SMOKE_SLOT_GREEN_LED );

    smoke_clear_FIFO(); // Reset the FIFO before we begin checking the sensor
  
 }

void smoke_set_registers(   uint16_t avg_sample,
                            uint16_t mode,
                            uint16_t adc_range,
                            uint16_t sample_rate,
                            uint16_t pulse_width,
                            uint16_t led_power_level )                                            
{
  num_of_LEDs = 0;

  // FIFO Configuration
  
  // The chip will average multiple samples of same type together if you wish

  // avg_sample = 1; No averaging per FIFO record
  if ( avg_sample == 1 ) smoke_set_FIFO_average( SMOKE_SAMPLEAVG_1 ); 
  if ( avg_sample == 2 ) smoke_set_FIFO_average( SMOKE_SAMPLEAVG_2 );
  if ( avg_sample == 4 ) smoke_set_FIFO_average( SMOKE_SAMPLEAVG_4 );
  if ( avg_sample == 8 ) smoke_set_FIFO_average( SMOKE_SAMPLEAVG_8 );
  if ( avg_sample == 16 ) smoke_set_FIFO_average( SMOKE_SAMPLEAVG_16 );
  if ( avg_sample == 32 ) smoke_set_FIFO_average( SMOKE_SAMPLEAVG_32 );

  smoke_enable_FIFO_rollover(); // Allow FIFO to wrap/roll over
  
  // Mode Configuration

  // Watch all three LED channels
  if ( mode == SMOKE_MODE_MULTILED ) 
  {
    smoke_set_LED_mode( SMOKE_MODE_MULTILED ); 
    num_of_LEDs = 3;
  }
  // Red and IR LED channels
  else if ( mode == SMOKE_MODE_REDIRONLY ) 
  {
    smoke_set_LED_mode( SMOKE_MODE_REDIRONLY ); 
    num_of_LEDs = 2;
  }
  // Red LED channel only
  else
  {
     smoke_set_LED_mode( SMOKE_MODE_REDONLY );
     num_of_LEDs = 1;
  }

  // Particle Sensing Configuration
  
  smoke_set_ADC_range( adc_range ); // 62.5pA per LSB
  
  // Take SMOKE_SAMPLERATE_ samples per second
  if ( sample_rate < 100 ) smoke_set_sample_rate( SMOKE_SAMPLERATE_50 ); 
  else if ( sample_rate < 200 ) smoke_set_sample_rate( SMOKE_SAMPLERATE_100 );
  else if ( sample_rate < 400 ) smoke_set_sample_rate( SMOKE_SAMPLERATE_200 );
  else if ( sample_rate < 800 ) smoke_set_sample_rate( SMOKE_SAMPLERATE_400 );
  else if ( sample_rate < 1000 ) smoke_set_sample_rate( SMOKE_SAMPLERATE_800 );
  else if ( sample_rate < 1600 ) smoke_set_sample_rate( SMOKE_SAMPLERATE_100 );
  else if ( sample_rate < 3200 ) smoke_set_sample_rate( SMOKE_SAMPLERATE_1600 );
  else if ( sample_rate == 3200 ) smoke_set_sample_rate( SMOKE_SAMPLERATE_3200 );
  else smoke_set_sample_rate( SMOKE_SAMPLERATE_50 );

  // The longer the pulse width the longer range of detection you'll have
  // At 69us and 0.4mA it's about 2 inches
  // At 411us and 0.4mA it's about 6 inches

  // 15 bit resolution
  if ( pulse_width < 118 ) smoke_set_pulse_width( SMOKE_PULSEWIDTH_69 ); 

  // 16 bit resolution
  else if ( pulse_width < 215 ) smoke_set_pulse_width( SMOKE_PULSEWIDTH_118 ); 

  // 17 bit resolution
  else if ( pulse_width < 411 ) smoke_set_pulse_width( SMOKE_PULSEWIDTH_215 ); 

  // 18 bit resolution
  else if ( pulse_width == 411 ) smoke_set_pulse_width( SMOKE_PULSEWIDTH_411 ); 

  else smoke_set_pulse_width( SMOKE_PULSEWIDTH_69 );
  
  // LED Pulse Amplitude Configuration
  
  // Default is 0x1F which gets us 6.4mA
  // led_power_level = 0x02, 0.4mA - Presence detection of ~4 inch
  // led_power_level = 0x1F, 6.4mA - Presence detection of ~8 inch
  // led_power_level = 0x7F, 25.4mA - Presence detection of ~8 inch
  // led_power_level = 0xFF, 50.0mA - Presence detection of ~12 inch

  smoke_set_pulse_amplitude_red( led_power_level );
  smoke_set_pulse_amplitude_IR( led_power_level );
  smoke_set_pulse_amplitude_green( led_power_level );
  smoke_set_pulse_amplitude_proximity( led_power_level );
  
  // Multi-LED Mode Configuration, Enable the reading of the three LEDs
  
  smoke_enable_slot( 1, SMOKE_SLOT_RED_LED );
  if ( mode > 1 ) smoke_enable_slot( 2, SMOKE_SLOT_IR_LED );
  if ( mode > 2 ) smoke_enable_slot( 3, SMOKE_SLOT_GREEN_LED );

  smoke_clear_FIFO(); // Reset the FIFO before we begin checking the sensor 
}

/*                                                                 End of File
 ******************************************************************************/ 