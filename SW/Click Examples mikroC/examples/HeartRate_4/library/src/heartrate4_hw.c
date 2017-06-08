#include "heartrate4_hw.h"
#include <stdint.h>

uint32_t red_val = 0;
uint32_t red_average = 0;

// HELPER FUNCTIONS
uint8_t hr4_read_reg ( uint8_t reg )
{
    uint8_t temp = reg;
    hal_hr4_read( HR4_I2C_ADDRESS, &temp, 1 );
    return temp;
}

void hr4_read_reg_multi ( uint8_t reg, uint8_t *buffer, uint8_t count )
{
    uint8_t* temptr = buffer;
    temptr[0] = reg;
    hal_hr4_read( HR4_I2C_ADDRESS, temptr, count );
}

void hr4_write_reg( uint8_t reg, uint8_t reg_val )
{
    uint8_t send_buffer[ 2 ];

    send_buffer[0] = reg;
    send_buffer[1] = reg_val;
    hal_hr4_write( HR4_I2C_ADDRESS, send_buffer, 2 );
}

// LIBRARY ROUTINES

void hr4_init() 
{ 
    hal_hr4_init();
    hal_delay( 100 );
    hr4_reset();
    hal_delay( 100 );
}

void hr4_set_registers() 
{
    // FIFO Configuration
    hr4_set_fifo_sample_averaging( 0x05 ); // 32 sample averaging
    hr4_fifo_rollover_enable( 1 );         // Allow FIFO to wrap/roll over
    hr4_proximity_int_enable( 1 );         // Enable Proximity Threshold Triggering
    hr4_set_mode( 0x02 );                  // Entering HR mode, RED LED only!
    hr4_set_spo2_sample_rate( 0x05 );      // 1000 sample rate

    // Enabling interrupt in case of new data arrival, and disable when near full
    hr4_new_fifo_data_int_enable( 1 ); 
    hr4_fifo_full_int_enable( 0 );

    // Setting LED Pulse Amplitudes
    hr4_set_red_led_pulse_amplitude( 0x1F );
    hr4_set_ir_led_pulse_amplitude( 0x1F );
    hr4_set_green_led_pulse_amplitude( 0x1F );
    hr4_set_proximity_led_pulse_amplitude( 0x0F );

    // Setting PROX THRESHOLD value to 31743 ( 0x01 is 1023)
    hr4_set_proximity_threshold( 0x1F ); 
}

void hr4_read_fifo_oldest_sample()
{
   
  uint8_t temp_red[ 4 ];
  
  
  uint8_t temp[ 9 ] = { 0 };
 
  temp[ 0 ] = 0x07;
  
  hal_hr4_read ( HR4_I2C_ADDRESS, &temp, 3 );
 
  temp_red[ 3 ] = 0;
  temp_red[ 2 ] = temp[ 0 ];
  temp_red[ 1 ] = temp[ 1 ];
  temp_red[ 0 ] = temp[ 2 ];

  // Convert array to uint32
  memcpy( &red_val, temp_red, 4 );
}

uint32_t hr4_read_red(void)
{
    uint8_t i = 0;
    uint8_t sampleNum = 0;
    uint8_t wrPtr = 0;
    uint8_t rdPtr = 0;
    uint8_t temp_red[ 4 ];
    uint8_t temp[ 3 ] = { 0 };

    red_average = 0;

    wrPtr = hr4_get_write_pointer();
    rdPtr = hr4_get_read_pointer();

    sampleNum = abs( 16 + wrPtr - rdPtr ) % 16;

    if ( sampleNum >= 1 )
    {
        for ( i = 0; i < sampleNum; ++i )
        {          
            hr4_read_reg_multi ( 0x07, &temp, 3 );
            
            temp_red[ 3 ] = 0;
            temp_red[ 2 ] = temp[ 0 ] & 0x03;
            temp_red[ 1 ] = temp[ 1 ];
            temp_red[ 0 ] = temp[ 2 ];

            // Convert array to uint32
            memcpy( &red_val, temp_red, 4 );
 
            red_average += red_val;
        }
        red_average /= sampleNum;
    }
    return red_average;
}



