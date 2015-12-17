/**
 * project-specific info
 * Project HEXIWEAR, 2015
 */

#ifndef HG_HEXIWEAR_INFO
#define HG_HEXIWEAR_INFO

#include "HEXIWEAR_defs.h"

#include "host_mcu_interface.h"
#include "sensor_info.h"
#include "menu_info.h"

#include "GPIO.h"

#include "MK64F12.h"

#define HEXIWEAR_DEBUG

#define YES ( 1 )
#define NO ( 0 )

#define SEND_PACKETS_VIA_UART_INT
#define UART_TIMEOUT (10)

#define VIBRO_DURATION (50)

#define VIBRO_HAPTIC()\
GPIO_DRV_SetPinOutput( VIBRO );\
OSA_TimeDelay( VIBRO_DURATION );\
GPIO_DRV_ClearPinOutput( VIBRO );\

#define VIBRO_ON()  GPIO_DRV_SetPinOutput( VIBRO )
#define VIBRO_OFF() GPIO_DRV_ClearPinOutput( VIBRO )

#if defined( HEXIWEAR_DEBUG )
#define PROBE_PIN ( PROBE )
#define HEXIWEAR_DEBUG_UART_INSTANCE ( FSL_DEBUG_UART )
#endif


/**
 * HEXI tasks
 */


/**
 * tasks' stack sizes
 */

#define HEXIWEAR_KW40_INTF_TASK_OK_STACK_SIZE    ( gHostInterfaceOkTaskStackSize_c )
#define HEXIWEAR_KW40_INTF_TASK_Tx_STACK_SIZE    ( gHostInterfaceTxTaskStackSize_c )
#define HEXIWEAR_KW40_INTF_TASK_Rx_STACK_SIZE    ( gHostInterfaceRxTaskStackSize_c )

#define HEXIWEAR_TASK_SENSOR_GET_DATA_STACK_SIZE ( SENSOR_GET_DATA_STACK_SIZE )

#define HEXIWEAR_APP_WATCH_STACK_SIZE            ( WATCH_STACK_SIZE )
#define HEXIWEAR_APP_SENSOR_TAG_STACK_SIZE       ( SENSOR_TAG_STACK_SIZE )
#define HEXIWEAR_STARTUP_STACK_SIZE              ( 0x1000 )

/**
 * tasks' priorities
 */

#define HEXIWEAR_KW40_INTF_TASK_OK_PRIO ( gHostInterfaceOkPriority_c )
#define HEXIWEAR_KW40_INTF_TASK_Tx_PRIO ( gHostInterfaceTxPriority_c )
#define HEXIWEAR_KW40_INTF_TASK_Rx_PRIO ( gHostInterfaceRxPriority_c )
#define HEXIWEAR_APP_WATCH_DATA_PRIO      ( WATCH_PRIO )
#define HEXIWEAR_APP_SENSOR_TAG_DATA_PRIO ( SENSOR_TAG_PRIO )
#define HEXIWEAR_TASK_SENSOR_TAG_PRIO     ( SENSOR_GET_DATA_PRIO )
#define HEXIWEAR_STARTUP_PRIO             ( 12 )

/**
 * interrupts' channels
 */

#define HEXIWEAR_KW40_UART_IRQn   ( UART4_RX_TX_IRQn )
#if defined( HEXIWEAR_DEBUG )
#define HEXIWEAR_DEBUG_UART_IRQn  ( UART3_RX_TX_IRQn )
#endif
#define HEXIWEAR_FS_I2C_IRQn      ( I2C1_IRQn )
#define HEXIWEAR_NFS_I2C_IRQn     ( I2C0_IRQn )
#define HEXIWEAR_OLED_SPI_IRQn    ( SPI2_IRQn )
#define HEXIWEAR_OLED_DMA_RX_IRQn ( DMA0_IRQn )
#define HEXIWEAR_OLED_DMA_TX_IRQn ( DMA1_IRQn )
#define HEXIWEAR_FLASH_SPI_IRQn   ( SPI1_IRQn )

/**
 * interrupts' priorities
 */

#define HEXIWEAR_KW40_UART_IRQ_PRIO gHostInterfaceIRQPriority_c
#if defined( HEXIWEAR_DEBUG )
#define HEXIWEAR_DEBUG_UART_IRQ_PRIO ( 6 )
#endif
#define HEXIWEAR_FS_I2C_IRQ_PRIO      ( 7 )
#define HEXIWEAR_NFS_I2C_IRQ_PRIO     ( 7 )
#define HEXIWEAR_OLED_SPI_IRQ_PRIO    ( 8 )
#define HEXIWEAR_OLED_DMA_TX_IRQ_PRIO ( 9 )
#define HEXIWEAR_OLED_DMA_RX_IRQ_PRIO ( 9 )
#define HEXIWEAR_FLASH_SPI_IRQ_PRIO   ( 11 )

#define TypeMember_Size( type, member )  ( sizeof( ( (type*)0 )->member ) )
#define TypeMember_NumEl( type, member ) ( sizeof( ( (type*)0 )->member ) / sizeof( ( (type*)0 )->member[0] ) )
#define TypeMember_SCALAR                ( 1 )
#define ArraySize( array )               ( sizeof(array) / sizeof(array[0]) )

#define Extract( vector, field )              ( ( vector & field##_MASK ) >> field##_SHIFT )
#define Add( vector, field, valueToOR )       vector =   vector                       | ( valueToOR    << field##_SHIFT )
#define Write( vector, field, valueToWrite )  vector = ( vector & ~( field##_MASK ) ) | ( valueToWrite << field##_SHIFT )
#define WriteZ( vector, field, valueToWrite ) vector = 0; vector = ( vector & ~( field##_MASK ) ) | ( valueToWrite << field##_SHIFT )

#endif
