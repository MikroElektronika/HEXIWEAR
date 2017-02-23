/**
 * @file LCD_mini_click.c
 * @brief <h2> LCD mini click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * LCD mini click board.
 *
 *
 *
 ******************************************************************************/

/**
 * @page Example
 * @date        14 Dec 2016
 * @author      Branislav Marton
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 *
 * ### Test configuration STM : ###
 * @par
 * -<b> MCU           </b> :    MK64FN1M0XXX12
 * -<b> Dev. Board    </b> :    Hexiwear docking station
 * -<b> Ext. Modules  </b> :    LCD mini click
 * -<b> SW            </b> :    mikroC PRO for ARM v.4.9.0
 *
 */

/**
 * @page Dev. board setup
 *
 * 1) Put LCD mini click into mikroBUS 3 slot.
 *
 */


/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>

/******************************************************************************
* Preprocessors
*******************************************************************************/


/******************************************************************************
* Typedefs
*******************************************************************************/


/******************************************************************************
* Variable Definitions
*******************************************************************************/
sbit DigPot_CS      at  PTB_PDOR.B6;

sbit SPExpanderRST  at  PTB_PDOR.B10;
sbit SPExpanderCS   at  PTC_PDOR.B2;

static uint8_t value = 0x00;

static unsigned int pwm_period;

sbit LED  at  PTA_PDOR.B13;
/******************************************************************************
* Function Prototypes
*******************************************************************************/

static void system_init( void );
static void set_contrast( uint8_t value );
static void set_bcklight( uint8_t value );

/******************************************************************************
* Private Functions
*******************************************************************************/

/**************************************************************************//**
 *
 */
static void system_init( void )
{
    DigPot_CS = 1;
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_6 );
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_13 );

    // Initialise PWM for controlling back light.
    pwm_period = PWM_FTM0_Init(
        1000,
        _PWM_EDGE_ALIGNED_PWM,
        _PWM_CHANNEL_1,
        &_GPIO_Module_PWM0_PTA4
    );

    PWM_FTM0_Start(_PWM_CHANNEL_1);

    // Initialise SPI.
    SPI0_Init_Advanced(
        4000000,
        _SPI_CFG_MASTER | 
        _SPI_CFG_FRAME_SIZE_8BITS | 
        _SPI_CFG_CLK_IDLE_LOW | 
        _SPI_CFG_CLK_PHASE_CAPT_LEADING | 
        _SPI_CFG_MSB_FIRST, 
        &_GPIO_Module_SPI0_PC5_7_6
    );

    SPI_Lcd_Config(0);
    SPI_Lcd_Cmd(_LCD_CLEAR); 
    SPI_Lcd_Cmd(_LCD_CURSOR_OFF);
}

/**************************************************************************//**
 *
 */
static void set_contrast( uint8_t value )
{
    DigPot_CS = 0;

    SPI0_Write(0x00);
    SPI0_Write(~value);

    DigPot_CS = 1;
}

/**************************************************************************//**
 *
 */
static void set_bcklight( uint8_t value )
{
    PWM_FTM0_Set_Duty(
        (uint16_t) floor(~value / 255.0f * 128),
        _PWM_INVERTED, 
        _PWM_CHANNEL_1
    );
}

/******************************************************************************
* Public Functions
*******************************************************************************/

void main()
{
    system_init();
    
    SPI_Lcd_Out(1, 6,     "mikroE"     );
    SPI_Lcd_Out(2, 2, "LCD mini click" );

    set_bcklight(0xFF);
    set_contrast(0xDF);
    
    Delay_ms(5000);

    while (1)
    {
        set_bcklight(value);
        set_contrast(value);
        
        value++;
        if(value == 0) LED = !LED;
        delay_ms(40);
    }
}

/*************** END OF FUNCTIONS *********************************************/