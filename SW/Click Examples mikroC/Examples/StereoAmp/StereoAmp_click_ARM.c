/**
 * @file StereoAmp_click_ARM.c
 * @brief <h2> StereoAmp click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * StereoAmp click board.
 *
 *
 *
 ******************************************************************************/

/**
 * @page        Example
 * @date        7 Dec 2016
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
 * -<b> Dev. Board    </b> :    Hexiwear docking station
 * -<b> Oscillator    </b> :
 * -<b> Ext. Modules  </b> :    StereoAmp click board
 * -<b> SW            </b> :    mikroC PRO for ARM v4.9.0
 *
 */

/******************************************************************************
* Preprocessors Constants
*******************************************************************************/
#define AUTO_WR_BIT

#define INC( x, min, max ) (x) == max ? (x) = max : (x)++
#define DEC( x, min, max ) (x) == min ? (x) = min : (x)--

#define L_INIT_VALUE 10
#define R_INIT_VALUE 10

/******************************************************************************
* Includes
*******************************************************************************/
#include "StereoAmp.h"

#include "hexiwear_uart_messaging.h"
#include "OLED_driver.h"

/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct volume_widget {
    bool active;
    uint8_t x_position;
    uint8_t y_position;
    uint8_t value;
} volume_widget;

/******************************************************************************
* Variable Definitions
*******************************************************************************/

sbit MB1_SCL at PTD_PDORbits.B8;
sbit MB1_SDA at PTD_PDORbits.B9;

sbit RGB_R at PTC_PDORbits.B8;
sbit RGB_B at PTC_PDORbits.B9;

sbit MICROBUS1_AN at PTB_PDIRbits.B2;
sbit MICROBUS1_INT at PTB_PDIRbits.B13;

sbit FAULT_L at MICROBUS1_AN;
sbit FAULT_R at MICROBUS1_INT;

sbit T1 at PTA_PDIRbits.B12;
uint8_t buttonstate_t1 = 0x00;

uint8_t volume_control_L = L_INIT_VALUE;
uint8_t volume_control_R = R_INIT_VALUE;

volume_widget volume_widget_L = {
    true,
    18,
    10,
    L_INIT_VALUE
};

volume_widget volume_widget_R = {
    false,
    66,
    10,
    R_INIT_VALUE
};

volume_widget* active_widget = &volume_widget_L;
uint8_t* active_control = &volume_control_L;
uint8_t active_speaker_addr = LEFT_SPEAKER;

bool power = true;

/***************************************************************************//**
* Public Functions
*******************************************************************************/

/***************************************************************************//**
 *
 */
static void Draw_Arrow( uint8_t x, uint8_t y,  oled_color_t color)
{
    OLED_DrawBox (x, y, 1, 1, color);
    OLED_DrawBox (x - 1, y + 1, 3, 1, color);
    OLED_DrawBox (x - 2, y + 2, 5, 1, color);
}

/**************************************************************************//**
 *
 */
 static void Volume_Widget_Active(volume_widget* widget, bool active )
 {
    uint16_t x = widget->x_position;
    uint16_t y = widget->y_position;
    
    if(widget->active != active) {
        if(active) 
            Draw_Arrow(x + 6, y + 81, OLED_COLOR_BLUE);
        else 
            Draw_Arrow(x + 6, y + 81, OLED_COLOR_BLACK);

        widget->active = active;
    }
 }

/***************************************************************************//**
 *
 */
void Volume_Widget_Init(volume_widget* widget, bool active ) 
{
    uint8_t i;
    uint8_t x = widget->x_position;
    uint8_t y = widget->y_position;

    OLED_DrawBox (x, y, 12, 1, OLED_COLOR_BLUE);
    OLED_DrawBox (x, y + 66, 12, 1, OLED_COLOR_BLUE);
    
    OLED_DrawBox (x + 3, y, 6, 1, OLED_COLOR_BLACK);

    OLED_DrawBox (x, y + 1, 1, 65, OLED_COLOR_BLUE);
    OLED_DrawBox (x + 11, y + 1, 1, 65, OLED_COLOR_BLUE);

    OLED_SetFont(guiFont_Tahoma_8_Regular, OLED_COLOR_BLUE, 0);
    OLED_WriteText(gain_text[widget->value], x - 13, 77);

    widget->active = false;
    Volume_Widget_Active(widget, active);

    for(i = 0; i <= widget->value; i++) {
        OLED_DrawBox(x + 2, y + 64 - i * 2, 8, 1, OLED_COLOR_BLUE);
    }
}

