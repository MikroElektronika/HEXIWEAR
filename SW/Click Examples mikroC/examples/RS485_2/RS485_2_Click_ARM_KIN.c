/*
 * Example for RS485 2 Click
 *
 * Date         APR 2017
 * Author       Branislav M.
 *
 * Test configuration KINETIS :
 *  MCU           :        MK64
 *  Dev. Board    :        HEXIWEAR
 *  SW            :        mikroC PRO for ARM v5.1.0
 *
 * Description :
 * The example is simple master/slave communication. The Master uses input pin 
 * to toggle LED and sends command to a slave. The slave receives an command and
 * turn on/off LED.
 * In RS485_2_Click_ARM_STM.pld define MASTER_NODE to build node as master.
 *
 ******************************************************************************/

#include "__RS485_2_Driver.h"
#include "hexiwear_uart_messaging.h"

#ifndef MASTER_NODE
#define SLAVE_NODE (1)
#endif

#define LED_ON (0)
#define LED_OFF (1)

#define CMD_R (0x01)
#define CMD_G (0x02)
#define CMD_B (0x03)


sbit _RS485_2_DE_PIN at PTC_PDOR.B4;
sbit _RS485_2_RE_PIN at PTA_PDOR.B10;

sbit BUTTON_PIN at PTA_PDIR.B12;

sbit LED_R_PIN at PTC_PDOR.B8;
sbit LED_G_PIN at PTD_PDOR.B0;
sbit LED_B_PIN at PTC_PDOR.B9;

#ifdef MASTER_NODE
static uint8_t ledState;
#endif

static uint8_t cmdBuf;

static void setLeds(uint8_t cmd)
{
    LED_R_PIN = LED_OFF;
    LED_G_PIN = LED_OFF;
    LED_B_PIN = LED_OFF;

    switch (cmd)
    {
    case CMD_R: LED_R_PIN = LED_ON;
        break;
    case CMD_G: LED_G_PIN = LED_ON;
        break;
    case CMD_B: LED_B_PIN = LED_ON;
        break;
    default:
        break;
    }
}

#ifdef MASTER_NODE    
void decState( void )
{
    if (ledState == CMD_R)
        ledState = CMD_B;
    else
        ledState--;
}
#endif

#ifdef MASTER_NODE    
void incState( void )
{
    if (ledState == CMD_B)
        ledState = CMD_R;
    else
        ledState++;
}
#endif

#ifdef MASTER_NODE    
void handlePressUp( void )
{
    incState(); 
    setLeds(ledState);
    RS485_2_transmit(&ledState, 1);
}
#endif

#ifdef MASTER_NODE    
void handlePressDown( void )
{
    decState(); 
    setLeds(ledState);
    RS485_2_transmit(&ledState, 1);
}
#endif

/*
 * System Initialization
 */
void systemInit()
{
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 ); // _RS485_2_DE_PIN
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_10 ); // _RS485_2_RE_PIN

    LED_R_PIN = LED_OFF;
    LED_G_PIN = LED_OFF;
    LED_B_PIN = LED_OFF;
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_8 ); // LED_PIN
    GPIO_Digital_Output( &PTD_PDOR, _GPIO_PINMASK_0 ); // LED_PIN
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_9 ); // LED_PIN

    
#ifdef MASTER_NODE    
    hexiwear_uart_messaging_callback( PT_PRESS_UP,  handlePressUp );
    hexiwear_uart_messaging_callback( PT_PRESS_DOWN,  handlePressDown );
#endif

    UART2_Init_Advanced( 
        115200, 
        _UART_8_BIT_DATA, 
        _UART_NOPARITY,
        _UART_ONE_STOPBIT,
        &_GPIO_Module_UART2_PD3_2
    );


    RS485_2_driverInit(UART2_Write, UART2_Tx_Idle);

#ifdef MASTER_NODE
    ledState = CMD_R;
    setLeds(CMD_R);
    RS485_2_transmit(&ledState, 1);

    hexiwear_uart_messaging_init();
#endif

    // IE init 
#ifdef SLAVE_NODE    
    UART2_C2 |= 1 << 5;
    NVIC_IntEnable( IVT_INT_UART2_RX_TX );
#endif    
    EnableInterrupts();
}


void main()
{
    systemInit();

    while( 1 )
    {
#ifdef MASTER_NODE
        hexiwear_uart_messaging_process();
#endif
    }
}

#ifdef SLAVE_NODE    
void RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
    char s1 = UART2_S1;
    char rxByte = UART2_D;

    if(  s1 & ( 1 << 5 )  )
    {
        setLeds(rxByte);
    }
}
#endif
/************************************************************ END OF FILE *****/