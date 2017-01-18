#line 1 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_Thunder_Click/example/ARM/Thunder.c"
#line 1 "d:/uros/!!konacni primeri/hexiwear_thunder_click/example/arm/common/inc/common_screen_objects.h"
#line 1 "d:/uros/!!konacni primeri/hexiwear_thunder_click/example/arm/oled/inc/oled_driver.h"
#line 1 "d:/uros/!!konacni primeri/hexiwear_thunder_click/example/arm/oled/inc/oled_types.h"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 13 "d:/uros/!!konacni primeri/hexiwear_thunder_click/example/arm/oled/inc/oled_types.h"
typedef enum
{
 OLED_TRANSITION_NONE,
 OLED_TRANSITION_TOP_DOWN,
 OLED_TRANSITION_DOWN_TOP,
 OLED_TRANSITION_LEFT_RIGHT,
 OLED_TRANSITION_RIGHT_LEFT

} oled_transition_t;

typedef enum
{
 OLED_STATUS_SUCCESS,
 OLED_STATUS_ERROR,
 OLED_STATUS_PROTOCOL_ERROR,
 OLED_STATUS_INIT_ERROR,
 OLED_STATUS_DEINIT_ERROR

} oled_status_t;
#line 41 "d:/uros/!!konacni primeri/hexiwear_thunder_click/example/arm/oled/inc/oled_types.h"
typedef uint16_t* oled_pixel_t;

typedef struct
{
 uint32_t DCpin;
 uint32_t CSpin;
 uint32_t RSTpin;

 uint32_t ENpin;

} settingsOLED_t;

typedef enum
{
 OLED_TEXT_ALIGN_NONE = 0,

 OLED_TEXT_ALIGN_LEFT = 0x1,
 OLED_TEXT_ALIGN_RIGHT = 0x2,
 OLED_TEXT_ALIGN_CENTER = 0x3,

 OLED_TEXT_VALIGN_TOP = 0x10,
 OLED_TEXT_VALIGN_BOTTOM = 0x20,
 OLED_TEXT_VALIGN_CENTER = 0x30

} oled_text_align_t;

typedef enum
{
 OLED_COLOR_BLACK = 0x0000,
 OLED_COLOR_BLUE_1 = 0x06FF,
 OLED_COLOR_BLUE = 0x001F,
 OLED_COLOR_RED = 0xF800,
 OLED_COLOR_GREEN = 0x07E0,
 OLED_COLOR_CYAN = 0x07FF,
 OLED_COLOR_MAGENTA = 0xF81F,
 OLED_COLOR_YELLOW = 0xFFE0,
 OLED_COLOR_GRAY = 0x528A,
 OLED_COLOR_WHITE = 0xFFFF

} oled_color_t;

typedef struct
{
 uint8_t xCrd;
 uint8_t yCrd;
 uint8_t width;
 uint8_t height;
 oled_pixel_t areaBuffer;

} oled_dynamic_area_t;

typedef struct
{
 const uint8_t* font;
 uint16_t fontColor;
 oled_text_align_t alignParam;
 const uint8_t* background;

} oled_text_properties_t;
#line 1 "d:/uros/!!konacni primeri/hexiwear_thunder_click/example/arm/oled/inc/oled_resources.h"
#line 1 "d:/program files/nxp/mikroc pro for arm/include/stdint.h"
#line 6 "d:/uros/!!konacni primeri/hexiwear_thunder_click/example/arm/oled/inc/oled_resources.h"
extern const uint8_t guiFont_Tahoma_18_Regular[];
extern const uint8_t guiFont_Tahoma_16_Regular[];
extern const uint8_t guiFont_Tahoma_14_Regular[];
extern const uint8_t guiFont_Tahoma_10_Regular[];
extern const uint8_t guiFont_Tahoma_8_Regular[];
extern const uint8_t guiFont_Tahoma_7_Regular[];
extern const uint8_t guiFont_Tahoma_6_Regular[];
extern const uint8_t guiFont_Roboto_Mono11x23_Regular[];
extern const uint8_t guiFont_Exo_2_Condensed10x16_Regular[];
extern const uint8_t guiFont_Exo_2_Condensed15x23_Regular[];
extern const uint8_t guiFont_Exo_2_Condensed21x32_Regular[];

