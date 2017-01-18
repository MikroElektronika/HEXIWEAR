/****************************************************************************
* Title                 :   BUZZ click
* Filename              :   BUZZ.c
* Author                :   UC
* Origin Date           :   20/04/2016
* Notes                 :   BUZZ Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  20/04/16       1.0.0            UC        Interface Created.
*
*****************************************************************************/
/**
 * @file BUZZ.c
 * @brief <h2> BUZZ Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * BUZZ click board.
 */

/**
 * @page LIB_INFO Library Info
 * @date        20 Apr 2016
 * @author      Uros Cvetinovic
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

 /**
 * @page Test Configuration
 * <h3> Test configuration : </h3>
 * @par
 * <ul>
 * <li><b> MCU           </b> :      MK64FN1M0XXX12              </li>
 * <li><b> Dev. Board    </b> :      HEXIWEAR                    </li>
 * <li><b> Oscillator    </b> :      12 MHz external             </li>
 * <li><b> Ext. Modules  </b> :      BUZZ Click                 </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1    </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> BUZZ click example using HEXIWEAR </h3>
 * @par Place BUZZ Click into the mikroBUS socket 3 on the docking station.
 * Press bottom-left button on hexiwear for playing a melody
 *
 * <h3> BUZZ Features </h3>
 * @par BUZZ click, Hexiwear Docking Station
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>
#include <BUZZ.h>
#include "OLED_driver.h"
#include "common_screen_objects.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define true 1
#define false 0
#define bool UINT8_t
#define gHostInterface_startByte1               0x55
#define gHostInterface_startByte2               0xAA
#define gHostInterface_trailerByte              0x45

#define gHostInterface_dataSize                 23
#define gHostInterface_headerSize               4

#define UART4_C2_REG *( (unsigned char*)(0x400EA003) )
#define UART4_S1_REG *( (unsigned char*)(0x400EA004) )

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/
#define data __data
#define KW40_RST_SET()   PTB_PSOR.B23 = 1
#define KW40_RST_CLEAR() PTB_PCOR.B23 = 1

/******************************************************************************
* Module Typedefs
*******************************************************************************/
typedef enum
{
    touch_left  = 0,
    touch_right = 1,
    touch_invalid = 0xFF

} touch_type_t;

/**
 * @enum Packet definitions
 *
 * Types of packets exchanged.
 */
typedef enum
{
    packetType_pressUp          = 0, /**< Press up event */
    packetType_pressDown        = 1,
    packetType_pressLeft        = 2,
    packetType_pressRight       = 3,
    packetType_slide            = 4,
} hostInterface_packetType_t;

typedef struct
{
    // NOTE: Size of struct must be multiplier of 4 !
    uint8_t start1;
    uint8_t start2;
    hostInterface_packetType_t type;
    uint8_t length;
    uint8_t data[gHostInterface_dataSize + 1];

} hostInterface_packet_t;

typedef enum
{
    hostInterface_rxState_idle           = 0,
    hostInterface_rxState_headerReceived = 3,
    hostInterface_rxState_dataWait       = 4,
    hostInterface_rxState_trailerWait    = 5

} hostInterface_rxState_t;

int cntr;

bit playing;

bit STOPED;

const STOP_PLAYING = 1;

sbit KW40_RST at PTB_PDOR.B23;

static touch_type_t pressedTouch = touch_invalid;

static hostInterface_packet_t hostInterface_rxPacket;

uint8_t * pktBuf = ( uint8_t * ) &hostInterface_rxPacket;

static hostInterface_rxState_t hostInterface_rxState = hostInterface_rxState_idle;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void PacketParser();
char play(long int freq, int ddd);
void play_melody();
/******************************************************************************
* Private Function Definitions
*******************************************************************************/
/**
 * @brief <h3> Packet parser for handling data-packets received from KW40 </h3>
 */
