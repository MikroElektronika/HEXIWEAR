// File: HEXIWEAR_info.h

// Some commonly used macros in the HEXIWEAR module.

#ifndef _HEXIWEAR_info_h_
#define _HEXIWEAR_info_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "host_mcu_interface.h"
#include "sensor_info.h"
#include "gui_info.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define HEXIWEAR_STATE_FLAGS_ADDRESS ( 0xF1000 )
#define HEXIWEAR_FLAGS ( ( hexiwear_flags_t* )HEXIWEAR_STATE_FLAGS_ADDRESS )

#define HEXIWEAR_WIFI_FLAG_ADDRESS ( 0xF2000 )
#define HEXIWEAR_WIFI_FLAGS ( ( hexiwear_wifi_flags_t* )HEXIWEAR_WIFI_FLAG_ADDRESS )

#define HEXIWEAR_G3_FLAG_ADDRESS ( 0xF3000 )
#define HEXIWEAR_G3_FLAGS ( ( hexiwear_g3_flags_t* )HEXIWEAR_G3_FLAG_ADDRESS )

#define HEXIWEAR_CONNECTION_FLAG_ADDRESS ( 0xF4000 )
#define HEXIWEAR_CONNECTION_FLAGS ( ( hexiwear_connection_flags_t* )HEXIWEAR_CONNECTION_FLAG_ADDRESS )

// HEXIWEAR firmware version
#define HEXIWEAR_VERSION_PATCH ( 0 )
#define HEXIWEAR_VERSION_MINOR ( 1 )
#define HEXIWEAR_VERSION_MAJOR ( 2 )

// uncomment below to enable additional debugging capabilities
// #define HEXIWEAR_DEBUG

// global  constants
#define UART_TIMEOUT (10)
#define VIBRO_DURATION (50)
#define SEND_PACKETS_VIA_UART_INT

#define VIBRO_ON()  PTB_PDOR.B9 = 1;
#define VIBRO_OFF() PTB_PDOR.B9 = 0;

#if defined( HEXIWEAR_DEBUG )
        #define HEXIWEAR_DEBUG_UART_INSTANCE ( FSL_DEBUG_UART )

        #define SET_PROBE()    PTA_PDOR.B11 = 1;
        #define CLEAR_PROBE()  PTA_PDOR.B11 = 0;
        #define TOGGLE_PROBE() PTA_PDOR.B11 = !PTA_PDOR.B11;

        #define SET_PROBE2()    PTB_PDOR.B16 = 1;
        #define CLEAR_PROBE2()  PTB_PDOR.B16 = 0;
        #define TOGGLE_PROBE2() PTB_PDOR.B16 = !PTB_PDOR.B16;
#else
        #define SET_PROBE()
        #define CLEAR_PROBE()
        #define TOGGLE_PROBE()

        #define SET_PROBE2()
        #define CLEAR_PROBE2()
        #define TOGGLE_PROBE2()
#endif

#define HEXIWEAR_EnableExceptions()                                            \
    SCB_SHCRS                    |= 0x00070000;                                \
    *( ( uint32_t* )0xE000E008 ) |= 0x00000002;
#define HEXIWEAR_Start() OSA_Start()

// tasks' stack sizes
#define HEXIWEAR_KW40_INTF_TASK_OK_STACK_SIZE gHostInterfaceOkTaskStackSize_c
#define HEXIWEAR_KW40_INTF_TASK_Tx_STACK_SIZE gHostInterfaceTxTaskStackSize_c
#define HEXIWEAR_KW40_INTF_TASK_Rx_STACK_SIZE gHostInterfaceRxTaskStackSize_c

#define HEXIWEAR_TASK_SENSOR_GET_DATA_STACK_SIZE ( SENSOR_GET_DATA_STACK_SIZE )

#define HEXIWEAR_APP_WATCH_STACK_SIZE            ( WATCH_STACK_SIZE )
#define HEXIWEAR_APP_SENSOR_TAG_STACK_SIZE       ( SENSOR_TAG_STACK_SIZE )
#define HEXIWEAR_STARTUP_STACK_SIZE              ( 0x1000 )

