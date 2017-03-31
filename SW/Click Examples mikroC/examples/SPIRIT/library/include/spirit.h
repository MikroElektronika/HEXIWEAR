/**
 * @file    spirit.h
 * @brief   Library for SPIRIT click.
 *
 * @defgroup    spirit SPIRIT click module
 * @brief   Library for SPIRIT click.
 *
 *
 * @{
 *
 * ### Device Description ###
 * 
 * The SP1ML module is a compact-size module, integrating an on-board antenna 
 * with easy-to-use interface, allowing users to easily add wireless 
 * connectivity in designs without requiring in-depth RF experience, and has all
 * necessary FCC modular approvals and CE compliance, reducing time-to-market.
 * 
 *
 * ### Features ###
 *
 * - Complete RF-ready SPIRIT1 module based on:
 *      + SPIRIT1 low data rate, low power sub-GHz transceiver
 *      + STM32L1 Ultra low power microcontroller at 32 MHz (16 kB RAM and 
 *        128 kB Flash)
 *      + BALF-SPI-01D3 868/915 MHz balun with integrated harmonic filter
 *      + Integrated antenna and crystal
 * - Compact size: 14 mm x 13.4 mm x 2.5 mm
 * - 863 to 870 MHz operation (SP1ML-868)
 * - 902 to 928 MHz operation (SP1ML-915)
 * - Operates from a single 1.8 V to 3.6 V supply
 * - Output power up to +11.6 dBm
 * - Data rates up to 500 kbps
 * - Modulation schemes: 2-FSK, GFSK, GMSK, OOK, and ASK
 * - Operating temperature: -40 °C to 85 °C
 * - UART interface with AT command set
 * - FCC and CE regulatory approvals
 *
 * ### Library Description
 * 
 * The library implements communication protocol between MCU host and SPIRIT 
 * click module. It can work in two modes, command mode and operating mode.
 * The command mode allows module configuration and status interrogation using 
 * an extended ‘AT’ style command set. In operating mode the module serves its 
 * primary purpose as a wireless transceiver. It uses asynchronous approach
 * to issue commands and recieve responses via callback functions.
 *
 * @example SPIRIT_ARM.c
 * @example SPIRIT_HEXIWEAR.c
 * @example SPIRIT_PIC.c
 * @example SPIRIT_PIC32.c
 * @example SPIRIT_AVR.c
 * @example SPIRIT_FT90x.c
 *
 ******************************************************************************/

#ifndef SPIRIT_H
#define SPIRIT_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @name                 Device Properties
 ******************************************************************************/
///@{




///@}
/**
 * @name                 Return Values
 ******************************************************************************/
///@{

#define SPIRIT_OK (0x00)
#define SPIRIT_ERR_RING_BUFF_FULL (0xE1)
#define SPIRIT_ERR_FULL_CMD_BUFF (0xE2)
#define SPIRIT_ERR_RESPONSE_BUFF_FULL (0xE3)

#define SPIRIT_COMMAND_MODE (true)
#define SPIRIT_OPERATING_MODE (false)

///@}
/**
 * @name                 Types
 ******************************************************************************/
///@{

/**
 * UART write function pointer.
 */
#if     defined( __MIKROC_PRO_FOR_ARM__ )       || \
        defined( __MIKROC_PRO_FOR_DSPIC__ )     || \
        defined( __MIKROC_PRO_FOR_PIC32__ )
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef void ( *spirit_uart_write_t ) ( unsigned int data_out );
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#elif   defined( __MIKROC_PRO_FOR_AVR__ )     || \
        defined( __MIKROC_PRO_FOR_PIC__ )     || \
        defined( __MIKROC_PRO_FOR_8051__ )    || \
        defined( __MIKROC_PRO_FOR_FT90x__ )
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef void ( *spirit_uart_write_t ) ( unsigned char data_out );
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif    
///@}

typedef void ( *spirit_data_callback_t ) ( uint8_t *rx_data, uint8_t size );
typedef bool ( *spirit_callback_t ) ( char *response );

