/**
 * @file HEXIWEAR_GSM_GNSS_Click.c
 * @brief <h2> GSM/GNSS click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * GSM/GNSS click board. 
 *
 *
 *
 ******************************************************************************/

/**
 * @page        Example
 * @date        23 Nov 2016
 * @author      Branislav Marton
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 *
 * ### Test configuration STM : ###
 * @par
 * -<b> MCU           </b> :    STM32F207VG
 * -<b> Dev. Board    </b> :    EasyMx v7 for STM32
 * -<b> Ext. Modules  </b> :    GSM/GNSS click
 * -<b> SW            </b> :    mikroC PRO for ARM v4.9.0
 *
 */

/**
 * @page Dev. board setup
 *
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "gsm_gnss_click.h"

#include "log.h"
#include "hexiwear_gsm_gnss_gui.h"

#include "hexiwear_uart_messaging.h"

/******************************************************************************
* Preprocessors
*******************************************************************************/

#define LOG_BAUD_RATE    115200
#define MKW40_BAUD_RATE  230400

#define R_LED_BLINK_RATE    150
#define R_LED_BLINK_COUNT   4
#define VIBRATE_DURATION    50

#define MSG_COUNT 5

#define INC( x, min, max ) x == (max - 1) ? x = min : x++
#define DEC( x, min, max ) x == min ? x = max - 1 : x--

/******************************************************************************
* Typedefs
*******************************************************************************/


/******************************************************************************
* Constants Definitions
*******************************************************************************/

// Enter phone number.
static const char phone_number[10] = ___ENTER_YOUR_PHONE_NUMBER_HERE___;


static const char* gui_msg[MSG_COUNT][5] = {
    {"I need your", "help.", "\r"},
    {"Call the", "doctor!", "\r"},
    {"Visit me.", "\r"},
    {"Call me.", "\r"},
    {"Buy bread", "and milk.", "\r"}
};

static const char* msg[MSG_COUNT] = {
    "I need your help.",
    "Call the doctor!",
    "Visit me.",
    "Call me.",
    "Buy bread and milk."
};

/******************************************************************************
* Variable Definitions
*******************************************************************************/
sbit GSM_PWR    at PTB_PDOR.B11;
sbit GSM_CTS    at PTB_PDOR.B13;
sbit GSM_RTS    at PTC_PDIR.B4;
sbit GSM_RING   at PTA_PDIR.B10;
sbit GSM_STAT   at PTB_PDIR.B2;

sbit R_LED    at PTC_PDOR.B8;
sbit G_LED    at PTD_PDOR.B0;
sbit B_LED    at PTC_PDOR.B9;

sbit VIBRO    at PTB_PDOR.B9;


static uint8_t msg_index = 0;

static bool sending = false;

char msg_buffer[256];   
char url_buffer[128];    

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void rgb_led_blink( bool, bool, bool );
static void vibrate( void );

/******************************************************************************
* Private Functions
*******************************************************************************/

/**
 *
 */
static void system_init()
{
    // mikroBUS 1 - RST
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_11 );
    // mikroBUS 1 - CS
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );
    // mikroBUS 1 - PWM
    GPIO_Digital_Input( &PTA_PDIR, _GPIO_PINMASK_10 );
    // mikroBUS 1 - AN and INT
    GPIO_Digital_Input( &PTB_PDIR, _GPIO_PINMASK_13 | _GPIO_PINMASK_2 );
    
    // PC11 - RGB LEDs and VIBRO
    R_LED = 1;
    G_LED = 1;
    B_LED = 1;
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_8 );
    GPIO_Digital_Output( &PTD_PDOR, _GPIO_PINMASK_0 );
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_9 );
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_9 );

    log_init(LOG_BAUD_RATE);
    Delay_ms( 100 );

    hexiwear_uart_messaging_init();

    // GSM/GNSS module communication.
    UART2_Init_Advanced(
        GSM_MODEM_BAUD_RATE, 
        _UART_8_BIT_DATA,
        _UART_NOPARITY,
        _UART_ONE_STOPBIT,
        &_GPIO_Module_UART2_PD3_2
    );
    Delay_ms( 100 );

    UART2_C2 |= 1 << 5;
    NVIC_IntEnable( IVT_INT_UART2_RX_TX );

    EnableInterrupts();

    OLED_Init();
    //strcpy(phone_number, _PHONE_NUMBER_);

    log_info("System initialised.");
}

