/**
 * @file main.c
 * @brief <h2> 16x9 G click click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * 16x9 G click click board.
 *
 *
 *
 ******************************************************************************/

/**
 * @page        Example
 * @date        12 Jan 2017
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
 * -<b> Dev. Board    </b> :    HEXIWEAR DOCKING STATION
 * -<b> Ext. Modules  </b> :    16x9 G click
 * -<b> SW            </b> :    mikroC PRO for ARM v.4.9.0
 *
 */

/**
 * @page Dev. board setup
 *
 * Insert 16x9 click board into mikroBUS 1 slot.
 */

/***************************************************************************//**
* Includes
*******************************************************************************/

#include "click_16x9.h"

/***************************************************************************//**
* Preprocessors
*******************************************************************************/

/***************************************************************************//**
* Typedefs
*******************************************************************************/

/***************************************************************************//**
* Constant Definitions
*******************************************************************************/

const code uint8_t gamma[] =
{
    0, 1,2, 4, 6, 10, 13, 18, 22, 28, 33, 39, 46, 53, 61, 69, 78, 86, 96, 106,
    116, 126, 138, 149, 161, 173, 186, 199, 212, 226, 240, 255
};

/***************************************************************************//**
* Variable Definitions
*******************************************************************************/

sbit CLICK_16x9_SDB at PTC_PDOR.B4;  

uint8_t frame = 0;
uint8_t radius = 0;
uint8_t x = 0;
uint8_t y = 0;

/***************************************************************************//**
* Function Prototypes
*******************************************************************************/

static void system_init( void );

/***************************************************************************//**
* Private Functions
*******************************************************************************/

static void system_init( void )
{
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_4 );

    I2C0_Init_Advanced( 400000, &_GPIO_Module_I2C0_PD8_9 );
    click_16x9_init(0x74);
}

/***************************************************************************//**
* Public Functions
*******************************************************************************/

void main()
{
    system_init();

    // Hardware power on.
    click_16x9_shutdown_hw(false);
    // Software shutdown mode.
    click_16x9_shutdown_sw(true);

    // Turn on all LED's in frame 1.
    click_16x9_begin_frame(FRAME_1);
    {
        click_16x9_control_all(CTRL_LED, true);
        click_16x9_fill_screen(0x00);
    }
    click_16x9_end_frame();

    // Turn on all LED's in frame 2.
    click_16x9_begin_frame(FRAME_2);
    {
        click_16x9_control_all(CTRL_LED, true);
        click_16x9_fill_screen(0x00);
    }
    click_16x9_end_frame();

    // Software normal operation mode.
    click_16x9_shutdown_sw(false);

    while (1)
    {
        radius = frame = 0;
        x = rand() % 9;
        y = rand() % 16;

        // Uses swap chain to display frames.
        while (radius <= 15)
        {
            click_16x9_begin_frame((frame_t)(frame % 2 + 1));
            {
                click_16x9_fill_screen(0x00);
                click_16x9_circle(x, y, radius, gamma[(15 - radius++) * 2]);
            }
            click_16x9_end_frame();

            // Swap frame.
            click_16x9_func_reg(REG_PICTURE_DISPLAY, frame++ % 2);
            Delay_ms(50);
        }
    }
}

/*************** END OF FUNCTIONS *********************************************/