static void PacketParser()
{
    static uint8_t byteCount;

    switch ( hostInterface_rxState )
    {
        case hostInterface_rxState_idle:
        {
            if ( gHostInterface_startByte1 == hostInterface_rxPacket.start1 )
            {
                hostInterface_rxState++;
                pktBuf++;
            }

            break;
        }

        case hostInterface_rxState_headerReceived:
        {
            if  (
                ( gHostInterface_startByte1 != hostInterface_rxPacket.start1 )
                ||     ( gHostInterface_startByte2 != ( hostInterface_rxPacket.start2 &
                         0xFE ) )
                || ( hostInterface_rxPacket.length >  gHostInterface_dataSize )
            )
            {
                // return to idle state
                hostInterface_rxState = hostInterface_rxState_idle;
                // reset the RX buffer pointer
                pktBuf = ( uint8_t * )&hostInterface_rxPacket;
            }

            else
            {
                // advance the buffer pointer
                pktBuf++;

                if ( 0 == hostInterface_rxPacket.length )
                {
                    // advance to "wait-trailer-bit" state
                    hostInterface_rxState = hostInterface_rxState_trailerWait;
                }

                else
                {
                    byteCount = 0;
                    // advance to "data-wait" state
                    hostInterface_rxState = hostInterface_rxState_dataWait;
                }
            }

            break;
        }

        case hostInterface_rxState_dataWait:
        {
            byteCount++;
            pktBuf++;

            // if we reached the byte-count
            if  ( hostInterface_rxPacket.length == byteCount )
            {
                // advance to "wait-trailer-bit" state
                hostInterface_rxState = hostInterface_rxState_trailerWait;
            }

            break;
        }

        case hostInterface_rxState_trailerWait:
        {
            if ( gHostInterface_trailerByte == *pktBuf )
            {
                switch ( hostInterface_rxPacket.type )
                {
                    case packetType_pressRight:
                    {
                        pressedTouch = touch_right;
                        break;
                    }
                    case packetType_pressLeft:
                    {
                        pressedTouch = touch_left;
                        break;
                    }
                    default:
                    {
                        pressedTouch = touch_invalid;
                    }
                }
            }

            // go back to the idle state
            hostInterface_rxState = hostInterface_rxState_idle;
            // reset the RX buffer pointer
            pktBuf = ( uint8_t * )&hostInterface_rxPacket;
            break;
        }

        default:
        {
            hostInterface_rxState++;
            pktBuf++;
        }
    }
}

/******************************************************************************
* Public Function Definitions
*******************************************************************************/




char play(long int freq, int delay_in_miliseconds){
int i, r=0;

PWM_FTM0_Init(freq,_PWM_EDGE_ALIGNED_PWM, _PWM_CHANNEL_1, &_GPIO_Module_PWM0_PTA4);
PWM_FTM0_Set_Duty(5,_PWM_NON_INVERTED,1);
for(i=0; i < delay_in_miliseconds; i++){
  if (STOPED) {
    r = STOP_PLAYING;
    return r;
    break;
    }
 delay_ms(1);
 }
 PWM_FTM0_Stop(1);
 return r;
}


