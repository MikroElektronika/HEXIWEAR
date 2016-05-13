#ifndef HG_BOND_PRIVATE
#define HG_BOND_PRIVATE

#include "gui_driver.h"

// Resources
extern const uint8_t bond_screen_bmp[ OLED_GRAM_SIZE+6 ];

// Objects
extern guiLabel_t bond_label;

// Callbacks
void bond_Init( void *param );
void bond_DestroyTasks( void *param );

#endif
