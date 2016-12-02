/**
 * @file                                                        gsm4_config.h
 *
 * @defgroup AT_CONF AT Parser Configuration
 * @{
 *
 * @brief               AT Parser Configuration
 *
 * @par
 * Set of preprocessors used to configure AT Parser.
 *
 ******************************************************************************/

#ifndef AT_CONFIG_H
#define AT_CONFIG_H

/******************************************************************************
* Includes
*******************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/**
 * AT Head */
#define AT_HEAD                                         "AT"
#define AT_HEAD_SIZE                                    2

/**
 * General Error Message */
#define AT_CMS_ERROR                                    "+CMS ERROR:"
#define AT_CMS_ERROR_SIZE                               11

/**
 * Size of AT command. This should represent maximum size of request header */
#define AT_HEADER_SIZE                                  15

/**
 * Size of command storage. This represent number of commands that can be
 * stored to the module and later recognized by the library. */
#define AT_STORAGE_SIZE                                 50

/**
 * This is the maximum amount of characters that can be transfered per one
 * sequence in both directions. */
#define AT_TRANSFER_SIZE                                256

/**
 * Default timeout in milliseconds for the specific module */
#define AT_DEFAULT_TIMEOUT                              500

/******************************************************************************
* Typedefs
*******************************************************************************/

typedef enum
{
    AT_OK,
    AT_ERROR,
    AT_UNKNOWN

}at_t;

typedef void ( *at_cmd_cb )( char *buffer );

#endif

/**
 * @}
 */
/*******************************End of File ***********************************/