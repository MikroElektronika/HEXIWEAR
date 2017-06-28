/*
 * mic_24045_4_click.c
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * 0.0.1 (Jan/2017) Module created                          __________________
 *
 * To Do List :
 *
 ******************************************************************************/


#include "mic_24045_Click.h"
#include "mic_24045_Click_hal.h"

/*                 Preprocessors
 ******************************************************************************/



/*                Typedefs
 ******************************************************************************/



/*                Variables
 ******************************************************************************/


/*                 Private Function Prototypes
 ******************************************************************************/

static uint16_t _mic_24045_read(  uint8_t reg, uint8_t *output );
static uint16_t _mic_24045_write( uint8_t reg, uint8_t wr_data);
static float _mic_24045_bit2float (uint8_t _value);
static uint8_t _mic_24045_float2bit (float vout);
/*                 Private Function Definitions
 ******************************************************************************/

/*For reading from a register*/
static uint16_t _mic_24045_read ( uint8_t reg, uint8_t *output )
{
    uint8_t *out = output;
    *out = reg;
    hal_read( _i2c_hw_address, out ,1 );
    return MIC24045_CLICK_OK;
}

/*For writing into a register*/
static uint16_t _mic_24045_write ( uint8_t reg, uint8_t wr_data)
{
        uint8_t input[ 2 ];
        input[ 0 ] = reg;
        input[ 1 ] = wr_data;
        hal_write( _i2c_hw_address, input, 2 );
        return MIC24045_CLICK_OK;
}
/*Converts voltage into its 8bit representation*/
static uint8_t _mic_24045_float2bit (float vout)
{
       uint8_t _value = 0;
       if (vout >= 5.250)
       {
          _value = 0xff;
          return _value;
       }
       else if (vout >= 4.750)
       {
            _value = 0xf5;
            while (vout > 4.750)
            {
                 _value++;
                 vout -= 0.05;
            }
            return _value;
       }
       else if (vout >= 3.420)
       {
            _value = 0xf4;
            return _value;
       }
       else if (vout >= 1.980)
       {
            _value = 0xc4;
            while (vout > 1.980)
            {
                 _value++;
                 vout -= 0.03;
            }
            return _value;
       }
       else if (vout >= 1.290)
       {
             _value = 0x81;
            while (vout > 1.290)
            {
                 _value++;
                 vout -= 0.01;
            }
            return _value;
       }
       else if (vout >= 0.640)
       {
            _value = 0x00;
            while (vout > 0.640)
            {
                 _value++;
                 vout -= 0.005;
            }
            return _value;
       }
       else  _value = 0x00;
       return _value;
}
/*Converts 8bit representation into voltage*/
static float _mic_24045_bit2float (uint8_t _value)
{
       float _retval = 0;
       if (_value >= 0 && _value <= 0x80)
       {
            _retval = 0.640;
            while (_value > 0)
            {
               _retval += 0.005;
               _value --;
            } 
            return _retval;
       }
       else if (_value >= 0x81 && _value <= 0xC3)
       {
            _retval = 1.290;
            while (_value > 0x81)
            {
               _retval += 0.010;
               _value --;
            }
            return _retval;
       }
       else if (_value >= 0xC4 && _value <= 0xF4)
       {
            _retval = 1.980;
            while (_value > 0xC4)
            {
               _retval += 0.030;
               _value --;
            }
            return _retval;
       }
       else if (_value >= 0xF5 && _value <= 0xFF)
       {
            _retval = 4.750;
            while (_value > 0xF5)
            {
               _retval += 0.050;
               _value --;
            }
            return _retval;
       }
       return _retval;

}


/*                Public Function Definitions
 ******************************************************************************/


uint16_t mic_24045_init (uint8_t i2c_address )
{
     return hal_init( i2c_address);
}

bool mic_24045_status (uint8_t cmd)
{
     uint8_t _value = 0;
     _mic_24045_read (MIC24045_STATUS, &_value);
     if (cmd & _value)
        return true;
     else return false;
}

void mic_24045_clear_flags ()
{
     _mic_24045_write (MIC24045_COMMAND, MIC24045_CIFF);
}


float mic_24045_read_vout ()
{
     uint8_t _value = 0;
     _mic_24045_read (MIC24045_VOUT, &_value);
     return _mic_24045_bit2float (_value);
}
void mic_24045_write_vout (float vout)
{
     uint8_t _value = 0;
     _value = _mic_24045_float2bit (vout);
     _mic_24045_write (MIC24045_VOUT, _value);
}



uint8_t mic_24045_read_settings (uint8_t reg)
{
     uint8_t _value = 0;
     _mic_24045_read (reg, &_value);
     return _value;
}
void mic_24045_write_settings (uint8_t reg, uint8_t set)
{
     _mic_24045_write (reg, set);
}


/*                                                                 End of File
 ******************************************************************************/