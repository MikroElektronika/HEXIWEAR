/**
 * project-specific info
 * Project HEXIWEAR, 2015
 */

#ifndef HG_HEXIWEAR_INFO
#define HG_HEXIWEAR_INFO

#include "HEXIWEAR_types.h"
#include "host_mcu_interface.h"
#include "gpio1.h"

#define TASK_SENSOR_GET_DATA_DATA_PRIO (10)
#define TASK_SENSOR_GET_DATA_STACK_SIZE (1000)

#define PROBE_PIN ( RMII0_RXD_1 )

//#define HEXIWEAR_DEBUG

#if defined( HEXIWEAR_DEBUG )
#define HEXIWEAR_DEBUG_PRIO     ( 6 )
#define HEXIWEAR_DEBUG_INSTANCE ( FSL_UARTCOM2 )
#define HEXIWEAR_DEBUG_IRQn ( UART3_RX_TX_IRQn )
#endif

#define TypeMember_Size( type, member )  ( sizeof( ( (type*)0 )->member ) )
#define TypeMember_NumEl( type, member ) ( sizeof( ( (type*)0 )->member ) / sizeof( ( (type*)0 )->member[0] ) )
#define TypeMember_SCALAR (1)

#define Extract( vector, field )              ( ( vector & field##_MASK ) >> field##_SHIFT )
#define Write( vector, field, valueToWrite )  ( vector = ( vector & ~( field##_MASK ) ) | ( valueToWrite << field##_SHIFT ) )
#define Add( vector, field, valueToOR )       ( vector =   vector                       | ( valueToOR    << field##_SHIFT ) )

#endif
