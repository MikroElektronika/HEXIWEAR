/****************************************************************************
* Title                 :   eight_b CLICK
* Filename              :   eight_b_hw.h
* Author                :   CAL
* Origin Date           :   03/29/2016
* Notes                 :   Hardware layer
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials      Description
*  03/29/2016     .1                CAL     Interface Created.
*
*****************************************************************************/
/**
 * @file eight_b_hw.c
 * @brief <h3> Hardware Layer </h3>
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "eight_x_eight_hw.h"
#include "eight_x_eight_hal.h"
#include "eight_x_eight_font.h"
#include "stddef.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
/**
  Instructions
*/

#define NOP         0x00

#define DIGITS
#define DIGIT_0     0X01
#define DIGIT_1     0X02
#define DIGIT_2     0X03
#define DIGIT_3     0X04
#define DIGIT_4     0X05
#define DIGIT_5     0X06
#define DIGIT_6     0X07
#define DIGIT_7     0X08

#define DEC_MODE    0x09
#define DEC_NONE    0x00
#define DEC_DG1     0x01
#define DEC_DG3_0   0x0F
#define DEC_DG7_0   0xFF

#define INTNS       0x0A
#define INTNS_1     0x00
#define INTNS_3     0x01
#define INTNS_5     0x02
#define INTNS_7     0x03
#define INTNS_9     0x04
#define INTNS_11    0x05
#define INTNS_13    0x06
#define INTNS_15    0x07
#define INTNS_17    0x08
#define INTNS_19    0x09
#define INTNS_21    0x0A
#define INTNS_23    0x0B
#define INTNS_25    0x0C
#define INTNS_27    0x0D
#define INTNS_29    0x0E
#define INTNS_31    0x0F

#define SCN_LMT     0x0B
#define SCN_0       0x00
#define SCN_1       0x01
#define SCN_2       0x02
#define SCN_3       0x03
#define SCN_4       0x04
#define SCN_5       0x05
#define SCN_6       0x06
#define SCN_7       0x07

#define SHUT_DOWN   0x0C
#define SHUT_DOWN_D 0x00
#define SHUT_DOWN_N 0x01

#define DISP_TEST   0x0F


/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static uint8_t frame_buffer[8];

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Private Function Definitions
*******************************************************************************/
static refresh( void );
static scroll_refresh( void );
static uint8_t led_eight_reverse_byte( uint8_t b );
/******************************************************************************
* Public Function Definitions
*******************************************************************************/
static refresh()
{
    int i,j,k,m;
    uint8_t buffer[2];
    uint8_t result = 0;
    uint8_t *ptr = frame_buffer;

    for( i = 7, j = 0; i >= 0; i--, j++ )
    {
         for( k = 7, m = 7; k >= 0; k--, m--)
         {
             result |=  ( ptr[7 - k] & ( 1 << j  ) ) >> j << k; //Rotate 270 deg
         }

         buffer[0] = j + 1;
         buffer[1] = result;
         led_eight_hal_write( buffer );
         result = 0;
    }

    return;
}

static scroll_refresh()
{
    int i,j,k,m;
    uint8_t buffer[2];
    uint8_t result = 0;
    uint8_t *ptr = frame_buffer;

    for( i = 7, j = 0; i >= 0; i--, j++ )
    {
         for( k = 7, m = 7; k >= 0; k--, m--)
         {
             result |=  ( ptr[7 - k] & ( 1 << j  ) ) >> j << k; //Rotate 270 deg
         }
         //buffer[0] = j + 1;
         result = led_eight_reverse_byte( result );  //Reverse bits on each digit
         
         buffer[0] = j + 1;
         buffer[1] = result;
         led_eight_hal_write( buffer );
         result = 0;
    }

    return;
}

