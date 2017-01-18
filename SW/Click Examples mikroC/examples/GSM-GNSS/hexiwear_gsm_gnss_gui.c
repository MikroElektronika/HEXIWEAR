/**
 * @file hexiwear_gsm_gnss_gui.c
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
 * @date        29 Nov 2016
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



/******************************************************************************
* Includes
*******************************************************************************/
#include "hexiwear_gsm_gnss_gui.h"
#include "resources.h"

/******************************************************************************
* Preprocessors
*******************************************************************************/
#define LEFT_ARROW_POSITION_X 2 
#define ARROW_POSITION_Y 20
#define RIGHT_ARROW_POSITION_X 94


/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Constants Definitions
*******************************************************************************/
static const char** old_text = NULL;

static const uint16_t line_spacing = 15;

static const uint16_t x_offset = 112;
static const uint16_t y_offset = 72;

/******************************************************************************
* Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Private Functions
*******************************************************************************/

/******************************************************************************
* Public Functions
***
****************************************************************************/
/***************************************************************************//**
 *
 */
void hexiwear_gsm_gnss_gui_init( void )
{
    hexiwear_gsm_gnss_gui_clear_page();

    OLED_SetFont(guiFont_Tahoma_10_Regular, OLED_COLOR_WHITE, 0);
    OLED_WriteText("SIM", 35,36);
    OLED_WriteText("not ready", 20,  50);
}

/***************************************************************************//**
 *
 */
void hexiwear_gsm_gnss_gui_clear_page( void )
{
    OLED_FillScreen( OLED_COLOR_BLACK );
}

/***************************************************************************//**
 *
 */
void hexiwear_gsm_gnss_gui_write_msg( char** text )
{
    uint8_t row = 0;
    uint16_t spacing = 0;

    if( old_text != NULL  && old_text != text )
    {
        OLED_SetFont(guiFont_Tahoma_10_Regular, OLED_COLOR_BLACK, 0);
        while( strcmp( old_text[row], "\r" ) != 0 )
        {
            OLED_WriteText(old_text[row++], 13, 10 + spacing);
            spacing = spacing + line_spacing;
        }
    }

    row = 0;
    spacing = 0;

    OLED_SetFont(guiFont_Tahoma_10_Regular, OLED_COLOR_WHITE, 0);
    while( strcmp( text[row], "\r" ) != 0 )
    {
        OLED_WriteText(text[row++], 13, 10 + spacing);
        spacing = spacing + line_spacing;
    }

    old_text = text;
}

/***************************************************************************//**
 *
 */
void hexiwear_gsm_gnss_gui_draw_arrows( void )
{
    OLED_DrawBox (91, 20, 1, 1, OLED_COLOR_WHITE);
    OLED_DrawBox (91 - 1, 20 + 1, 3, 1, OLED_COLOR_WHITE);
    OLED_DrawBox (91 - 2, 20 + 2, 5, 1, OLED_COLOR_WHITE);

    OLED_DrawBox (91, 79, 1, 1, OLED_COLOR_WHITE);
    OLED_DrawBox (91 - 1, 79 - 1, 3, 1, OLED_COLOR_WHITE);
    OLED_DrawBox (91 - 2, 79 - 2, 5, 1, OLED_COLOR_WHITE);
}

/***************************************************************************//**
 *
 */
void hexiwear_gsm_gnss_gui_draw_button( void )
{
    OLED_DrawBox (5, 94, 35, 2, OLED_COLOR_WHITE);

    OLED_SetFont(guiFont_Tahoma_10_Regular, OLED_COLOR_WHITE, 0);
    OLED_WriteText("SEND", 8, 78);
}

/***************************************************************************//**
 *
 */
void hexiwear_gsm_gnss_gui_draw_sending_page( void )
{
    hexiwear_gsm_gnss_gui_clear_page();

    OLED_SetFont(guiFont_Tahoma_10_Regular, OLED_COLOR_WHITE, 0);
    OLED_WriteText("Sending...", 25, 15);

    OLED_DrawImage (sms_bmp, 23, 35);
}

/***************************************************************************//**
 *
 */
void hexiwear_gsm_gnss_gui_draw_waiting_bar( uint8_t index )
{
    OLED_DrawBox (39, 81, 18, 12, OLED_COLOR_BLACK);

    OLED_DrawBox (39, ((index % 3) == 0) ? 81 : 83, 3, ((index % 3) == 0) ? 12 : 8, OLED_COLOR_WHITE);
    OLED_DrawBox (46, ((index % 3) == 1) ? 81 : 83, 3, ((index % 3) == 1) ? 12 : 8, OLED_COLOR_WHITE);
    OLED_DrawBox (53, ((index % 3) == 2) ? 81 : 83, 3, ((index % 3) == 2) ? 12 : 8, OLED_COLOR_WHITE);
}

/***************************************************************************//**
 *
 */
void hexiwear_gsm_gnss_gui_draw_msg_select_page( char** msg )
{
    hexiwear_gsm_gnss_gui_clear_page();
    hexiwear_gsm_gnss_gui_draw_arrows();
    hexiwear_gsm_gnss_gui_draw_button();
    hexiwear_gsm_gnss_gui_write_msg( msg );
}
/*************** END OF FUNCTIONS *********************************************/