/**************************************************************************//**
 *
 */
void Volume_Widget_Update(volume_widget* widget, uint8_t value) 
{
    uint8_t i;
    uint16_t x = widget->x_position;
    uint16_t y = widget->y_position;

    if(value != widget->value) 
    {
        OLED_SetFont(guiFont_Tahoma_8_Regular, OLED_COLOR_BLACK, 0);
        OLED_WriteText(gain_text[widget->value], x - 13, 77);

        if(value < widget->value) 
        {
            OLED_DrawBox(x + 2, y + 64 - widget->value * 2, 8, 1, OLED_COLOR_BLACK);
        }

        if(value > widget->value) 
        {
            OLED_DrawBox(x + 2, y + 64 - value * 2, 8, 1, OLED_COLOR_BLUE);
        }

        widget->value = value;

        OLED_SetFont(guiFont_Tahoma_8_Regular, OLED_COLOR_BLUE, 0);
        OLED_WriteText(gain_text[widget->value], x - 13, 77);
    }
}

/**************************************************************************//**
 *
 */
static void Gui_Init( void )
{
    OLED_FillScreen(OLED_COLOR_BLACK);

    // Initialise widgets.
    Volume_Widget_Init(&volume_widget_L, volume_widget_L.active);
    Volume_Widget_Init(&volume_widget_R, volume_widget_R.active);
}

/**************************************************************************//**
 *
 */
static void Gui_Standby( void )
{
    OLED_FillScreen(OLED_COLOR_BLACK);
    OLED_SetFont(guiFont_Tahoma_8_Regular, OLED_COLOR_BLUE, 0);
    OLED_WriteText("STANDBY", 27, 40);
}

/***************************************************************************//**
 *
 */
static void Write_Amp_Reg(uint8_t amp_addr, uint8_t reg_addr, uint8_t reg_data) 
{
    char data_write = (reg_addr & REG_ADDR_MASK) | (reg_data & DATA_MASK);
    delay_ms(1);
    I2C0_Start();
    I2C0_Write(amp_addr, &data_write, 1, END_MODE_STOP);
}

/***************************************************************************//**
 *
 */
static void StereoAmp_On() 
{
   // Power On and Input 1 enabled.
    Write_Amp_Reg(LEFT_SPEAKER, MODE_CONTROL_REG, POWER_ON | INPUT1);
    Write_Amp_Reg(RIGHT_SPEAKER, MODE_CONTROL_REG, POWER_ON | INPUT1);

    // Set volume.
    Write_Amp_Reg(LEFT_SPEAKER, VOLUME_CONTROL1_REG, volume_control_L);
    Write_Amp_Reg(RIGHT_SPEAKER, VOLUME_CONTROL1_REG, volume_control_R);

    // Restore diagnostic.
    Write_Amp_Reg(LEFT_SPEAKER, DIAGNOSTIC_CONTROL_REG, DG_RESET );
    Write_Amp_Reg(RIGHT_SPEAKER, DIAGNOSTIC_CONTROL_REG, DG_RESET );
}

/***************************************************************************//**
 *
 */
static void StereoAmp_Off() 
{
   // Power OFF.
    Write_Amp_Reg(LEFT_SPEAKER, MODE_CONTROL_REG, POWER_OFF);
    Write_Amp_Reg(RIGHT_SPEAKER, MODE_CONTROL_REG, POWER_OFF);
}

/***************************************************************************//**
 *
 */
