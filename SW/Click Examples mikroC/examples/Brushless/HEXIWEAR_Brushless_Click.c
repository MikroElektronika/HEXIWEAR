/*******************************************************************************
  * Title                 :   HEXIWEAR / Brushless Click / DOCKING STATION
  * Filename              :   HEXIWEAR_Brushless_Click.c
  * Author                :   Stefan Popovic
  * Origin Date           :   12/08/2016
  * Notes                 :   
                              - This example demonstrates controlling of BLDC
                                motor rpm using buttons on Hexiwear
                              - Place Brushless Click Board on mikroBUS slot 3
                              - Get external voltage supply for Brushless Click
                              - Connect BLDC motor on U, V and W screw terminal
/******************************************************************************
* Includes
*******************************************************************************/
#include "OLED_driver.h"
#include "OLED_resources.h"
#include "UART_Messaging.h"
#include "common_screen_objects.h"
#include <stdbool.h>
#include <stdint.h>
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define CW 0x01
#define CCW 0x00
#define STEP 2
#define MAX_PWM_VALUE 80
/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
sbit MOTOR_DIR at PTB_PTOR.B10;
sbit R_LED at PTC_PDOR.B8;
sbit G_LED at PTD_PDOR.B0;
sbit B_LED at PTC_PDOR.B9;

uint16_t current_duty;
uint16_t pwm_period;
uint8_t adc_read;
char txt_value[10];
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/

void system_init()
{
    // OLED Init
    OLED_Init();
    OLED_FillScreen(OLED_COLOR_BLACK);

    // GPIO Init
    R_LED = 1;
    G_LED = 1;
    B_LED = 1;
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_8);
    GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_0);
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_9);
    GPIO_Analog_Input(&PTB_PDIR, _GPIO_PINMASK_6);    // AN
    GPIO_Analog_Input(&PTB_PDIR, _GPIO_PINMASK_7);    // INT
    GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_4);  // PWM
    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_9);  // Vibration PIN
    PTB_PDOR = 0;

    // PWM Init
    current_duty = 0;
    pwm_period = PWM_FTM0_Init(200,
                               _PWM_EDGE_ALIGNED_PWM,
                                _PWM_CHANNEL_1, 
                                &_GPIO_Module_PWM0_PTA4);
    PWM_FTM0_Set_Duty(0, _PWM_NON_INVERTED, _PWM_CHANNEL_1);   // Set duty ratio
    PWM_FTM0_Start(_PWM_CHANNEL_1);

    Delay_ms(100);

    // Display text
    OLED_DrawBox(0, 0, 96, 15, OLED_COLOR_BLUE);
    OLED_DrawBox(0, 80, 96, 15, OLED_COLOR_BLUE);
    OLED_SetFont(guiFont_Exo_2_Condensed10x16_Regular, OLED_COLOR_WHITE, 0);
    OLED_WriteText("BRUSHLESS", 20, 0);
    OLED_WriteText("Period:", 5, 30);
    OLED_WriteText("Duty:", 5, 50);
    OLED_WriteText("DEC", 15, 80);
    OLED_WriteText("INC", 63, 80);
    WordToStr(pwm_period, txt_value);
    OLED_WriteText(txt_value, 50, 30);
    WordToStr(current_duty, txt_value);
    OLED_WriteText(txt_value, 50, 50);

    hexiwear_uart_messaging_init();              // Init UART messaging
    MOTOR_DIR = CCW;                             // Setting motor direction 
                                                 //  to counter-clock-wise
}
// On button left pressed
static void button_left(void)
{

    R_LED = 0;                                   // Turn on Red diode
    G_LED = 1;                                   // Turn off Green diode
    PTB_PDOR.B9 = 1;                             // Turn on vibration
    current_duty = current_duty - STEP;          // Decrement current_duty
    if (current_duty > MAX_PWM_VALUE)            // If we decrease current_duty 
                                                 //  greater then possible
                                                 //  MAX_PWM_VALUE value (overflow)
    {
        current_duty = 0;                        // Set current_duty to 0
    }

    // Set newly acquired duty ratio
    PWM_FTM0_Set_Duty(current_duty, _PWM_NON_INVERTED, _PWM_CHANNEL_1);  
    OLED_DrawBox(50, 50, 25, 20, OLED_COLOR_BLACK);
    WordToStr(current_duty, txt_value);
    OLED_WriteText(txt_value, 50, 50);           // Write text value on screen
    Delay_ms(50);
    PTB_PDOR.B9 = 0;                             // Turn off vibration 
}
// On button right pressed
static void button_right(void)
{
    
    G_LED = 0;                                   // Turn on Green diode
    R_LED = 1;                                   // Turn off Red diode
    PTB_PDOR.B9 = 1;                             // Turn on Vibration
    current_duty = current_duty + STEP;          // Increment current_duty
    if (current_duty > MAX_PWM_VALUE)            // If we increase current_duty greater 
                                                 //  then possible MAX_PWM_VALUE value
    {
        current_duty = MAX_PWM_VALUE;            // Reset current_duty value 
                                                 //  to MAX_PWM_VALUE
    }
    
    // Set newly acquired duty ratio
    PWM_FTM0_Set_Duty(current_duty, _PWM_NON_INVERTED, _PWM_CHANNEL_1);  
    OLED_DrawBox(50, 50, 25, 20, OLED_COLOR_BLACK);
    WordToStr(current_duty, txt_value);          
    OLED_WriteText(txt_value, 50, 50);           // Write text value on screen
    Delay_ms(50);
    PTB_PDOR.B9 = 0;                             // Turn off vibration 
}

void main()
{
    system_init();
    Delay_ms(100);
    hexiwear_uart_messaging_callback(PT_PRESS_LEFT, button_left);
    hexiwear_uart_messaging_callback(PT_PRESS_RIGHT, button_right);
    
    // Listening for button actions
    while (1)                                 
    {
        hexiwear_uart_messaging_process();
    }
}