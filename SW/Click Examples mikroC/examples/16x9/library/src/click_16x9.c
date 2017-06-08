/**
 * click_16x9.c
 *
 * @brief <h2> 16x9 click Example </h2>
 *
 * @par
 * Example for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * 16x9 click board.
 *
 *
 *
 ******************************************************************************/

/**
 * @page        Example
 * @date        13 Jan 2017
 * @author      Branislav Marton
 * @copyright   GNU Public License
 * @version     1.0.0 - Initial testing and verification
 */

/***************************************************************************//**
* Includes
*******************************************************************************/
#include "click_16x9.h"
#include "click_16x9_hal.h"
 
/***************************************************************************//**
* Preprocessors
*******************************************************************************/

#define PAGE_NINE  0x0B

#define SSD_SHUTDOWN_MODE       0x00
#define SSD_NORMAL_OPERATION    0x01

#define FRAME_MASK  0x07

#define REG_COMMAND 0xFD

/***************************************************************************//**
* Typedefs
*******************************************************************************/

/***************************************************************************//**
* Constant Definitions
*******************************************************************************/

/***************************************************************************//**
* Variable Definitions
*******************************************************************************/

extern sfr sbit CLICK_16x9_SDB;

static uint8_t i2c_addr_;

static bool func_reg_avaliable;

static uint8_t tmp_buffer[145];

/***************************************************************************//**
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Private Functions
*******************************************************************************/

/***************************************************************************//**
* Public Functions
*******************************************************************************/

void click_16x9_init( uint8_t i2c_addr )
{
    i2c_addr_ = i2c_addr;

    hal_16x9_init();

    click_16x9_end_frame();

    CLICK_16x9_SDB = 0;
    func_reg_avaliable = false;
}

void click_16x9_shutdown_hw(bool flag)
{
    CLICK_16x9_SDB = flag ? 0 : 1;
}

void click_16x9_shutdown_sw(bool flag)
{
    click_16x9_func_reg(
        REG_SHUTDOWN, 
        flag ? SSD_SHUTDOWN_MODE : SSD_NORMAL_OPERATION
    );
}

void click_16x9_func_reg(uint8_t reg, uint8_t data_)
{
    if(!func_reg_avaliable) return;

    tmp_buffer[0] = reg;
    tmp_buffer[1] = data_;

    hal_16x9_write(i2c_addr_, tmp_buffer, 2);
}

void click_16x9_begin_frame(frame_t frame)
{
    func_reg_avaliable = false;

    tmp_buffer[0] = REG_COMMAND;
    tmp_buffer[1] = ((uint8_t)frame - 1) & FRAME_MASK;

    hal_16x9_write(i2c_addr_, tmp_buffer, 2);
}

void click_16x9_end_frame()
{
    func_reg_avaliable = true;

    tmp_buffer[0] = REG_COMMAND;
    tmp_buffer[1] = PAGE_NINE;

    hal_16x9_write(i2c_addr_, tmp_buffer, 2);
}


void click_16x9_control_all(control_t ctrl, bool state)
{
    if( ctrl == CTRL_LED )
        tmp_buffer[ 0 ] = 0x00;
    else
        tmp_buffer[ 0 ] = 0x12;
    memset(tmp_buffer + 1, state ? 0xFF : 0x00, 18);
    hal_16x9_write(i2c_addr_, tmp_buffer, 19); 
}

void click_16x9_control(control_t ctrl, uint8_t column, uint16_t states)
{
    tmp_buffer[0] = ( ( ctrl == CTRL_LED ) ? 0x00 : 0x12) + (column - 1) * 2;
    tmp_buffer[1] = (states & 0xFF00) >> 8;
    tmp_buffer[2] = (states & 0x00FF);

    hal_16x9_write(i2c_addr_, tmp_buffer, 3);
}

void click_16x9_point(uint8_t x, uint8_t y, uint8_t pwm)
{
    if(x > 8 || y > 15) return;

    tmp_buffer[0] = 0x24 + x * 16 + y;
    tmp_buffer[1] = pwm;

    hal_16x9_write(i2c_addr_, tmp_buffer, 2);
}

void click_16x9_rectangle(
    uint8_t x, 
    uint8_t y, 
    uint8_t width, 
    uint8_t height,
    uint8_t pwm
)
{
    uint8_t i;
    uint8_t w = x + (width > 9) ? (9 - x) : width;
    uint8_t h = y + (height > 16) ? (16 - y) : height;
    
    for (i = 0; i < w; i++)
    {
        tmp_buffer[0] = 0x24 + (x + i) * 16 + y;
        memset(tmp_buffer + 1, pwm, h);
        hal_16x9_write(i2c_addr_, tmp_buffer, h + 1);
    }
}

void click_16x9_fill_screen(uint8_t pwm)
{
    memset(tmp_buffer, pwm, 145);
    tmp_buffer[0] = 0x24;
    hal_16x9_write(i2c_addr_, tmp_buffer, 145);
}

void click_16x9_circle(uint8_t x, uint8_t y, uint8_t r, uint8_t pwm)
{
    int i;
    int r2 = r * r;
    int area = r2 << 2;
    int rr = r << 1;
    int tx;
    int ty;

    for (i = 0; i < area; i++)
    {
        tx = (i % rr) - r;
        ty = (i / rr) - r;

        if (tx * tx + ty * ty <= r2)
            click_16x9_point((uint8_t)(x + tx), (uint8_t)(y + ty), pwm);
    }
}

/*************** END OF FUNCTIONS *********************************************/