static uint8_t led_eight_reverse_byte( uint8_t b )
{
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

void led_eight_init()
{
     uint8_t buffer[2];
     led_eight_hal_init();

     buffer[0] = DEC_MODE;          //Decode mode set to No Decoding
     buffer[1] = DEC_NONE;
     led_eight_hal_write( buffer );

     buffer[0] = SCN_LMT;           //Scan Limit set to all ( show all leds )
     buffer[1] = SCN_7;
     led_eight_hal_write( buffer );

     buffer[0] = INTNS;             //Intensity set to max on init
     buffer[1] = INTNS_31;
     led_eight_hal_write( buffer );

     buffer[0] = DISP_TEST;         //Display Test set to Off
     buffer[1] = 0x00;
     led_eight_hal_write( buffer );

     buffer[0] = SHUT_DOWN;         //ShutDown Mode set to Normal Operation
     buffer[1] = SHUT_DOWN_N;
     led_eight_hal_write( buffer );

    return;
}


void led_eight_display_one_col( uint8_t row, uint8_t col )
{
    uint8_t buffer[2];
    buffer[0] = 8 - row;
    buffer[1] = col;
    led_eight_hal_write( buffer );

    return;
}

void led_eight_display_image( uint8_t* image )
{
   int i;

   if( image == NULL )
       return;

   for( i = 0; i <=7; i++ )
   {
        frame_buffer[i] = image[i];
   }
   refresh();

   return;
}

void led_eight_display_const_image( const uint8_t* image )
{
   int i;

   if( image == NULL )
       return;

   for( i = 0; i <=7; i++ )
   {
        frame_buffer[i] = image[i];
   }
   refresh();

   return;
}

void led_eight_display_string( uint8_t* str, uint8_t delay )
{
      uint8_t *ptr = str;
      int i;
      
      if( ptr == NULL )
          return;

      while( *ptr != NULL )
      {
          for( i = 0; i < 8; i++ )
               frame_buffer[i] = font[( *ptr * 8 ) + i];
          
          refresh();
          vDelay_ms( delay );
          ptr++;
      }
}

void led_eight_scroll_text( uint8_t* str, uint8_t delay)
{
      uint8_t *ptr = str;          //Holds Pointer
      uint8_t *p_font = 0;
      int i, j, k, m;
      
      memset( frame_buffer, 0, sizeof(frame_buffer) );
      
      if( ptr == NULL )           //Sanity Check
          return;
          
      p_font = font[*ptr];
      
      while( *ptr != NULL )
      {
          for( i = 0, m = 8; i < 8; i++, m-- )
          {
              for( j = 0, k = 8; j < 8; j++, k-- )
              {
                  frame_buffer[j] <<= 1;
                  frame_buffer[j] |=  ( font[( *ptr * 8) + m ] & ( 1 << j) ) >> j;
                  scroll_refresh();
                  vDelay_ms( delay );
              }
              p_font++;
          }
          ptr++;
      }
      
}

void led_eight_display_shift_left()
{
     int i, j;
     uint8_t temp_buffer[8];
     
     for( i = 0; i < 8; i++ )
     {
         temp_buffer[i] = frame_buffer[i];
     }
     for( j = 7; j > 0; j-- )
     {
         frame_buffer[j] = temp_buffer[ j - 1 ];
     }
     refresh();
     
     return;

}

void led_eight_set_intensity( uint8_t intensity )
{
    uint8_t buffer[2];

     if( intensity > 15 || intensity < 0 )
         return;

     buffer[0] = INTNS;
     buffer[1] = intensity;
     led_eight_hal_write( buffer );

     return;
}

void led_eight_set_scan_limit( uint8_t scan_limit )
{
     uint8_t buffer[2];

     if( scan_limit > 7 || scan_limit < 0 )
         return;

     buffer[0] = SCN_LMT;
     buffer[1] = scan_limit;
     led_eight_hal_write( buffer );

     return;
}

void led_eight_shut_down( void )
{
     uint8_t buffer[2];

     buffer[0] = SHUT_DOWN;
     buffer[1] = SHUT_DOWN_D;
     led_eight_hal_write( buffer );

     return;
}

void led_eight_display_test( void )
{
     uint8_t buffer[2];

     buffer[0] = DISP_TEST;
     buffer[1] = 0x01;
     led_eight_hal_write( buffer );

     return;
}

/*************** END OF FUNCTIONS *********************************************/