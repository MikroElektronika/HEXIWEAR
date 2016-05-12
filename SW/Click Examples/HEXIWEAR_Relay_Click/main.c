/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * [File Name]     main.c
 * [Platform]      MK64FN1M0VDC12
 * [Project]       HEXIWEAR_Relay_Click
 * [Version]       1.00
 * [Author]        marko.lainovic
 * [Date]          04/19/2016
 * [Language]      'C'
 * [History]       1.00 - Original Release
 *
 * [Description]   Put Relay Click into a MikroBus socket 1 on the docking station.
 * Toggle the relay terminals via the touch interface (left and right buttons)
 *
 */

//-----------------------------------------------------------------------
// Standard C/C++ Includes
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// KSDK Includes
//-----------------------------------------------------------------------
#include "main.h"
#include "OLED_driver.h"
#include "screens_common.h"
#include "generic_spi_driver.h"

#include "OLED_defs.h"
#include "GPIO.h"
#include "OLED_SPI.h"
#include "DMA_controller.h"
#include "gui_resources.h"

//-----------------------------------------------------------------------
// Application Includes
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------
static void PacketParser( uint32_t instance, void* uartState );

//-----------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------
#define gHostInterface_startByte1               0x55
#define gHostInterface_startByte2               0xAA
#define gHostInterface_trailerByte              0x45

#define gHostInterface_dataSize                 23
#define gHostInterface_headerSize               4

#define FSL_KW40_UART UART4_IDX

//-----------------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------------
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


//-----------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------
oled_dynamic_area_t
	splashArea =
	{
		.xCrd = 0,
		.yCrd = 0
	};

const gpio_output_pin_user_config_t
	GPIO_cfg[] = {
  {
    .pinName = relay1,
    .config.outputLogic = 0,
    .config.slewRate = kPortSlowSlewRate,
    .config.isOpenDrainEnabled = false,
    .config.driveStrength = kPortLowDriveStrength,
  },
  {
    .pinName = relay2,
    .config.outputLogic = 0,
    .config.slewRate = kPortSlowSlewRate,
    .config.isOpenDrainEnabled = false,
    .config.driveStrength = kPortLowDriveStrength,
  },
  {
    .pinName = KW40_RST,
    .config.outputLogic = 0,
    .config.slewRate = kPortSlowSlewRate,
    .config.isOpenDrainEnabled = false,
    .config.driveStrength = kPortLowDriveStrength,
  },
  {
    .pinName = GPIO_PINS_OUT_OF_RANGE,
  }
};

/*! KW40_UART configuration structure */
const uart_user_config_t KW40_UART_InitConfig = {
  .baudRate = 230400U,
  .parityMode = kUartParityDisabled,
  .stopBitCount = kUartTwoStopBit,
  .bitCountPerChar = kUart8BitsPerChar,
};


/*! Driver state structure without DMA */
uart_state_t KW40_UART_State;

volatile touch_type_t pressedTouch = touch_invalid;

static hostInterface_packet_t hostInterface_rxPacket;

//uint8_t * pktBuf = ( uint8_t * ) &hostInterface_rxPacket;

static hostInterface_rxState_t hostInterface_rxState = hostInterface_rxState_idle;

//-----------------------------------------------------------------------
// Macros
//-----------------------------------------------------------------------
#define TOGGLE_RELAY1() GPIO_DRV_TogglePinOutput( relay1 )
#define TOGGLE_RELAY2() GPIO_DRV_TogglePinOutput( relay2 )

#define KW40_RST_SET()   GPIO_DRV_SetPinOutput( KW40_RST )
#define KW40_RST_CLEAR() GPIO_DRV_ClearPinOutput( KW40_RST )

//-----------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------

int main(void)
{
	CLOCK_SYS_EnablePortClock(PORTA_IDX);
	CLOCK_SYS_EnablePortClock(PORTB_IDX);
    CLOCK_SYS_EnablePortClock(PORTC_IDX);
	CLOCK_SYS_EnablePortClock(PORTD_IDX);
	CLOCK_SYS_EnablePortClock(PORTE_IDX);

    g_xtal0ClkFreq = 12000000U;
    g_xtalRtcClkFreq = 32768U;

	/** configure UART pins */
    PORT_HAL_SetMuxMode( PORTE, 24u, kPortMuxAlt3 );
    PORT_HAL_SetMuxMode( PORTE, 25u, kPortMuxAlt3 );

    /** configure SPI2 pins */
    PORT_HAL_SetMuxMode( PORTB, 21UL, kPortMuxAlt2 );
    PORT_HAL_SetMuxMode( PORTB, 22UL, kPortMuxAlt2 );

    OSA_Init();

    GPIO_DRV_Init( pir_input_cfg, pir_output_cfg );
    GPIO_DRV_Init( NULL, OLED_cfg );
    GPIO_DRV_Init( NULL, PWR_cfg );
    GPIO_DRV_Init( NULL, RGB_cfg );
	GPIO_DRV_Init( NULL, GPIO_cfg );

    EDMA_DRV_Init( &DMA_controller_State, &DMA_controller_InitConfig0 );
    DSPI_DRV_EdmaMasterInit(FSL_OLED_SPI, &OLED_SPI_MasterState, &OLED_SPI_MasterConfig, &OLED_SPI_dmaTcd);
    DSPI_DRV_EdmaMasterConfigureBus(FSL_OLED_SPI, &OLED_SPI_BusConfig, &OLED_SPI_calculatedBaudRate);

    OLED_Init( &oledModule, &oledSettings );
    OLED_GetImageDimensions( &(splashArea.width), &(splashArea.height), hexiwear_logo_bmp );
    OLED_SetDynamicArea( &splashArea );

    // initialize UART to KW40
	UART_DRV_Init( FSL_KW40_UART, &KW40_UART_State, &KW40_UART_InitConfig );

	__enable_irq();
	NVIC_EnableIRQ( UART4_RX_TX_IRQn );

	UART_DRV_InstallRxCallback( FSL_KW40_UART, PacketParser, (uint8_t*)&hostInterface_rxPacket, NULL, true );

    // Reset KW40
    KW40_RST_CLEAR();
    OSA_TimeDelay( 10 );
    KW40_RST_SET();
    OSA_TimeDelay( 200 );

    OLED_DrawImage( relay_logo_bmp );

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

static void PacketParser(
							uint32_t instance,
							void* uartState
						)
{
    static uint8_t byteCount;

    uart_state_t* state = (uart_state_t*)uartState;

    switch ( hostInterface_rxState )
    {
        case hostInterface_rxState_idle:
        {
            if ( gHostInterface_startByte1 == hostInterface_rxPacket.start1 )
            {
                hostInterface_rxState++;
                state->rxBuff++;
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
                state->rxBuff = ( uint8_t * )&hostInterface_rxPacket;
            }

            else
            {
                // advance the buffer pointer
            	state->rxBuff++;

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
            state->rxBuff++;

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
            if ( gHostInterface_trailerByte == *(state->rxBuff) )
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
            state->rxBuff = ( uint8_t * )&hostInterface_rxPacket;
            break;
        }

        default:
        {
            hostInterface_rxState++;
            state->rxBuff++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////