uint32_t hr4_get_red() 
{
    return red_val;
}

uint8_t hr4_get_part_id()
{
    uint8_t tempread = 0;

    tempread = hr4_read_reg( 0xFF );
    return tempread;
}

uint8_t hr4_is_fifo_full()
{
    uint8_t temp = 0;
    temp = hr4_read_reg( 0x00 );
    temp >>= 7;
    return temp;
}

uint8_t hr4_is_new_fifo_data_ready()
{
    uint8_t temp = 0;
    temp = hr4_read_reg( 0x00 );
    temp >>= 6;
    return temp;
}

uint8_t hr4_is_alc_overflow()
{
    uint8_t temp = 0;
    temp = hr4_read_reg(0x00);
    temp &= (1 << 5);
    temp >>= 5;
    return temp;
}

uint8_t hr4_is_proximity_int()
{
    uint8_t temp = 0;
    temp = hr4_read_reg(0x00);
    temp &= (1 << 4);
    temp >>= 4;
    return temp;
}

uint8_t hr4_is_powered_up()
{
    uint8_t temp = 0;
    temp = hr4_read_reg( 0x00 );
    temp &= 1;
    return temp;
}

uint8_t hr4_is_internal_temp_ready()
{
    uint8_t temp = 0;
    temp = hr4_read_reg( 0x01 );
    temp &= (1 << 1);
    temp >>= 1;
    return temp;
}

void hr4_fifo_full_int_enable( bool enable )
{
    uint8_t temp = 0;
    temp = hr4_read_reg( 0x02 );

    if (enable)
        temp |= (1 << 7);
    else
        temp &= ~(1 << 7);
    hr4_write_reg( 0x02, temp );
}

void hr4_new_fifo_data_int_enable( bool enable )
{
    uint8_t temp = 0;
    temp = hr4_read_reg( 0x02 );

    if (enable)
        temp |= (1 << 6);
    else
        temp &= ~(1 << 6);
    hr4_write_reg( 0x02, temp );
}

void hr4_alc_int_enable( bool enable )
{
    uint8_t temp = 0;
    temp = hr4_read_reg( 0x02 );

    if (enable)
        temp |= (1 << 5);
    else
        temp &= ~(1 << 5);
    hr4_write_reg( 0x02, temp );
}

void hr4_proximity_int_enable( bool enable )
{
    uint8_t temp = 0;
    temp = hr4_read_reg( 0x02 );

    if (enable)
        temp |= (1 << 4);
    else
        temp &= ~(1 << 4);
    hr4_write_reg( 0x02, temp );
}

void hr4_new_internal_temp_int_enable( bool enable )
{
    uint8_t temp = 0;
    temp = hr4_read_reg( 0x03 );

    if (enable)
        temp |= (1 << 1);
    else
        temp &= ~(1 << 1);
    hr4_write_reg( 0x02, temp );
}

uint16_t hr4_read_fifo_all_samples( uint8_t *buffer )
{
    uint8_t *temptr = buffer;
    uint16_t samples_to_read = 0;
    uint16_t fifo_readptr = 0;
    uint16_t fifo_writeptr = 0;
    uint16_t tempctr = 0;

    fifo_writeptr = hr4_read_reg( 0x04 );
    fifo_readptr = hr4_read_reg( 0x06 );
    samples_to_read = fifo_writeptr - fifo_readptr;

    for (tempctr = 0; tempctr < samples_to_read; tempctr++)
    {
        hr4_read_reg_multi( 0x07, temptr, 9 );
        temptr+= 9;
    }

    return samples_to_read;
}

