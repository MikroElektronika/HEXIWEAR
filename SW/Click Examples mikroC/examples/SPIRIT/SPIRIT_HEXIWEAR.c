/*
 * Example for SPIRIT click click
 *
 * Date         Feb 2017
 * Author       Branislav M.
 * Copyright    GNU Public License v2
 *
 * Test configuration Kinetis :
 *  MCU           :        MK64FN1M0XXX12
 *  Dev. Board    :        EasyMx PRO v7 for STM32 ARM
 *  SW            :        mikroC PRO for ARM v4.9.0
 *
 *
 ******************************************************************************/

#include "log.h"

#include "spirit.h"

/*  Preprocessors
 ******************************************************************************/

#define _ASCII_CR (0x0D)
#define _ASCII_NULL (0x00)
#define _ASCII_ESCAPE (0x1B)

#define RING_BUFFER_SIZE (256)
#define CMD_BUFFER_SIZE (8)


/* Variables
 ******************************************************************************/
sbit SPIRIT_RST at PTB_PDOR.B11;
sbit SPIRIT_CMD at PTC_PDOR.B4;
sbit SPIRIT_SHD at PTA_PDOR.B10;


typedef struct
{
    char buffer[256];
    uint8_t size;
} message_t;

static message_t rx_message;
static message_t tx_message;

static bool broadcast_flag;
static bool read_info;


static uint8_t ring_buffer[RING_BUFFER_SIZE];
static spirit_cmd_t cmd_buffer[CMD_BUFFER_SIZE];

static uint8_t Snn;

/* Function declarations
 ******************************************************************************/
static void system_init( void );
static void on_data(uint8_t *buffer, uint8_t size);
static void on_response(char* response);
static bool on_ato(char* response);
static bool on_read_conf(char* response);


/* Callbacks
 ******************************************************************************/
static void on_data(uint8_t *buffer, uint8_t size)
{
    while (size--)
    {
        if (*buffer == _ASCII_NULL)
        {
            rx_message.buffer[rx_message.size++] = _ASCII_NULL;

            LOG_RULE();
            LOG_INFO("Message recieved.");
            LOG_INFO(rx_message.buffer);
            LOG_RULE();

            rx_message.size = 0;
        }
        else
        {
            rx_message.buffer[rx_message.size++] = *(buffer++);
        }
    }
}

static bool on_response(char* response)
{
    LOG_RULE();
    LOG_INFO("On response");
    LOG_INFO(response);
    LOG_RULE();

    return true;
}

static bool on_ato(char* response)
{
    LOG_RULE();

    if(strcmp(response, "OK") == 0)
    {
        LOG_INFO("Entered operation mode.");

        spirit_mode(SPIRIT_OPERATING_MODE);
    }
    else
    {
        LOG_ERROR("Failed to enter to operation mode...");
    }

    LOG_RULE();
    return true;
}

static bool on_read_conf(char* response)
{
    if (Snn == 0)
    {
        LOG_RULE();
        LOG_INFO("Configuration registers.");    
        LOG_RULE();
    }

    LOG_INFO(response);

    if (Snn == 28)
    {
        LOG_RULE();
        // Return true to notify library that this is the 
        // last expected response from AT/S command.
        return true;
    }

    Snn++;
    
    // Return false to notify library that you expect more responses 
    // from AT/S command.
    return false;
}

static bool on_read_info(char* response)
{
    if (strstr(response, "I0:") != 0)
    {
        LOG_RULE();
        LOG_INFO("Inforamtion registers.");
        LOG_RULE();
    }

    LOG_INFO(response);

    if (strstr(response, "I2:") != 0)
    {
        LOG_RULE();
        // Exit command mode after last inforamtion register.
        spirit_cmd("ATO", on_ato);
    }
    
    return true;
}

/* System initialization.
 ******************************************************************************/
static void system_init( void )
{
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_10 );

    LOG_INIT(460800);

    UART2_Init_Advanced( 
        115200, 
        _UART_8_BIT_DATA, 
        _UART_NOPARITY,
        _UART_ONE_STOPBIT,
        &_GPIO_Module_UART2_PD3_2
    );

    UART2_C2 |= 1 << 5;
    NVIC_IntEnable( IVT_INT_UART2_RX_TX );
    UART3_C2 |= 1 << 5;
    NVIC_IntEnable( IVT_INT_UART3_RX_TX );
    EnableInterrupts();

    spirit_init(
        UART2_Write,
        on_data,
        ring_buffer,
        RING_BUFFER_SIZE,
        cmd_buffer,
        CMD_BUFFER_SIZE
    );

    rx_message.size = 0;
    tx_message.size = 0;

    broadcast_flag = false;
    read_info = false;
    Snn = 0;
    
    LOG_INFO("System initialized.");
}

/* main
 ******************************************************************************/
void main()
{
    system_init();

    spirit_restart(SPIRIT_COMMAND_MODE);

    // Push commands to queue.
    spirit_cmd("AT/V", on_response);    // Read SW/HW module version.
    spirit_cmd("ATS24=1", on_response); // TX/RX LED on.
    spirit_cmd("ATS02=38400", on_response); // Data rate.
    spirit_cmd("ATS28=96", on_response);// Packet size.
    spirit_cmd("AT/C", on_response);    // Save configuration to EEPROM 
    spirit_cmd("AT/S", on_read_conf);   // Read all configuartion registers.
    spirit_cmd("ATO", on_ato);  // Enter operating mode.

    while( 1 )
    {
        spirit_process();

        // Press ENTER button to broadcast message.
        if (broadcast_flag)
        {
            spirit_send(tx_message.buffer, tx_message.size);

            LOG_RULE();
            LOG_INFO("Message sent.");    
            LOG_INFO(tx_message.buffer);    
            LOG_RULE();

            tx_message.size = 0;
            broadcast_flag = false;
        }

        // Press ESC button to read configuration registers.
        if (read_info)
        {
            spirit_restart(SPIRIT_COMMAND_MODE);
            
            spirit_cmd("ATI0", on_read_info);
            spirit_cmd("ATI1", on_read_info);
            spirit_cmd("ATI2", on_read_info);
            read_info = false;
        }
    }
}

/* ISR
 ******************************************************************************/

// SPIRIT click UART
void RX2_ISR() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
    char s1 = UART2_S1;
    char data_reg = UART2_D;

    if(  s1 & ( 1 << 5 )  )
    {
        spirit_rx(data_reg);
    }
}

// Terminal UART
void RX3_ISR() iv IVT_INT_UART3_RX_TX ics ICS_AUTO
{
    char s1 = UART3_S1;
    char input_char = UART3_D;

    if(  s1 & ( 1 << 5 )  )
    {
        if (input_char == _ASCII_CR)
        {
            broadcast_flag = true;
            tx_message.buffer[tx_message.size++] = _ASCII_NULL;
        }
        else if(input_char == _ASCII_ESCAPE)
        {
            read_info = true;
        }
        else
        {
            tx_message.buffer[tx_message.size++] = input_char;
        }
    }
}

/************************************************************ END OF FILE *****/