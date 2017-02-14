/**
 * @file                                                        at_engine.c
 *
 * @cond INTER
 *
 * @brief                       AT Engine
 *
 * Version : 1.0.0
 *
 * ### Revision Log : ###
 *
 * @version
 * 0.0.1 (Apr/2016)  Module created
 *  + UART based engine
 *  + Timer not required
 *  + Write pointer assingment without user interaction
 *  + Internal buffer with fixed size
 *  + Internal handler storage
 * @author Milos Vidojevic
 *
 * @version
 * 1.0.0 (Dec/2016)  Module improved
 *  + Timer based engine
 *  + Timer requierd
 *  + User providing write pointer
 *  + Improved functionality
 *  + External user defined buffer provided drunig initialization
 * @author Milos Vidojevic
 *
 * ### To Do List : ###
 *
 * @todo
 * Implement Hardware flow control
 *  + Add dynamic enabling of HFC depend on HW implementation
 *  + Cover both possible HFC methods
 *
 * @todo
 * Improve Parser
 *  + Response parsing for now uses "+" as the begin of the command. However
 *      some AT commands starts with "#" or "$" or some other character.
 *
 * @todo
 * Buffer overflow check needed
 *  + In case of data transfers some responses might be bigger than the size of
 * the buffer - this situation is not handled yet.
 *
 * ### Test configuration 1 : ###
 * @par
 * - <b>MCU</b> :             STM32F107VC
 * - <b>Dev. Board</b> :      EasyMx Pro v7
 * - <b>Oscillator</b> :      72 Mhz
 * - <b>Ext. Modules</b> :    GSM-GPS Click
 * - <b>SW</b> :              MikroC PRO for ARM 4.9.0
 *
 ******************************************************************************/

#include "at_engine.h"

/**         Macros
 ******************************************************************************/

/**
 * AT string size */
#define AT_HEAD_SIZE                                    2

/**
 * Size of AT command. This should represent maximum size of request header */
#define AT_HEADER_SIZE_MAX                             15

/**
 * Termination characters */
#define AT_TERMINATE                                    0x0D
#define AT_TERMINATE_ADD                                0x1A

/**
 * Default timeout in milliseconds for the specific module */
#define AT_DEFAULT_TIMEOUT                              500

/**
 * Size of command storage. This represent number of commands that can be
 * stored to the module and later recognized by the library. */
#define AT_STORAGE_SIZE                                 50

/* Stores the pointer to the buffer and cleans it. */
#define AT_BUFFER_INIT(ptr,max)                                                 \
{ p_rx_buf = (ptr); rx_max = (max); rx_idx = 0;                                 \
  memset( ( void* )p_rx_buf, 0, rx_max ); }

/* Clears the content of the buffer */
#define AT_BUFFER_RESET()                                                       \
{ rx_idx = 0; *p_rx_buf = 0; }

/* Sets all flags to false and all counters to the zero. */
#define AT_CORE_INIT()                                                          \
{ t_response_l = 0; t_response_c = 0; t_char_l = 50; t_char_c = 0; tmp_cnt = 0; \
  t_response_f = false; t_char_f = false; response_f = false;                   \
  no_response_f = false; cue_f = false;  }

/* Cleans handlers storage. */
#define AT_STORAGE_INIT()                                                       \
{ at_cmd_storage_used = 0;                                                      \
  for( tmp_cnt = 0; tmp_cnt < AT_STORAGE_SIZE; tmp_cnt++ ) {                    \
    at_cmd_storage[ tmp_cnt ].hash = 0; at_cmd_storage[ tmp_cnt ].timeout  = 0; \
    at_cmd_storage[ tmp_cnt ].getter = NULL;                                    \
    at_cmd_storage[ tmp_cnt ].setter = NULL;                                    \
    at_cmd_storage[ tmp_cnt ].tester = NULL;                                    \
    at_cmd_storage[ tmp_cnt ].executer = NULL; }}

/* Blocks sending of the new command if the AT Engine excepts response. */
#define AT_WAIT_RESPONSE()                                                      \
{ while( cue_f ) at_process(); }

/* Puts the AT Engine to the blocked state. */
#define AT_SET_CUE()                                                            \
{ no_response_f = false; response_f = false; cue_f = true; }

