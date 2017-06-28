/*
 * thermo_4_click.c
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * 0.0.1 (Jan/2017) Module created                          __________________
 *
 * To Do List :
 *
 ******************************************************************************/



#include "thermo_4_Click.h"
#include "thermo_4_Click_hal.h"

/*                 Preprocessors
 ******************************************************************************/



/*                Typedefs
 ******************************************************************************/



/*                Variables
 ******************************************************************************/


extern sfr sbit Thermo_OS;

/*                 Private Function Prototypes
 ******************************************************************************/
static uint8_t _thermo_read_config ( uint8_t reg, uint8_t *output );
static uint8_t _thermo_read(  uint8_t reg, uint16_t *output );
static uint8_t _thermo_write_config( uint8_t reg, uint8_t wr_data);
static uint8_t _thermo_write( uint8_t reg, uint16_t wr_data);
static void _thermo_temp_tostring (uint16_t input, char output [15]);
static void _thermo_string_trim (char *output);
static uint8_t thermo_output_signal( void );
static uint8_t thermo_two_bits_config (uint8_t _value, uint8_t config);
/*                 Private Function Definitions
 ******************************************************************************/

/*For writing into config register*/
static uint8_t _thermo_read_config ( uint8_t reg, uint8_t *output )
{
    uint8_t *out = output;
    *out = reg;
    hal_thermo_read( _i2c_hw_address, out ,1 );
    return THERMO_CLICK_OK;
}

/*For reading from temperature registers*/
static uint8_t _thermo_read( uint8_t reg, uint16_t *output )
{
    uint16_t *out = output;
    *out = reg;
    hal_thermo_read( _i2c_hw_address, out ,2 );
    return THERMO_CLICK_OK;
}

/*For writing into config register*/
static uint8_t _thermo_write_config( uint8_t reg, uint8_t wr_data)
{
        uint8_t input[ 2 ];
        input[ 0 ] = reg;
        input[ 1 ] = wr_data;
        hal_thermo_write( _i2c_hw_address, input, 2 );
        return THERMO_CLICK_OK;
}

/*For writing into temperature registers*/
static uint8_t _thermo_write( uint8_t reg, uint8_t wr_data1, uint8_t wr_data2)
{
        uint8_t input[ 3 ];
        input[ 0 ] = reg;
        input[ 1 ] = wr_data1;
        input[ 2 ] = wr_data2;
        hal_thermo_write( _i2c_hw_address, input, 3 );
        return THERMO_CLICK_OK;
}

/*Converts a 16bit temperature value into a string (format "x.y")*/
static void _thermo_temp_tostring (uint16_t input, char *output)
{       
         uint8_t _value [ 2 ];
         char *ptr = output;
         memset( ptr, 0, 15);
         _value[ 0 ] =  input & 0x00FF;         /*value before decimal point*/
         _value[ 1 ] = (input & 0xFF00) >> 8;   /*value after decimal point*/
         
         ShortToStr (_value [0], ptr);
         _thermo_string_trim (ptr);
         ptr = strcat (ptr, ".");
        
         if (_value[ 1 ] >= 0x80)
              ptr = strcat (ptr, "5");
         else ptr = strcat (ptr, "0");

}


float _thermo_temp_tofh (uint16_t input)
{
         uint8_t _value [ 2 ];
         float _res = 0;
         
         _value[ 0 ] =  input & 0x00FF;         /*value before decimal point*/
         _value[ 1 ] = (input & 0xFF00) >> 8;   /*value after decimal point*/

         _res = _value [0] * 1.8 + 32;

         if (_value[ 1 ] >= 0x80)
              _res += 0.9;

         return _res;
}


/*removes empty space from the beginning of the string*/
static void _thermo_string_trim (char *output)
{
      int i;
      while (output[0] == 0x20)
      {
          i = 1;
          while (output [i] != 0)
          {
              output [i-1] = output [i];
              i++;
          }
          output [i-1] = output [i];
      }

}


static uint8_t thermo_output_signal( void )
{
    return Thermo_OS;
}

/*
 * Inline function to simplify fever_config.
 * Only used when writing 2 bits into configuration register.
 */
static uint8_t thermo_two_bits_write (uint8_t _value, uint8_t config)
{
       if (_value == 0x08)            /*setting 5th bit to 0, and 4th to 1*/
       {
          if (config & 0x10)
          {
              config = config | _value;
              config -= 0x10;
          }
          else  config = config | _value;
       }
       else if (_value == 0x10)      /*setting 4th bit to 0, and 5th to 1*/
       {
          if (config & 0x08)
          {
              config = config | _value;
              config -= 0x08;
          }
          else  config = config | _value;
       }
       return config;
}

/*                Public Function Definitions
 ******************************************************************************/



uint16_t thermo_init(uint8_t i2c_address )
{
     return hal_thermo_init( i2c_address);
}


void thermo_config(uint8_t _value)
{
     short config;
     _thermo_read_config(THERMO_CONFIG, &config);
    
     /*two cases where 2 bits need to be set at once */
     if (_value == 0x08 || _value == 0x10)
         config = thermo_two_bits_write (_value, config);
     /*one of the bits is to be set to 0*/
     else if (_value > 0x80 || _value == 0x7F)
        config = config & _value;
     /*one of the bits is to be set to 1*/
     else config = config | _value;
     
    _thermo_write_config ( THERMO_CONFIG, config);
}


void thermo_read_temperature_text ( char *output, uint8_t _location )
{       
        uint16_t _value;
        char *ptr = output;
        _thermo_read ( _location, &_value);
        _thermo_temp_tostring (_value, ptr);
}

float thermo_read_temperature_fh ( uint8_t _location )
{
        uint16_t _value;
        float _res = 0;
        _thermo_read ( _location, &_value);
        return _thermo_temp_tofh (_value);
}

uint16_t thermo_read_temperature_binary( uint8_t _location )
{
        uint16_t res;
        _thermo_read( _location, &res );
        return res;
}

void thermo_write_temperature ( float _value, uint8_t _location )
{

        uint8_t _value_dec;
        float _value_fract;
        uint8_t _binary_fract;
        
        if (_location ==  0x00)    /*Register 0x00 is read-only*/
             return;
        
        _value_dec = _value;
        /* Will round any fraction down to 0 or 0.5 */
        _value_fract = _value - _value_dec;
        if (_value_fract >= 0.5)
           _binary_fract = 0x80;
        else _binary_fract = 0x00;

        _thermo_write (_location, _value_dec, _binary_fract);
}


/*                                                                 End of File
 ******************************************************************************/