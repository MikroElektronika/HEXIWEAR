/*
 * spirit.c
 *
 * Version : 0.0.1
 *
 * Revision Log :
 * 0.0.1 (Feb/2017) Module created 
 *
 * To Do List :
 * - prilikom prelsaka u command mode treba isprazniti ring buffer
 *   predati ga on_data ili sta vec.
 * - Zasto mora delay pre send?
 *
 ******************************************************************************/

#include "spirit.h"

/* 		Preprocessors
 ******************************************************************************/

#define _ASCII_CR (0x0D)
#define _ASCII_LF (0x0A)
#define _ASCII_NULL (0x00)

#define _RESPONSE_BUFFER_SIZE (32)
#define _DATA_BUFFER_SIZE (16)

#define _WAKEUP (1)
#define _SHUTDOWN (0)

#define _COMMAND_MODE (0)
#define _OPERATING_MODE (1)

#define _RESTART (0)


/*		Typedefs
 ******************************************************************************/



/*		Variables
 ******************************************************************************/

extern sfr sbit SPIRIT_RST;
extern sfr sbit SPIRIT_SHD;
extern sfr sbit SPIRIT_CMD;

static spirit_uart_write_t _write;

static spirit_data_callback_t _on_data;
static spirit_callback_t _on_response;

static char _response_buffer[_RESPONSE_BUFFER_SIZE];
static uint8_t _response_ind;

static uint8_t _data_buffer[_DATA_BUFFER_SIZE];
static uint8_t _data_ind;

// States
static bool _command_mode;
static bool _wait_response;

// Command buffer (Ring buffer)
static spirit_cmd_t *_cmd_begin;
static spirit_cmd_t *_cmd_end;

static spirit_cmd_t *_cmd_head;
static spirit_cmd_t *_cmd_tail;

static uint8_t _cmd_size;
static uint8_t _cmd_capacity;

// Rx data buffer (Ring buffer)
static uint8_t *_ring_begin;
static uint8_t *_ring_end;

static volatile uint8_t *_ring_head;
static volatile uint16_t _ring_size;

static uint8_t *_ring_tail;
static uint16_t _ring_capacity;



/* 		Private Function Prototypes
 ******************************************************************************/
static void _write_cmd(char* cmd);
static uint8_t _ring_next();
static void _cmd_next(spirit_cmd_t *command);


/* 		Private Function Definitions
 ******************************************************************************/

/*
 ******************************************************************************/
static void _write_cmd(char* cmd)
{
    if (_command_mode)
    {
        while (*cmd)
        {
            _write(*cmd++);
        }

        _write(_ASCII_CR);
    }
}

/*
 ******************************************************************************/
static uint8_t _ring_next()
{
    uint8_t next;

    next = *(_ring_tail++);
    _ring_size--;

    if(_ring_tail > _ring_end)
    {
        _ring_tail = _ring_begin;
    }

    return next;
}

/*
 ******************************************************************************/
static void _ring_clear()
{
    _ring_tail = _ring_head;
    _ring_size = 0;
}

/*
 ******************************************************************************/
static void _cmd_next(spirit_cmd_t *cmd)
{
    cmd->command = _cmd_tail->command;
    cmd->callback = _cmd_tail->callback;

    _cmd_tail++;
    _cmd_size--;

    if(_cmd_tail > _cmd_end)
    {    
        _cmd_tail = _cmd_begin;
    }
}

/*
 ******************************************************************************/
static uint8_t _process_command_mode()
{
    spirit_cmd_t at_cmd;

    if(_wait_response)
    {
        char next_char;

        if(_ring_size > 0)
        {
            next_char = _ring_next();

            if (next_char == _ASCII_CR)
            {
                if(_on_response(&_response_buffer))
                {
                    _wait_response = false;
                }

                _response_ind = 0;
            }
            else if(next_char != _ASCII_NULL)
            {
                if(_response_ind == _RESPONSE_BUFFER_SIZE) 
                {    
                    return SPIRIT_ERR_RESPONSE_BUFF_FULL;
                }

                if(next_char == _ASCII_LF) 
                {
                    next_char = _ASCII_NULL;
                }

                _response_buffer[_response_ind++] = next_char;
            }
        }
    }
    else
    {
        if (_cmd_size > 0)
        {
            _cmd_next(&at_cmd);
            _write_cmd(at_cmd.command);
            _on_response = at_cmd.callback;
            _wait_response = true;
            _response_ind = 0;
        }
    }

    return SPIRIT_OK;
}