/* Releases the AT Engine from the blocked state. */
#define AT_RESET_CUE()                                                          \
{ no_response_f = false; response_f = false; cue_f = false; }

/* Loads the global timer for the particular command. */
#define AT_LOAD_TIMER(x)                                                        \
{ t_response_l = x; t_response_c = 0; t_response_f = true; }

/* Stop the global timer. */
#define AT_STOP_TIMER()                                                         \
{ t_response_f = false; }

/* Restarts the character timer used to detect end of response. */
#define AT_RESTART_T()                                                          \
{ t_char_c = 0; t_char_f = true; }

/* Stops the character timer. */
#define AT_STOP_T()                                                             \
{ t_char_f = false; }

/**         Typedefs
 ******************************************************************************/

typedef enum
{
    AT_OK,
    AT_ERROR,
    AT_UNKNOWN

}at_t;

/**         Variables
 ******************************************************************************/

/* Hardware Flow Control Pins */
#if defined( __MIKROC_PRO_FOR_ARM__ )       || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )     || \
    defined( __MIKROC_PRO_FOR_PIC32__ )     || \
    defined( __MIKROC_PRO_FOR_AVR__ )       || \
    defined( __MIKROC_PRO_FOR_PIC__ )       || \
    defined( __MIKROC_PRO_FOR_8051__ )      || \
    defined( __MIKROC_PRO_FOR_FT90x__ )
extern sfr sbit CTS_PIN;
extern sfr sbit RTS_PIN;
#endif

/* Function pointer */
#if defined( __MIKROC_PRO_FOR_ARM__ )       || \
    defined( __MIKROC_PRO_FOR_DSPIC__ )     || \
    defined( __MIKROC_PRO_FOR_PIC32__ )
static void         ( *write_uart_p )           ( unsigned int data_out );
#elif defined( __MIKROC_PRO_FOR_AVR__ )     || \
      defined( __MIKROC_PRO_FOR_PIC__ )     || \
      defined( __MIKROC_PRO_FOR_8051__ )    || \
      defined( __MIKROC_PRO_FOR_FT90x__ )
static void         ( *write_uart_p )           ( unsigned char data_out );
#endif

static const uint8_t            header_size = 2;

/* Buffer Pointers*/
static volatile uint8_t*        p_rx_buf;
static volatile uint16_t        rx_idx;
static uint16_t                 rx_max;

/* Timer Flags */
static volatile bool            t_response_f;
static volatile bool            t_char_f;

/* Timer Counters */
static volatile uint32_t        t_response_c;
static volatile uint32_t        t_char_c;

/* Timer Limits */
static volatile uint32_t        t_response_l;
static volatile uint32_t        t_char_l;

/* Temp Variables */
static at_cmd_cb                tmp_cb;
static uint8_t                  tmp_cnt;
static uint32_t                 tmp_timer;

/* Callbacks */
static volatile at_cmd_cb       cb;
static volatile at_cmd_cb       cb_default;

/* CB Storage */
static uint8_t              at_cmd_storage_used;
static at_cmd_t             at_cmd_storage      [ AT_STORAGE_SIZE ];

/* Global Cue Flag - used to block sending of more than one command */
static volatile bool            cue_f;
/* Response Flag - used to start parsing of complete resposne */
static volatile bool            response_f;
/* No Response Flag - used to start parsing of incomplete response */
static volatile bool            no_response_f;

/**         Private Functions Prototypes
 ******************************************************************************/

/**
 * @brief Transmission
 *
 * @param[in] uint8_t tx_input - pointer to command
 * @param[in] uint8_t delimiter - character to confirm command
 *
 * Transmission uses function pointer provided by the user as an argument
 * to the initialization of the engine.
 */
static void _tx( uint8_t *tx_input, uint8_t delimiter );

/**
 * @brief Hash code generation
 *
 * @param[in] char* cmd - pointer to command
 * @return uint32_t Hash code
 *
 * Hash code is used to save the command to the storage in aim to have fixed
 * storage space for all functions.
 */
static uint32_t _parse_hash( char *cmd );

/**
 * @brief Search storage for provided command
 *
 * @param[in] char* cmd - pointer to command
 * @return uint16_t Command position inside the storage
 *
 * Function search the storage based on hash code. If function returns zero
 * command does not exists in storage area.
 */
static uint16_t _parse_find( char* cmd );