/**
 *
 */
static void rgb_led_blink( bool r, bool g, bool b )
{
    uint8_t i = 0;

    R_LED = 1;
    G_LED = 1;
    B_LED = 1;

    for (; i < R_LED_BLINK_COUNT * 2; i++)
    {
        if(r) R_LED = ~R_LED; 
        if(g) G_LED = ~G_LED; 
        if(b) B_LED = ~B_LED; 
        
        Delay_ms(R_LED_BLINK_RATE);   
        if(i == 3)    
            Delay_ms(R_LED_BLINK_RATE * 2);   
    }
}

static void vibrate( void )
{
    VIBRO = 1;
    Delay_ms(VIBRATE_DURATION);
    VIBRO = 0;
}

static void sms_delivered( void )
{
    hexiwear_gsm_gnss_gui_draw_msg_select_page( gui_msg[msg_index] );
    rgb_led_blink(false, true, true);

    sending = false;
}

static void sms_failed( void )
{
    hexiwear_gsm_gnss_gui_draw_msg_select_page( gui_msg[msg_index] );
    rgb_led_blink(true, false, false);

    sending = false;
}

static void sms_sent( void )
{

}

static void sms_confirmed( void )
{

}

static void on_button_down( void )
{
    if(sending) return;

    vibrate();

    INC(msg_index, 0, MSG_COUNT);
    hexiwear_gsm_gnss_gui_write_msg( gui_msg[msg_index] );
}

static void on_button_up( void )
{
    if(sending) return;

    vibrate();

    DEC(msg_index, 0, MSG_COUNT);
    hexiwear_gsm_gnss_gui_write_msg( gui_msg[msg_index] );
}

static void on_button_left( void )
{
    if(sending) return;
    
    vibrate();

    gsm_gnss_click_read_nav( url_buffer );

    sprintf(msg_buffer, "%s\r\n\r\n%s", msg[msg_index], url_buffer);

    hexiwear_gsm_gnss_gui_draw_sending_page();
    gsm_gnss_click_send_sms(phone_number, msg_buffer);

    sending = true;
}

static void on_button_right( void )
{
    gsm_gnss_click_read_nav( url_buffer );
    log_info(url_buffer);
}

/******************************************************************************
* Public Functions
*******************************************************************************/

/******************************************************************************
* Main Function
*******************************************************************************/

void main( void )
{
    system_init();

    hexiwear_gsm_gnss_gui_init();

    gsm_gnss_click_init();
    gsm_gnss_click_configure_callbacks(
        sms_sent, 
        sms_delivered, 
        sms_failed, 
        sms_confirmed
    );

    hexiwear_gsm_gnss_gui_clear_page();
    rgb_led_blink(true, true, true);

    hexiwear_gsm_gnss_gui_draw_msg_select_page( gui_msg[msg_index] );

    hexiwear_uart_messaging_callback(PT_PRESS_DOWN, on_button_down );
    hexiwear_uart_messaging_callback(PT_PRESS_UP, on_button_up );
    hexiwear_uart_messaging_callback(PT_PRESS_LEFT, on_button_left );
    hexiwear_uart_messaging_callback(PT_PRESS_RIGHT, on_button_right );

    while(1)
    {
        gsm_gnss_click_process();
        hexiwear_uart_messaging_process();
    }
}

/*************** END OF FUNCTIONS *********************************************/