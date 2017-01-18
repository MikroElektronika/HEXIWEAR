/*
 * LEDs_private.h
 *
 *  Created on: 08.11.2016
 *      Author: Patrick
 */

#ifndef CODE_GUI_SCREENS_7__LEDS_INC_LEDS_PRIVATE_H_
#define CODE_GUI_SCREENS_7__LEDS_INC_LEDS_PRIVATE_H_

#include "gui_driver.h"
#include <stdint.h>

extern const uint8_t
	control_bmp[18438];

#endif /* CODE_GUI_SCREENS_7__LEDS_INC_LEDS_PRIVATE_H_ */


#define CONTROL_STACK_SIZE ( 0x400 )
#define CONTROL_PRIO       ( HEXIWEAR_APP_PRIO )

//#define LED1 GPIO_MAKE_PIN(GPIOC_IDX, 6U)