/**
 * @brief Save command to storage
 *
 * @param[in] char* command - command string
 * @param[in] uint32_t timeout - timeout for particular command
 * @param[in] at_cmd_cb getter - handler for GET command
 * @param[in] at_cmd_cb setter - handler for SET command
 * @param[in] at_cmd_cb tester - handler for TEST command
 * @param[in] at_cmd_cb executer - handler for EXECUTE command
 *
 * Function check does provided command already exist inside the storage and
 * writes the command with provided handlers to the first free space inside
 * the storage only in case if command does not exists in storage area.
 */
static void _parse_save( char *command, uint32_t timeout,
                         at_cmd_cb getter, at_cmd_cb setter,
                         at_cmd_cb tester, at_cmd_cb executer );

/**
 * @brief Preparsing
 *
 * @param[in] char* raw_in - raw command string
 * @param[in] char* clean_out - clean command string
 *
 * @return at_type_t command type
 *
 * Function cleans the provided command string from any arguments provided
 * alongside with command and returns command type. If command type is not
 * recognized EXECUTE type is returned as default command type. Cleaning is
 * needed for later generation of the hash code and searching of the storage
 * for the particular command.
 */
static at_type_t _parse_pre( char *raw_in, char *clean_out );

/**
 * @brief Parsing
 *
 * @param[in] char* input - AT Command
 * @param[out] at_cmd_cb* cb - handler pointer for the particular command
 * @param[out] uint32_t* timeout - timeout for the particular command
 *
 * Function parses provided raw command string and returns previously saved
 * handler and timeout for the particular command. If command is not found
 * the default handler and default timeout will be returned.
 */
static void _parse_exe( char *input, at_cmd_cb *cb, uint32_t *timeout );

/**         Private Functions Definitions
 ******************************************************************************/
static void _tx( uint8_t *tx_input, uint8_t delimiter )
{
#ifdef _DEBUG_
        LOG( "< WR >\r\n" );
#endif
    while( *tx_input )
    {
        /**
         * @todo
         * Check CTS before every char and loop until last one
         */
#ifdef _DEBUG_
        LOG_CH( *tx_input );
#endif
        write_uart_p( *tx_input++ );
    }

    write_uart_p( delimiter );
    write_uart_p( '\n' );
#ifdef _DEBUG_
    LOG_CH( delimiter );
    LOG( "\r\n" );
#endif
}

static uint32_t _parse_hash( char *cmd )
{
    uint16_t ch     = 0;
    uint32_t hash   = 4321;
    while( ( ch = *( cmd++ ) ) )
        hash = ( ( hash << 5 ) + hash ) + ch;
    return hash;
}

static uint16_t _parse_find( char* cmd )
{
    uint8_t _cnt = 0;

    uint32_t tmp_hash = _parse_hash( cmd );
    for( _cnt = 0; _cnt < at_cmd_storage_used; _cnt++ )
        if( at_cmd_storage[ _cnt ].hash == tmp_hash )
            return _cnt;
    return 0;
}

static void _parse_save( char *command, uint32_t timeout,
                         at_cmd_cb getter, at_cmd_cb setter,
                         at_cmd_cb tester, at_cmd_cb executer )
{
    at_cmd_t cmd;

    cmd.hash        = _parse_hash( command );
    cmd.timeout     = timeout;
    cmd.getter      = getter;
    cmd.setter      = setter;
    cmd.tester      = tester;
    cmd.executer    = executer;

    if( strlen( command ) >= AT_HEADER_SIZE_MAX + AT_HEAD_SIZE )
        return;

    if( at_cmd_storage_used == AT_STORAGE_SIZE )
        return;

    if( _parse_find( command ) )
        return;

    at_cmd_storage[ at_cmd_storage_used ] = cmd;
    at_cmd_storage_used++;
}