/*
 ******************************************************************************/
static uint8_t _process_operating_mode()
{
    uint8_t *ring_head;

    ring_head = _ring_head;
    _data_ind = 0;

    while ((_ring_tail != ring_head) && (_data_ind < _DATA_BUFFER_SIZE))
    {
        _data_buffer[_data_ind++] = _ring_next();
    }

    if (_data_ind > 0)
    {
        _on_data(&_data_buffer, _data_ind);
    }

    return SPIRIT_OK;
}

/*		Public Function Definitions
 ******************************************************************************/

/*
 ******************************************************************************/
void spirit_init( 
    spirit_uart_write_t uart_write,
    spirit_data_callback_t on_data,
    uint8_t *ring_buffer,
    uint16_t ring_size,
    spirit_cmd_t *cmd_buffer,
    uint8_t cmd_buffer_size
)
{
    _write = uart_write;

    _on_data = on_data;

    // Rx data buffer init
    _ring_begin = ring_buffer;
    _ring_end = &ring_buffer[ring_size - 1];
    _ring_capacity = ring_size;
    _ring_head = _ring_begin;
    _ring_tail = _ring_begin;
    _ring_size = 0;

    // Command buffer init
    _cmd_begin = cmd_buffer;
    _cmd_end = &cmd_buffer[cmd_buffer_size - 1];
    _cmd_capacity = cmd_buffer_size;
    _cmd_head = _cmd_begin;
    _cmd_tail = _cmd_begin;
    _cmd_size = 0;

    _response_ind = 0;
    _data_ind = 0;

    _command_mode = true;
    _wait_response = false;

    memset(_response_buffer, 0x00, _RESPONSE_BUFFER_SIZE);

    SPIRIT_SHD = _WAKEUP;
    SPIRIT_CMD = _COMMAND_MODE;
    SPIRIT_RST = _RESTART;
    spirit_restart(SPIRIT_COMMAND_MODE);
}

/*
 ******************************************************************************/
uint8_t spirit_rx(uint8_t rx_data)
{
    if(_ring_size == _ring_capacity)
    {
        return SPIRIT_ERR_RING_BUFF_FULL;
    }

    *(_ring_head++) = rx_data;
    _ring_size++;

    if(_ring_head > _ring_end)
    {
        _ring_head = _ring_begin;
    }


    return SPIRIT_OK;
}

/*
 ******************************************************************************/
uint8_t spirit_cmd(char* command, spirit_callback_t on_response)
{
    if(_cmd_size == _cmd_capacity)
    {
        return SPIRIT_ERR_FULL_CMD_BUFF;
    }

    _cmd_head->command = command;
    _cmd_head->callback = on_response;

    _cmd_head++;
    _cmd_size++;

    if (_cmd_head > _cmd_end)
    {
        _cmd_head = _cmd_begin;
    }

    return SPIRIT_OK;
}

/*
 ******************************************************************************/
uint8_t spirit_send(uint8_t *buffer, uint16_t size)
{
    if(!_command_mode)
    {
        while(size--)
        {
            _write(*(buffer++));
        }
    }

    return SPIRIT_OK;
}

/*
 ******************************************************************************/
uint8_t spirit_process()
{
    if (_command_mode)
    {
        return _process_command_mode();
    }
    else
    {
        return _process_operating_mode();
    }
}

/*
 ******************************************************************************/
uint8_t spirit_mode(bool command_mode)
{
    _command_mode = command_mode;
    _ring_clear();

    return SPIRIT_OK;
}

/*
 ******************************************************************************/
uint8_t spirit_restart(bool command_mode)
{
    spirit_mode(command_mode);
    spirit_clear_cmd();

    SPIRIT_CMD = !command_mode;
    SPIRIT_RST = _RESTART;
    Delay_ms(100);
    SPIRIT_RST = !_RESTART;
    Delay_ms(100);

    return SPIRIT_OK;
}

/*
 ******************************************************************************/
uint8_t spirit_clear_cmd()
{
    _cmd_tail = _cmd_head;
    _cmd_size = 0;

    _wait_response = false;

    return SPIRIT_OK;
}

/* 								End of File
 ******************************************************************************/