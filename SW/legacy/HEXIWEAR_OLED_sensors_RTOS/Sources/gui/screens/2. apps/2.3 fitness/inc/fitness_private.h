/**
 * fitness app private declarations
 * Project HEXIWEAR, 2015
 */

#ifndef HG_FITNESS_PRIVATE
#define HG_FITNESS_PRIVATE

#include "gui_driver.h"

#define FITNESS_QUEUE_SIZE (3)

extern const uint8_t
	test_bmp[ OLED_GRAM_SIZE+6 ];

extern const uint8_t
	fitness_screen_bmp[ OLED_GRAM_SIZE+6 ];

extern const uint8_t
	Exo_2_Light_Condensed13x20_Regular[];

extern guiLabel_t
  fitness_labelStepCounter;

extern guiLabel_t
  fitness_labelSteps;

void fitness_Init( void* param );
void fitness_CreateTasks( void* param );
void fitness_DestroyTasks( void* param );

void test_Init( void* param );

#endif