// tasks' priorities
#define HEXIWEAR_STARTUP_PRIO ( 1 )
#define HEXIWEAR_KW40_INTF_TASK_OK_PRIO ( gHostInterfaceOkPriority_c )
#define HEXIWEAR_KW40_INTF_TASK_Tx_PRIO ( gHostInterfaceTxPriority_c )
#define HEXIWEAR_KW40_INTF_TASK_Rx_PRIO ( gHostInterfaceRxPriority_c )
#define HEXIWEAR_GUI_PRIO     ( 5 )
#define HEXIWEAR_APP_PRIO     ( 6 )
#define HEXIWEAR_SENSOR_PRIO  ( 7 )
#define HEXIWEAR_USB_TASK     ( USB_PRIO )

#define HEXIWEAR_TASK_SENSOR_TAG_PRIO     ( SENSOR_GET_DATA_PRIO )
#define HEXIWEAR_APP_WATCH_DATA_PRIO      ( WATCH_PRIO )

// interrupts' IRQ channels
#define HEXIWEAR_KW40_UART_IRQn   ( 66 )

#if defined( HEXIWEAR_DEBUG )
#define HEXIWEAR_DEBUG_UART_IRQn  ( 37 )
#endif

#define HEXIWEAR_FS_I2C_IRQn       ( 25 )
#define HEXIWEAR_NFS_I2C_IRQn      ( 24 )

#define HEXIWEAR_OLED_SPI_IRQn     ( 65 )
#define HEXIWEAR_OLED_DMA_RX_IRQn  ( 0 )
#define HEXIWEAR_OLED_DMA_TX_IRQn  ( 1 )

#define HEXIWEAR_FLASH_SPI_IRQn    ( 27 )
#define HEXIWEAR_FLASH_DMA_RX_IRQn ( 3 )
#define HEXIWEAR_FLASH_DMA_TX_IRQn ( 4 )

#define HEXIWEAR_RTC_IRQn ( 46 )

#define HEXIWEAR_TIMER_IRQn ( 58 )

// interrupts' priorities for protocols

// KW40 and debug UART
#define HEXIWEAR_KW40_UART_IRQ_PRIO  ( 1 )
#if defined( HEXIWEAR_DEBUG )
#define HEXIWEAR_DEBUG_UART_IRQ_PRIO ( 3 )
#endif

// OLED SPI
#define HEXIWEAR_OLED_SPI_IRQ_PRIO    ( 4 )
#define HEXIWEAR_OLED_DMA_TX_IRQ_PRIO ( 5 )
#define HEXIWEAR_OLED_DMA_RX_IRQ_PRIO ( 5 )

// I2C
#define HEXIWEAR_FS_I2C_IRQ_PRIO      ( 6 )
#define HEXIWEAR_NFS_I2C_IRQ_PRIO     ( 6 )

// RTC
#define HEXIWEAR_RTC_IRQ_PRIO     ( 7 )

// sensor timer
#define HEXIWEAR_TIMER_IRQ_PRIO   ( 8 )

// external FLASH SPI
#define HEXIWEAR_FLASH_SPI_IRQ_PRIO   ( 11 )
#define HEXIWEAR_FLASH_DMA_TX_IRQ_PRIO ( 12 )
#define HEXIWEAR_FLASH_DMA_RX_IRQ_PRIO ( 12 )

// GPIO
#define HEXIWEAR_CHG_IRQ_PRIO ( 1 )
#define HEXIWEAR_TAP_IRQ_PRIO ( 2 )

// helpful macros
#define TypeMember_Size( type, member )                                        \
    ( sizeof( ( (type*)0 )->member ) )
#define TypeMember_NumEl( type, member )                                       \
    ( sizeof( ( (type*)0 )->member ) / sizeof( ( (type*)0 )->member[0] ) )
#define TypeMember_SCALAR                ( 1 )
#define ArraySize( array )               ( sizeof(array) / sizeof(array[0]) )

#define Extract( vector, field )                                               \
    ( ( vector & field##_MASK ) >> field##_SHIFT )
#define Add( vector, field, valueToOR )                                        \
    vector =   vector                       | ( valueToOR    << field##_SHIFT )
#define Write( vector, field, valueToWrite )                                   \
    vector = ( vector & ~( field##_MASK ) ) | ( valueToWrite << field##_SHIFT )
#define WriteZ( vector, field, valueToWrite )                                  \
    vector = 0; Write( vector, field, valueToWrite )

#endif