static void StereoAmp_Toggle_Power()
{
    power = !power;
    RGB_B = !RGB_B;

    if(power)
    {
        StereoAmp_On();
        Gui_Init();
    }
    else
    {
        StereoAmp_Off();
        Gui_Standby();
    }
}

/***************************************************************************//**
 *
 */
static void Set_Volume(char amp_addr, char value) 
{
    Write_Amp_Reg(amp_addr, VOLUME_CONTROL1_REG, value);
}

/**************************************************************************//**
 *
 */
static void MCU_Init() 
{
    // IMPORTANT: Toggle I2C lines (PTD8, PTD9), before initialising I2C module 
    // to enable amplifiers.
    GPIO_Digital_Output(&PTD_PDOR, _GPIO_PINMASK_8 | _GPIO_PINMASK_9);
    MB1_SDA = 1;
    MB1_SCL = 1;
    Delay_ms(100);
    MB1_SDA = 0;
    MB1_SCL = 0;
    Delay_ms(100);

    RGB_B = 1;
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_9);
    GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_2 | _GPIO_PINMASK_13);
    GPIO_Digital_Input(&PTA_PDOR, _GPIO_PINMASK_12);

    I2C0_Init_Advanced(I2C_CLK, &_GPIO_Module_I2C0_PD8_9);
    Delay_ms(800);

    OLED_Init();
    OLED_FillScreen(OLED_COLOR_BLACK);

    PORTA_PCR12 |= 0x00000002;
}


/**************************************************************************//**
 *
 */
static void on_press_down( void )
{
    if(!power) return;

    DEC(*active_control, 0, 31);
    Volume_Widget_Update(active_widget, *active_control);
    Set_Volume(active_speaker_addr, *active_control);
}

/**************************************************************************//**
 *
 */
static void on_press_up( void )
{
    if(!power) return;

    INC(*active_control, 0, 31);
    Volume_Widget_Update(active_widget, *active_control);
    Set_Volume(active_speaker_addr, *active_control);
}

/**************************************************************************//**
 *
 */
static void on_press_left( void )
{
    if(!power) return;

    active_control = &volume_control_L;
    active_widget = &volume_widget_L;
    active_speaker_addr = LEFT_SPEAKER;

    Volume_Widget_Active(&volume_widget_L, true);
    Volume_Widget_Active(&volume_widget_R, false);
}

/**************************************************************************//**
 *
 */
static void on_press_right( void )
{
    if(!power) return;

    active_control = &volume_control_R;
    active_widget = &volume_widget_R;
    active_speaker_addr = RIGHT_SPEAKER;

    Volume_Widget_Active(&volume_widget_L, false);
    Volume_Widget_Active(&volume_widget_R, true);
}

/**************************************************************************//**
 *
 */
static void system_init( void )
{
    // Initialize I2C and I/O ports.
    MCU_Init();
    // Initialize StereoAmp click.
    StereoAmp_On();
    // Initialize MKW40 UART messaging.
    hexiwear_uart_messaging_init();

    // Register touch interface callbacks.
    hexiwear_uart_messaging_callback(PT_PRESS_DOWN,  on_press_down  );
    hexiwear_uart_messaging_callback(PT_PRESS_UP,    on_press_up    );
    hexiwear_uart_messaging_callback(PT_PRESS_LEFT,  on_press_left  );
    hexiwear_uart_messaging_callback(PT_PRESS_RIGHT, on_press_right );
   
    // Initialise widgets.
    Gui_Init();
}

/**************************************************************************//**
 *
 */
uint8_t button_pressed(uint8_t state, uint8_t* old_state)
{
    if(!state && *old_state)
    {
        *old_state = state;
        return 0xFF;
    }

    *old_state = state;
    return 0x00;
}

/**************************************************************************//**
 *
 */
void main() 
{
    system_init();

    while(1) {
        if (button_pressed(T1, &buttonstate_t1))
            StereoAmp_Toggle_Power();
        
        hexiwear_uart_messaging_process();

        Delay_ms(10);
    }
}
/*************** END OF FUNCTIONS *********************************************/