int8_t hr4_set_fifo_sample_averaging( uint8_t sample_number )
{
    uint8_t temp = 0;
    if (sample_number > 7)
        return -1;

    temp = hr4_read_reg( 0x08 );
    temp |= sample_number << 5;
    hr4_write_reg( 0x08, temp );
    return 0;
}

void hr4_fifo_rollover_enable( bool enable )
{
    uint8_t temp = 0;
    temp = hr4_read_reg( 0x08 );
    if (enable)
        temp |= (1 << 4);

    else
        temp &= ~(1 << 4);

    hr4_write_reg( 0x08, temp );
}

int8_t hr4_set_fifo_almost_full_value( uint8_t full_value )
{
    uint8_t temp = 0;
    if (full_value > 15)
        return -1;

    temp = hr4_read_reg( 0x08 );
    temp |= full_value;
    hr4_write_reg( 0x08, temp );
    return 0;
}

void hr4_shut_down_enable( bool enable )
{
    uint8_t temp = 0;
    temp = hr4_read_reg( 0x09 );
    if (enable)
        temp |= (1 << 7);

    else
        temp &= ~(1 << 7);

    hr4_write_reg( 0x09, temp );

}

void hr4_reset()
{
    uint8_t temp = 0;
    temp = hr4_read_reg( 0x09 );
    temp |= (1 << 6);
    hr4_write_reg( 0x09, temp );
}

int8_t hr4_set_mode( uint8_t mode )
{
    uint8_t temp = 0;
    if ((mode > 7) || (mode == 0) || (mode == 1) || (mode == 4) || (mode == 5) || (mode == 6))
        return -1;

    temp |= mode;
    hr4_write_reg( 0x09, temp );
    return 0;
}

int8_t hr4_set_spo2_range( uint8_t range )
{
    uint8_t temp = 0;
    if (range > 3)
        return -1;

    temp = hr4_read_reg( 0x0A );
    temp |= range << 5;
    hr4_write_reg( 0x0A, temp );
    return 0;
}

int8_t hr4_set_spo2_sample_rate( uint8_t rate )
{
    uint8_t temp = 0;
    if (rate > 7)
        return -1;

    temp = hr4_read_reg( 0x0A );
    temp |= rate << 2;
    hr4_write_reg( 0x0A, temp );
    return 0;
}

int8_t hr4_set_led_pulse_width( uint8_t pulse_width )
{
    uint8_t temp = 0;
    if (pulse_width > 3)
        return -1;

    temp = hr4_read_reg( 0x0A );
    temp |= pulse_width;
    hr4_write_reg( 0x0A, temp );
    return 0;
}

 void hr4_set_red_led_pulse_amplitude( uint8_t amplitude )
 {
     hr4_write_reg( 0x0C, amplitude );
 }

 void hr4_set_ir_led_pulse_amplitude( uint8_t amplitude )
 {
     hr4_write_reg( 0x0D, amplitude );
 }
 
 void hr4_set_green_led_pulse_amplitude( uint8_t amplitude )
 {
     hr4_write_reg( 0x0E, amplitude );
 }

 void hr4_set_proximity_led_pulse_amplitude( uint8_t amplitude )
 {
     hr4_write_reg( 0x10, amplitude );
 }

int16_t hr4_get_temperature()
{
    uint8_t temp_en_read = 0;
    uint8_t tempread[ 2 ];
    uint16_t temperature = 0;
    tempread[0] = 0x1F;

    temp_en_read = hr4_read_reg( 0x21 );
    temp_en_read |= 1;
    hr4_write_reg( 0x21, temp_en_read );
    hal_hr4_read( HR4_I2C_ADDRESS, tempread, 2 );
    temperature = tempread[0] + tempread[1];
    return temperature;
}

void hr4_set_proximity_threshold( uint8_t threshold )
{
    hr4_write_reg( 0x30, threshold );
}

uint8_t hr4_get_write_pointer( void )
{
    return hr4_read_reg( 0x04 );
}

uint8_t hr4_get_read_pointer( void )
{
    return hr4_read_reg( 0x06 );
}