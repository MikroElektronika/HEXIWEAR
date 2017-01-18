#include "OLED_driver.h"

#define NULL ( (void*)0 )

uint8_t
    sampleText[] = "Sample Text";

oled_text_properties_t
    sampleTextProperties;

oled_dynamic_area_t
    sampleImageArea,
    sampleTextArea;

/** choose the test */
// #define TEST_SCREEN
// #define TEST_TEXT
#define TEST_IMAGE

#if defined (TEST_IMAGE)
#include "test_resources.h"
#endif

void main() org 0x1000
{
    OLED_Init();

#if defined (TEST_SCREEN)
    while (1)
    {
        OLED_FillScreen(0xFFFF);
        Delay_ms(500);
        OLED_FillScreen(0x0780);
        Delay_ms(500);
    }
#endif

#if defined (TEST_TEXT)
    sampleTextProperties.font       = guiFont_Tahoma_8_Regular;
    sampleTextProperties.fontColor  = OLED_COLOR_CYAN;
    sampleTextProperties.alignParam = OLED_TEXT_ALIGN_CENTER;
    sampleTextProperties.background = NULL;
    
    OLED_SetTextProperties( &sampleTextProperties );
    
    sampleTextArea.xCrd   = 5;
    sampleTextArea.yCrd   = 5;
    sampleTextArea.width  = 80;
    sampleTextArea.height = 80;
    
    sampleTextArea.areaBuffer = NULL;
    
    OLED_SetDynamicArea( &sampleTextArea );

    OLED_DrawText( sampleText );
#endif

#if defined (TEST_IMAGE)
    OLED_GetImageDimensions( &sampleImageArea.width, &sampleImageArea.height, bond_screen_bmp );
    OLED_SetDynamicArea( &sampleImageArea );

    OLED_DrawImage( bond_screen_bmp );
#endif
}