static at_type_t _parse_pre( char *raw_in, char *clean_out )
{
    uint8_t     _cnt                   = 0;
    uint8_t     end_pos                   = 0;
    uint8_t     set_pos                   = 0;
    uint8_t     get_pos                   = 0;
    uint8_t     start_pos                 = 0;
    char*       tmp_ptr                   = raw_in;
    char        tmp_cmd[ AT_HEADER_SIZE_MAX ] = { 0 };

    if( strlen( tmp_ptr ) <= AT_HEAD_SIZE )
        return AT_CMD_UNKNOWN;

    strncpy( tmp_cmd, tmp_ptr, AT_HEADER_SIZE_MAX );

    for( _cnt = 0; _cnt < AT_HEADER_SIZE_MAX; _cnt++ )
    {
        if( tmp_cmd[ _cnt ] == '\0' )
        {
            if( !end_pos )
                end_pos = _cnt;
            break;
        }

        /**
         * @todo
         * Setable array of characters for checking
         * - some AT commands uses( #, $ ... )
         */
        if( ( tmp_cmd[ _cnt ] == '+') && !start_pos )
            start_pos = _cnt;

        if( ( tmp_cmd[ _cnt ] == '=' ) && !set_pos )
            set_pos = _cnt;

        if( ( tmp_cmd[ _cnt ] == '?' ) && !get_pos )
            get_pos = _cnt;

        if( ( ( ( tmp_cmd[ _cnt ] == '\r' )  ||
                ( tmp_cmd[ _cnt ] == '\n' )  ||
                ( tmp_cmd[ _cnt ] == ':' ) ) && !end_pos ) && start_pos )
            end_pos = _cnt;
    }

    if( !set_pos && !get_pos )
    {
        strncpy( clean_out, &tmp_cmd[ start_pos ], end_pos - start_pos );
        return AT_CMD_EXEC;

    } else if( !set_pos && get_pos ) {

        strncpy( clean_out, &tmp_cmd[ start_pos ], get_pos - start_pos );
        return AT_CMD_TEST;

    } else if( set_pos && !get_pos ) {

        strncpy( clean_out, &tmp_cmd[ start_pos ], set_pos - start_pos );
        return AT_CMD_SET;

    } else if( set_pos == get_pos - 1 ) {

        strncpy( clean_out, &tmp_cmd[ start_pos ], set_pos - start_pos );
        return AT_CMD_GET;
    }

    return AT_CMD_UNKNOWN;
}

void _parse_exe( char *input, at_cmd_cb *cb, uint32_t *timeout )
{
    at_type_t   cmd_type                    = 0;
    uint16_t    cmd_idx                     = 0;
    char        cmd_temp[ AT_HEADER_SIZE_MAX ]  = { 0 };

    if( !( cmd_type = _parse_pre( input, cmd_temp ) ) )
    {
        *cb = at_cmd_storage[ 0 ].tester;
        *timeout = at_cmd_storage[ 0 ].timeout;
        return;
    }

    if( !( cmd_idx = _parse_find( cmd_temp ) ) )
    {
        *cb = at_cmd_storage[ 0 ].tester;
        *timeout = at_cmd_storage[ 0 ].timeout;
        return;
    }

    switch ( cmd_type )
    {
        case AT_CMD_SET :
            *cb = at_cmd_storage[ cmd_idx ].setter;
            *timeout = at_cmd_storage[ cmd_idx ].timeout;
        break;
        case AT_CMD_GET :
            *cb = at_cmd_storage[ cmd_idx ].getter;
            *timeout = at_cmd_storage[ cmd_idx ].timeout;
        break;
        case AT_CMD_TEST :
            *cb = at_cmd_storage[ cmd_idx ].tester;
            *timeout = at_cmd_storage[ cmd_idx ].timeout;
        break;
        case AT_CMD_EXEC :
            *cb = at_cmd_storage[ cmd_idx ].executer;
            *timeout = at_cmd_storage[ cmd_idx ].timeout;
        break;
        case AT_CMD_UNKNOWN :
            *cb = at_cmd_storage[ 0 ].executer;
            *timeout = at_cmd_storage[ 0 ].timeout;
        break;
    }
    return;
}

/**     Public Functions
 ******************************************************************************/

void at_init
(
    at_cmd_cb default_callback,
    at_write_p default_write,
    uint8_t *buffer_ptr,
    uint16_t buffer_size
)
{
    at_cmd_t cmd;

    cb_default          = default_callback;
    write_uart_p        = default_write;
    AT_CORE_INIT();
    AT_BUFFER_INIT( buffer_ptr, buffer_size );
    AT_STORAGE_INIT();
    cmd.hash                                = _parse_hash( "" );
    cmd.timeout                             = AT_DEFAULT_TIMEOUT;
    cmd.getter                              = default_callback;
    cmd.setter                              = default_callback;
    cmd.tester                              = default_callback;
    cmd.executer                            = default_callback;
    at_cmd_storage[ at_cmd_storage_used ]   = cmd;
    at_cmd_storage_used++;
}

