/**
 * @file                                                    gsm4_at_engine.h
 *
 * @defgroup AT_ENG AT Engine
 * @{
 *
 * @brief                   AT Engine
 *
 * @par
 * Generic AT engine for devices which uses AT commands.
 *
 ******************************************************************************/

#ifndef AT_ENGINE_H
#define AT_ENGINE_H

#include "gsm4_config.h"
#include "gsm4_at_parser.h"
#include "gsm4_dev_timer.h"
#include "gsm4_dev_adapter.h"

/******************************************************************************
* Function Prototypes
*******************************************************************************/

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief AT Engine Initialization
 *
 * Initialization of engine should be done before execution of any other
 * function.
 */
void engine_init( at_cmd_cb default_callback );

/**
 * @brief AT Command
 *
 * @par
 * Executes provided AT command
 *
 * @param[in] input
 */
void at_cmd( char *input );

/**
 * @brief AT addition
 *
 * @par
 * Some AT commands requires additional data, this function is used to add the
 * data after the module resposes with specific output.
 *
 * @param[in] input
 */
void at_cmd_addition( char *input );

/**
 * @brief Save AT Command to Storage
 *
 * @par
 * Saves provided command with callbacks and timeout to the storage for later
 * parsing.
 *
 * @param[in] cmd
 * @param[in] timeout
 * @param[in] setter
 * @param[in] getter
 * @param[in] tester
 * @param[in] executer
 */
void at_cmd_save
(
        char *cmd,
        uint32_t timeout,
        at_cmd_cb getter,
        at_cmd_cb setter,
        at_cmd_cb tester,
        at_cmd_cb executer
);

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
 * @}
 */
/*******************************End of File ***********************************/