/**
 * Command structure.
 */
typedef struct spirit_cmd
{
    char *command;
    spirit_callback_t callback;
} spirit_cmd_t;
/**
 * @name                 Functions
 ******************************************************************************/
///@{
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief <h3> SPIRIT module initialization </h3>
 *
 * @param[in]   uart_write - Uart write function
 * @param[in]   on_data - Callback for recieving data
 * @param[in]   ring_buffer - Ring buffer
 * @param[in]   ring_size - Ring buffer size
 * @param[in]   cmd_buffer - Command buffer
 * @param[in]   cmd_buffer_size - Command buffer size
 *
 *
 * Initializes SPIRIT module library.
 *
 * @note
 * This function must be called first.
 *
 */
void spirit_init( 
    spirit_uart_write_t uart_write,
    spirit_data_callback_t on_data,
    uint8_t *ring_buffer,
    uint16_t ring_size,
    spirit_cmd_t *cmd_buffer,
    uint8_t cmd_buffer_size
);

/**
 * @brief <h3> Recieves data </h3>
 *
 * @param[in]   rx_data - Recieved data
 *
 * @retval      SPIRIT_OK
 * @retval      SPIRIT_ERR_RING_BUFF_FULL - Recieve buffer is full.
 *
 *
 * @note
 * Call this function to pass recieved data from SPIRIT module.
 *
 */
uint8_t spirit_rx(uint8_t rx_data);

/**
 * @brief <h3> Push command to queue </h3>
 *
 * @param[in]   command - C string command representation
 * @param[in]   on_response - Callback function on response recieved.
 *
 * @retval      SPIRIT_OK
 * @retval      SPIRIT_ERR_FULL_CMD_BUFF - Command buffer is full.
 *
 * The function pushes command to FIFO queue. It is stored in command buffer 
 * given during initialization. Care must be taken to not exceede buffer size. 
 * The function is asynchronous and actual execution of cammand is in 
 * spirit_process function. 
 *
 * @note 
 * 
 *
 */
uint8_t spirit_cmd(char* command, spirit_callback_t on_response);

/**
 * @brief <h3> Send data </h3>
 *
 * @param[in]   buffer - Data buffer to send.
 * @param[in]   size - Data buffer size.
 *
 * @retval      SPIRIT_OK
 *
 * Sends data in operation mode.
 *
 *
 */
uint8_t spirit_send(uint8_t *buffer, uint16_t size);

/**
 * @brief <h3> Set mode </h3>
 *
 * @param[in]   command_mode - Selects mode. True for command, and false 
 *                             for operation mode.
 *
 * @retval      SPIRIT_OK
 *
 * 
 * Sets library state in witch mode to work. Use this method when changing 
 * from mode to mode when using ATO command or '+++' escape sequence.
 *
 */
uint8_t spirit_mode(bool command_mode);

/**
 * @brief <h3> Restart </h3>
 *
 * @param[in]   command_mode - Selects mode. True for command, and false 
 *                             for operation mode.
 *
 * @retval      SPIRIT_OK
 *
 * Perform hardware restart, with mode selection. It uses MODE0 pin for
 * mode selection during restart.
 *
 */
uint8_t spirit_restart(bool command_mode);

/**
 * @brief <h3> Clear command buffer </h3>
 *
 *
 * @retval      SPIRIT_OK
 *
 * The function clears command buffer. It can be used in callback function 
 * to clear queued commands in order to add new.
 *
 */
uint8_t spirit_clear_cmd();

/**
 * @brief <h3> Process </h3>
 *
 * @retval      SPIRIT_OK
 * @retval      SPIRIT_ERR_RESPONSE_BUFF_FULL - Response buffer is full.
 *
 * The function implements state machine of the module.
 *
 * @note
 * Call this function inside loop.
 *
 */
uint8_t spirit_process();

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SPIRIT_H
///@}
/**
 * @}                                                                 End of File
 ******************************************************************************/