void at_rx( char rx_input )
{
    AT_SET_CUE();
    AT_RESTART_T();
    *( p_rx_buf + rx_idx++ ) = rx_input;
}

void at_tick( void )
{
    if( t_response_f )
        if( t_response_c++ > t_response_l )
        {
            t_response_f = false;
            t_response_c = 0;
            *( p_rx_buf + rx_idx ) = 0;
            no_response_f = true;
        }

    if( t_char_f )
        if( t_char_c++ > t_char_l )
        {
            t_char_f = false;
            t_char_c = 0;
            *( p_rx_buf + rx_idx ) = 0;
            response_f = true;
        }
}

void at_cmd_save( char *cmd, uint32_t timeout,
                  at_cmd_cb getter, at_cmd_cb setter,
                  at_cmd_cb tester, at_cmd_cb executer )
{
    if( !setter )   setter = cb_default;
    if( !getter )   getter = cb_default;
    if( !tester )   tester = cb_default;
    if( !executer ) executer = cb_default;
    if( !timeout )  timeout = AT_DEFAULT_TIMEOUT;
    _parse_save( cmd, timeout, getter, setter, tester, executer );
}

void at_cmd_single( char *cmd )
{
    char* tmp = cmd;

    AT_WAIT_RESPONSE();
    _parse_exe( tmp, &tmp_cb, &tmp_timer );
    _tx( tmp, AT_TERMINATE );
    AT_SET_CUE();
    AT_LOAD_TIMER( tmp_timer );
}

void at_cmd_double( char *cmd, char *arg_1 )
{
    char *tmp       = cmd;
    char *tmp_a1    = arg_1;

    AT_WAIT_RESPONSE();
    _parse_exe( tmp, &tmp_cb, &tmp_timer );
    _tx( tmp, AT_TERMINATE );
    AT_SET_CUE();
    AT_LOAD_TIMER( tmp_timer );
    AT_WAIT_RESPONSE();
    AT_STOP_TIMER();
    _tx( tmp_a1, AT_TERMINATE_ADD );
    AT_SET_CUE();
    AT_LOAD_TIMER( tmp_timer );
}

void at_cmd_triple( char *cmd, char *arg_1, char *arg_2 )
{
    char *tmp       = cmd;
    char *tmp_a1    = arg_1;
    char *tmp_a2    = arg_2;

    AT_WAIT_RESPONSE();
    _parse_exe( tmp, &tmp_cb, &tmp_timer );
    _tx( tmp, AT_TERMINATE );
    AT_SET_CUE();
    AT_LOAD_TIMER( tmp_timer );
    AT_WAIT_RESPONSE();
    AT_STOP_TIMER();
    _tx( tmp_a1, AT_TERMINATE_ADD );
    AT_SET_CUE();
    AT_LOAD_TIMER( tmp_timer );
    AT_WAIT_RESPONSE();
    AT_STOP_TIMER();
    _tx( tmp_a2, AT_TERMINATE_ADD );
    AT_SET_CUE();
    AT_LOAD_TIMER( tmp_timer );
}

void at_process( void )
{
    /**
     * @todo
     * Check free space in buffer and handle situation if
     * buffer is near the end.
     */

    if( response_f )
    {
        /**
         * @todo
         * Handle RTS until callback finishes execution if HWC supports
         * bidirectional communication - handshake method.
         */
        AT_STOP_T();
        AT_STOP_TIMER();
        _parse_exe( p_rx_buf, &cb, &tmp_timer );
        cb( p_rx_buf );
        AT_BUFFER_RESET();
        AT_RESET_CUE();
    }

    if( no_response_f )
    {
        /**
         * @todo
         * Handle RTS until callback finishes execution if HWC supports
         * bidirectional communication - handshake method.
         */
        AT_STOP_T();
        AT_STOP_TIMER();
        _parse_exe( p_rx_buf, &cb, &tmp_timer );
        cb( p_rx_buf );
        AT_BUFFER_RESET();
        AT_RESET_CUE();
    }
}

/**
 * @}
 * @endcond                                                     End of File
 */