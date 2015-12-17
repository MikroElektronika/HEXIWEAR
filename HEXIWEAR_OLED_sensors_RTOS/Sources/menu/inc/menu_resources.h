
#ifndef _MENU_RESOURCES
#define _MENU_RESOURCES

#include "menu_info.h"
#include "menu_types.h"

#define BMP_HEADER_BYTE_SIZE (6)
#define MenuDriver_SkipHeader( imgPtr ) ( (const uint8_t*)(imgPtr) + BMP_HEADER_BYTE_SIZE )

extern const uint8_t menuScreen_clock_bmp   [ MENU_IMAGE_SIZE + 6 ];
extern const uint8_t menuScreen_welcome_bmp [ MENU_IMAGE_SIZE + 6 ];
extern const uint8_t menuScreen_fitness_bmp [ MENU_IMAGE_SIZE + 6 ];
extern const uint8_t menuScreen_sensors_bmp [ MENU_IMAGE_SIZE + 6 ];
extern const uint8_t menuScreen_settings_bmp[ MENU_IMAGE_SIZE + 6 ];

extern const uint8_t menuFont_Tahoma11x13_Regular[];
extern const uint8_t menuFont_Tahoma21x25_Regular[];
extern const uint8_t menuFont_Roboto_Mono11x23_Regular[];

#endif