void play_melody(){
while(1){
  if (play(220,QUARTER_NOTE) == STOP_PLAYING)
    break;
  Delay_ms(1+QUARTER_NOTE);
  if (play(220,QUARTER_NOTE) == STOP_PLAYING)
    break;
  Delay_ms(1+QUARTER_NOTE);
  if (play(220,QUARTER_NOTE) == STOP_PLAYING)
    break;
  Delay_ms(1+QUARTER_NOTE);
  if (play(F3,E+S) == STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(C4,S) == STOP_PLAYING)
    break;
  Delay_ms(1+S);

  if (play(LA3,QUARTER_NOTE)== STOP_PLAYING)
    break;
  Delay_ms(1+QUARTER_NOTE);
  if (play(F3,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(C4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(LA3,H)== STOP_PLAYING)
    break;
  Delay_ms(1+H);

  if (play(E4,QUARTER_NOTE)== STOP_PLAYING)
    break;
  Delay_ms(1+QUARTER_NOTE);
  if (play(E4,QUARTER_NOTE)== STOP_PLAYING)
    break;
  Delay_ms(1+QUARTER_NOTE);
  if (play(E4,QUARTER_NOTE)== STOP_PLAYING)
    break;
  Delay_ms(1+QUARTER_NOTE);
  if (play(F4,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(C4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);

  if (play(Ab3,QUARTER_NOTE)== STOP_PLAYING)
    break;
  Delay_ms(1+QUARTER_NOTE);
  if (play(F3,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(C4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(LA3,H)== STOP_PLAYING)
    break;
  Delay_ms(1+H);

  if (play(LA4,QUARTER_NOTE)== STOP_PLAYING)
    break;
  Delay_ms(1+QUARTER_NOTE);
  if (play(LA3,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(LA3,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(LA4,QUARTER_NOTE)== STOP_PLAYING)
    break;
  Delay_ms(1+QUARTER_NOTE);
  if (play(Ab4,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(G4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);

  if (play(Gb4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(E4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(F4,E)== STOP_PLAYING)
    break;
  Delay_ms(1+E);
  Delay_ms(1+E);
  if (play(Bb3,E)== STOP_PLAYING)
    break;
  Delay_ms(1+E);
  if (play(Eb4,QUARTER_NOTE)== STOP_PLAYING)
    break;
  Delay_ms(1+QUARTER_NOTE);
  if (play(D4,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(Db4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);

  if (play(C4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(B3,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(C4,E)== STOP_PLAYING)
    break;
  Delay_ms(1+E);
  Delay_ms(1+E);
  if (play(F3,E)== STOP_PLAYING)
    break;
  Delay_ms(1+E);
  if (play(Ab3,QUARTER_NOTE)== STOP_PLAYING)
    break;
  Delay_ms(1+Q);
  if (play(F3,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(LA3,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);

  if (play(C4,Q)== STOP_PLAYING)
    break;
  Delay_ms(1+Q);
  if (play(LA3,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(C4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(E4,H)== STOP_PLAYING)
    break;
  Delay_ms(1+H);

  if (play(LA4,Q)== STOP_PLAYING)
    break;
  Delay_ms(1+Q);
  if (play(LA3,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(LA3,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(LA4,Q)== STOP_PLAYING)
    break;
  Delay_ms(1+Q);
  if (play(Ab4,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(G4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);

  if (play(Gb4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(E4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(F4,E)== STOP_PLAYING)
    break;
  Delay_ms(1+E);
  Delay_ms(1+E);
  if (play(Bb3,E)== STOP_PLAYING)
    break;
  Delay_ms(1+E);
  if (play(Eb4,Q)== STOP_PLAYING)
    break;
  Delay_ms(1+Q);
  if (play(D4,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(Db4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);

  if (play(C4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(B3,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(C4,E)== STOP_PLAYING)
    break;
  Delay_ms(1+E);
  Delay_ms(1+E);
  if (play(F3,E)== STOP_PLAYING)
    break;
  Delay_ms(1+E);
  if (play(Ab3,Q)== STOP_PLAYING)
    break;
  Delay_ms(1+Q);
  if (play(F3,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(C4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);

  if (play(LA3,Q)== STOP_PLAYING)
    break;
  Delay_ms(1+Q);
  if (play(F3,E+S)== STOP_PLAYING)
    break;
  Delay_ms(1+E+S);
  if (play(C4,S)== STOP_PLAYING)
    break;
  Delay_ms(1+S);
  if (play(LA3,H)== STOP_PLAYING)
    break;
  Delay_ms(1+H);

  Delay_ms(2*H);
  }
}



int main(void)
{
cntr = 0;
OLED_Init();
OLED_DrawImage( BUZZ_bmp, 0, 0 );

// set KW40_RST as digital output
GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_23 );

// initialize UART to KW40
UART4_Init_Advanced( 230400, _UART_8_BIT_DATA, _UART_NOPARITY, _UART_TWO_STOPBITS,  &_GPIO_Module_UART4_PE24_25 );

EnableInterrupts();
NVIC_IntEnable( IVT_INT_UART4_RX_TX );

UART4_C2_REG |= 1 << 5;

// Reset KW40
KW40_RST_CLEAR();
Delay_ms( 10 );
KW40_RST_SET();
Delay_ms( 200 );
 while ( 1 )
 {

  

    if ( touch_invalid != pressedTouch )
        {
            switch ( pressedTouch )
            {
                case touch_left:
                {
                    playing = 1;
                    play_melody();
                    break;
                 }
             }
         }
 }
}



void IRQ_Uart4Handler() iv IVT_INT_UART4_RX_TX ics ICS_AUTO
{
    // read status register
    volatile uint8_t foo = UART4_S1;
    uint8_t readData = UART4_D;
    *pktBuf = readData;

    PacketParser();
    if(cntr != 0)
      if ( touch_invalid != pressedTouch )
        {
            switch ( pressedTouch )
            {
                case touch_left:
                {
                 if(playing)
                  {
                   STOPED = ~STOPED;
                   if(cntr == 50)
                   cntr = 1;
                   }

                 }
             }
         }
      cntr++;
}