extern const uint8_t hexiwearLogo_bmp[18438];
#line 22 "d:/uros/!!konacni primeri/hexiwear_thunder_click/example/arm/oled/inc/oled_driver.h"
oled_status_t OLED_Init(void);
#line 37 "d:/uros/!!konacni primeri/hexiwear_thunder_click/example/arm/oled/inc/oled_driver.h"
oled_status_t OLED_DrawBox (
 uint16_t xCrd,
 uint16_t yCrd,
 uint16_t width,
 uint16_t height,
 uint16_t color
 );
#line 54 "d:/uros/!!konacni primeri/hexiwear_thunder_click/example/arm/oled/inc/oled_driver.h"
oled_status_t OLED_FillScreen( uint16_t color );
#line 68 "d:/uros/!!konacni primeri/hexiwear_thunder_click/example/arm/oled/inc/oled_driver.h"
oled_status_t OLED_DrawPixel (
 int16_t xCrd,
 int16_t yCrd,
 uint16_t color
 );





oled_status_t OLED_AddText( const uint8_t* text );





void OLED_SetTextProperties(oled_text_properties_t *textProperties);





uint8_t OLED_GetTextWidth(const uint8_t* text);





uint8_t OLED_CharCount(uint8_t width, const uint8_t* font, const uint8_t* text, uint8_t length);





void OLED_SetFont(const uint8_t *activeFont, uint16_t font_color, uint8_t font_orientation);





void OLED_SetDynamicArea(oled_dynamic_area_t *dynamic_area);





void OLED_WriteText(uint8_t *text, uint16_t x, uint16_t y);





oled_status_t OLED_DrawImage (const uint8_t* image, uint8_t xCrd, uint8_t yCrd);
oled_status_t OLED_DrawImage_Ram (uint8_t* image, uint8_t xCrd, uint8_t yCrd);





void OLED_GetImageDimensions(uint8_t *width, uint8_t *height, const uint8_t* image);
#line 8 "d:/uros/!!konacni primeri/hexiwear_thunder_click/example/arm/common/inc/common_screen_objects.h"
extern const uint8_t
 common_hexiwearLogo_bmp[18438];
extern const uint8_t
 thunder_bmp[18438];
extern const
 thundera_bmp[18438];
#line 76 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_Thunder_Click/example/ARM/Thunder.c"
unsigned int distance;
int value;
int value1;
char Out_Text[15];
char cSF_test_status;
char interrupt_source = 0;

sbit Thunder_Sens_PIN at PTB_PDIR.B13;
sbit Thunder_CS at PTC_PDOR.B4;
static uint8_t isThunderDetected = -1;
#line 91 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_Thunder_Click/example/ARM/Thunder.c"
void Thunder_Write();
unsigned short Thunder_Read();
void Thunder_Init(void);
long int Thunder_Read_Energy();
unsigned int Thunder_Read_distance();
#line 105 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_Thunder_Click/example/ARM/Thunder.c"
void Thunder_Write(unsigned short address, unsigned short data1)
{

 address.B7 = 0;
 address.B6 = 0;
 Thunder_CS = 0;
 SPI_Wr_Ptr(address);
 SPI_Wr_Ptr(data1);
 Thunder_CS = 1;
}

unsigned short Thunder_Read(unsigned short address)
{
 unsigned short tmp = 0;

 address.B7 = 0;
 address.B6 = 1;
 Thunder_CS = 0;
 SPI_Wr_Ptr(address);
 tmp = SPI_Rd_Ptr(0);
 Thunder_CS = 1;

 return tmp;
}


