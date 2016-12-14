/****************************************************************************
* Title                 :   Relay click
* Filename              :   Relay.c
* Author                :   ML
* Origin Date           :   14/04/2016
* Notes                 :   Relay Example
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials       Description
*  14/04/16       1.0.0          ML             Functional example finished.
*
*****************************************************************************/
/**
 * @file Relay.c
 * @brief <h2> Relay Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * Relay click board.
 */

/**
 * @page Example Info
 * @date        14 Apr 2016
 * @author      Marko Lainovic
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
 * <li><b> Ext. Modules  </b> :      Relay Click                 </li>
 * <li><b> SW            </b> :      MikroC PRO for ARM 4.7.1    </li>
 * </ul>
 */

/**
 * @mainpage
 * <h3> Relay click example using HEXIWEAR </h3>
 * @par Place Relay Click into the mikroBUS socket 1 on docking station.
 * Press the right touch on HEXIWEAR and it toggles the right output on Relay Click.
 * Press the left touch on HEXIWEAR and it toggles the left output on Relay Click.
 *
 * <h3> Relay Features </h3>
 * @par Relay click, Hexiwear docking station
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "OLED_driver.h"

/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
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

#define TOGGLE_RELAY1() PTC_PTOR.B4  = 1
#define TOGGLE_RELAY2() PTA_PTOR.B10 = 1

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

    // Battery Service
    packetType_batteryLevel     = 5,

    packetType_accel            = 6, /**< motion service */
    packetType_ambiLight        = 7, /**< weather service */
    packetType_pressure         = 8, /**< weather service */


    packetType_gyro             = 9,  /**< motion service */
    packetType_temperature      = 10, /**< weather service */
    packetType_humidity         = 11, /**< weather service */
    packetType_magnet           = 12, /**< motion service */

    packetType_heartRate        = 13, /**< health service */
    packetType_steps            = 14, /**< health service */
    packetType_calories         = 15, /**< health service */

    // Alert Service
    packetType_alertIn          = 16,
    packetType_alertOut         = 17,

    // Type for password confirmation
    packetType_passDisplay      = 18,

    // Types for OTAP
    packetType_otapKW40Started  = 19,
    packetType_otapMK64Started  = 20,
    packetType_otapCompleted    = 21,
    packetType_otapFailed       = 22,

    // Active slider
    packetType_buttonsGroupToggleActive = 23,
    packetType_buttonsGroupGetActive    = 24,
    packetType_buttonsGroupSendActive   = 25,

    // Turn off/on bluetooth advertising
    packetType_advModeGet    = 26,
    packetType_advModeSend   = 27,
    packetType_advModeToggle = 28,

    // App Mode Service
    packetType_appMode       = 29,

    // Link state (connected / disconnected)
    packetType_linkStateGet  = 30,
    packetType_linkStateSend = 31,

    // Notifications
    packetType_notification  = 32,

    // Build version
    packetType_buildVersion = 33,

    // SLEEP ON
    packetType_sleepON = 34,

    // SLEEP OFF
    packetType_sleepOFF = 35,

    // OK Packet
    packetType_OK = 255

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

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
sbit relay1 at PTC_PDOR.B4;
sbit relay2 at PTA_PDOR.B10;
sbit KW40_RST at PTB_PDOR.B23;

static touch_type_t pressedTouch = touch_invalid;

static hostInterface_packet_t hostInterface_rxPacket;

uint8_t * pktBuf = ( uint8_t * ) &hostInterface_rxPacket;

static hostInterface_rxState_t hostInterface_rxState = hostInterface_rxState_idle;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void PacketParser();

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
/**
 * @brief <h3> UART4 IRQ handler for handling communication with KW40 </h3>
 */
void IRQ_Uart4Handler() iv IVT_INT_UART4_RX_TX ics ICS_AUTO
{
    // read status register
    volatile uint8_t foo = UART4_S1;
    uint8_t readData = UART4_D;
    *pktBuf = readData;

    PacketParser();
}

void main() org 0x1000
{
    // set PTA10 as digital output
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_10 );
    // set PTC4 as digital output
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );

    // set KW40_RST as digital output
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_23 );
    
    OLED_Init();

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

    // turn off relays
    relay1 = 0;
    relay2 = 0;
    
    OLED_DrawImage( &relay_bmp, 0, 0 );

    while ( 1 )
    {
        if ( touch_invalid != pressedTouch )
        {
            switch ( pressedTouch )
            {
                case touch_left:
                {
                    TOGGLE_RELAY1();
                    break;
                }

                case touch_right:
                {
                    TOGGLE_RELAY2();
                    break;
                }

                default:
                {}
            }
            pressedTouch = touch_invalid;
        }
    }
}

/*************** END OF FUNCTIONS *********************************************/