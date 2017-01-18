/**
 * @file                                                        at_engine.h
 * @brief                       AT Engine
 *
 * @defgroup AT Engine
 *
 * @{
 *
 * @par
 * Generic AT engine usable with any device which uses AT commands for the
 * communication with the host MCU.
 *
 ******************************************************************************/

#ifndef AT_ENGINE_H
#define AT_ENGINE_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef void ( *at_cmd_cb )( char *buffer );

#if defined( __MIKROC_PRO_FOR_ARM__ )       || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )     || \
    defined( __MIKROC_PRO_FOR_PIC32__ )
typedef void ( *at_write_p )( unsigned int in );
#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )    || \
      defined( __MIKROC_PRO_FOR_FT90x__ )
typedef void ( *at_write_p )( unsigned char data_out );
#endif

/**
 * @enum at_ctl_t
 * @brief AT Command Type
 */
typedef enum
{
    /**
     * Unknown command */
    AT_CMD_UNKNOWN                              = 0,
    /**
     * AT Get command */
    AT_CMD_GET                                  = 1,
    /**
     * AT Set command */
    AT_CMD_SET                                  = 2,
    /**
     * AT Test command */
    AT_CMD_TEST                                 = 3,
    /**
     * AT Execute command */
    AT_CMD_EXEC                                 = 4,

}at_type_t;

/**
 * @struct at_cmd_t
 * @brief Parser Structure
 *
 * @par
 * Struct is used for storing the command with timeout and callbacks.
 * Command strings are converted to the hash code for easiest comparision.
 */
typedef struct
{
    /**
     * Command Hash Value */
    uint32_t                hash;
    /**
     * Command Timeout */
    uint32_t                timeout;
    /**
     * Get Callback */
    at_cmd_cb               getter;
    /**
     * Set Callback */
    at_cmd_cb               setter;
    /**
     * Test Callback */
    at_cmd_cb               tester;
    /**
     * Execute Callback */
    at_cmd_cb               executer;

}at_cmd_t;

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief AT Engine Initialization
 *
 * @param[in] at_cmd_cb default_callback - default handler
 * @param[in] at_write_p default_write - UARTx_Write function
 * @param[in] uint8_t* buffer_ptr - pointer to buffer
 * @param[in] uint16_t buffer_size - size of the buffer in bytes
 *
 * Initialization should be executed before any other function. User can
 * execute this function later inside the application to reset AT Engine to
 * the default state.
 */
void at_init( at_cmd_cb default_callback, at_write_p default_write,
              uint8_t *buffer_ptr, uint16_t buffer_size );

/**
 * @brief AT Engine Receiver
 *
 * @param[in] char rx_input - char received from the module
 *
 * Function is used to populate response buffer with characters received from
 * the module. This function should be placed inside UART ISR function.Is also
 * can be used inside function which constatnly poll the UART RX register.
 */
void at_rx( char rx_input );

/**
 * @brief AT Engine Tick
 *
 * Function must be placed inside the Timer ISR function which will be called
 * every one millisecond.
 */
void at_tick( void );

/**
 * @brief Simple AT Command
 *
 * @param[in] char* cmd - pointer to command string
 *
 * Function should be used in case of simple AT commands which have no
 * additional arguments expected. Most of the AT Commands uses this function.
 */
void at_cmd_single( char *cmd );

/**
 * @brief Doble AT Command
 *
 * @param[in] char* cmd - pointer to command string
 * @param[in] char* arg_1 - pointer to the string used as additional argument
 *
 * Function should be used with AT commands which expects additional data after
 * the module responses with specific character. In most cases special character
 * is ">" like in example of AT command for SMS sending.
 */
void at_cmd_double( char *cmd, char *arg_1 );

/**
 * @brief Triple AT Command
 *
 * @param[in] char* cmd - pointer to command string
 * @param[in] char* arg_1 - pointer to the string used as additional argument
 * @param[in] char* arg_2 - pointer to the second additional argument
 *
 * Function should be used with AT command which excepts two additional
 * parameters after the execution of the command. This kind of AT functions are
 * very rare.
 */
void at_cmd_triple( char *cmd, char *arg_1, char *arg_2 );

/**
 * @brief Save AT Command to Storage
 *
 * @param[in] char* command - command string
 * @param[in] uint32_t timeout - timeout for particular command
 * @param[in] at_cmd_cb getter - handler for GET command
 * @param[in] at_cmd_cb setter - handler for SET command
 * @param[in] at_cmd_cb tester - handler for TEST command
 * @param[in] at_cmd_cb executer - handler for EXECUTE command
 *
 * @par
 * Saves provided command alongside with callbacks and timeout to the storage.
 * Saved commands are later used for the
 */
void at_cmd_save( char *cmd, uint32_t timeout,
                  at_cmd_cb getter, at_cmd_cb setter,
                  at_cmd_cb tester, at_cmd_cb executer );

/**
 * @brief AT Process
 *
 * This function should be placed inside the infinite while loop.
 */
void at_process( void );

#ifdef __cplusplus
}
#endif
#endif

/**
 * @}                                                           End of File
 */