void Thunder_Init(void)
{
unsigned short temp;
 SPI_Set_Active(SPI0_Read, SPI0_Write);
 Thunder_CS = 1;

 Thunder_Write(0x3C, 0x96);
 Thunder_Write(0x3D, 0x96);

 temp = Thunder_Read(0x00) & 0xC1;
 Thunder_Write(0x00, (( 0x12  << 1) | temp));

 temp = Thunder_Read(0x01) & 0x80;
 Thunder_Write(0x01, 0x44 | temp);

 temp = Thunder_Read(0x02) & 0x80;
 Thunder_Write(0x02, 0x40 | temp);

 temp = Thunder_Read(0x03) & 0x1F;
 Thunder_Write(0x03, 0x00 | temp);

 Thunder_Write(0x08, 0x00);
}

long int Thunder_Read_Energy()
{
 unsigned short low_byte, mid_byte;
 long int Out_thunder_energy;

 Out_thunder_energy = Thunder_Read(0x06) & 0x1F;
 mid_byte = Thunder_Read(0x05);
 low_byte = Thunder_Read(0x04);

 Out_thunder_energy = (Out_thunder_energy << 8);
 Out_thunder_energy = (Out_thunder_energy | mid_byte);
 Out_thunder_energy = (Out_thunder_energy << 8);
 Out_thunder_energy = (Out_thunder_energy | low_byte);

 return Out_thunder_energy;
}


unsigned int Thunder_Read_distance()
{
 int Out_thunder_distance;

 Out_thunder_distance = Thunder_Read(0x07) & 0x3F;

 return Out_thunder_distance;
}

void system_init()
{
GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
GPIO_Digital_Input(&PTB_PDOR, _GPIO_PINMASK_13);
SPI0_Init_Advanced(1000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 | _SPI_CFG_FRAME_SIZE_8BITS |
 _SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);

}

void display_init()
{
SPI_Set_Active(SPI2_Read, SPI2_Write);

OLED_Init();
OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );

OLED_DrawImage( thunder_bmp, 0, 0 );
}


void main() org 0x1000
{
system_init();

display_init();

Thunder_Init();


EnableInterrupts();
NVIC_IntEnable( IVT_INT_PORTB );
PORTB_PCR13bits.IRQC = 0xB;

 while (1)
 {
 if ( 1 == isThunderDetected )
 {
 NVIC_IntDisable( IVT_INT_PORTB );
 SPI_Set_Active(SPI0_Read, SPI0_Write);

 interrupt_source = Thunder_Read(0x03) & 0x0F;
 distance = Thunder_Read_distance();
 value = Thunder_Read_Energy();

 switch (interrupt_source){
 case 4:
 {
 IntToStr((distance*2), Out_Text);

 SPI_Set_Active(SPI2_Read, SPI2_Write);
 OLED_DrawImage( thundera_bmp, 0, 0 );
 OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
 OLED_WriteText(Out_Text, 41, 82 );
 OLED_WriteText("Distance:", 10, 82 );
 OLED_WriteText("Thundering", 17, 71 );
 OLED_WriteText("km", 70, 82 );

 delay_ms(3000);
 OLED_DrawImage( thunder_bmp, 0, 0 );
 break;
 }
 case 2:
 {
 SPI_Set_Active(SPI2_Read, SPI2_Write);
 OLED_DrawImage( thundera_bmp, 0, 0 );
 OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
 OLED_WriteText("Disturbance", 20, 75 );

 delay_ms(2000);
 OLED_DrawImage( thunder_bmp, 0, 0 );
 break;
 }
 }
 isThunderDetected = 0;
 NVIC_IntEnable( IVT_INT_PORTB );
 }
 }
}
#line 265 "D:/Uros/!!KONACNI PRIMERI/HEXIWEAR_Thunder_Click/example/ARM/Thunder.c"
void External1Int() iv IVT_INT_PORTB ics ICS_AUTO
{
 PORTB_ISFR = 0xFFFFFFFF;
 isThunderDetected = 1;
}
