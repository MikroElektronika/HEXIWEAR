
#include "menu_driver.h"
#include "string.h"
#include "OLED_defs.h"
#include "OLED_driver.h"
#include "GPIO.h"

#include "error.h"

typedef struct
{
  const menuItem_t *menuItem;
  uint8_t 	 image[MENU_IMAGE_SIZE];

} menuScreen_t;

menuScreen_t
  menuDriver_screen;

static menuStatus_t MenuDriver_ChangeItem(const menuItem_t * ptrNewItem, void *param);

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

/**
 * initialize modules
 */
void MenuDriver_Init(void)
{
  uint8_t
    moduleStatus = OLED_Init( &oledModule, &oledSettings );

  if ( 0 != moduleStatus )
  {
    catch(11);
  }

  MenuDriver_LoadScreen(MENU_NAVIGATION_ROOT , NULL);
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *
 *
 */

menuStatus_t MenuDriver_LoadScreen(menuNavigationDir_t navigationDir, void *param) {
	const menuItem_t  *ptrNewItem;
	transition_t       transition;
	menuNavigation_t  *navigation;

	navigation = &menuDriver_screen.menuItem->navigation;

	switch(navigationDir) {
		case MENU_NAVIGATION_ROOT: {
			ptrNewItem = &menuItem_main;
			transition = OLED_TRANSITION_NONE;
			break;
		}

		case MENU_NAVIGATION_ENTER: {
			ptrNewItem = navigation->enter;
			transition = OLED_TRANSITION_NONE;
			break;
		}

		case MENU_NAVIGATION_BACK: {
			ptrNewItem = navigation->back;
			transition = OLED_TRANSITION_NONE;
			break;
		}

		case MENU_NAVIGATION_LEFT: {
			ptrNewItem = navigation->left;
			transition = OLED_TRANSITION_LEFT_RIGHT;
			break;
		}

		case MENU_NAVIGATION_RIGHT: {
			ptrNewItem = navigation->right;
			transition = OLED_TRANSITION_RIGHT_LEFT;
			break;
		}


		default : {
			return MENU_STATUS_ERROR;
		}
	}

	if(MenuDriver_ChangeItem(ptrNewItem, param) != MENU_STATUS_SUCCESS) {
		return MENU_STATUS_ERROR;
	}
	else {
		statusOLED_t statusOLED;

		statusOLED = OLED_DrawImage( menuDriver_screen.image, transition);
		if(statusOLED == STATUS_OLED_SUCCESS) {
			return  MENU_STATUS_SUCCESS;
		}
		else {
			return   MENU_STATUS_ERROR;
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *
 *
 */

static menuStatus_t MenuDriver_ChangeItem(const menuItem_t * ptrNewItem, void *initParam) {

	uint16_t      *ptrInt;
	const uint8_t *ptrChar;

	if(ptrNewItem != NULL) {											// Check if new item exist.
		menuDriver_screen.menuItem = ptrNewItem;						// Update current menu item.

		// Load image from flash, with swapping bytes in each pixel.
		ptrInt = (uint16_t *)menuDriver_screen.image;
		ptrChar = (const uint8_t *)ptrNewItem->image;
		for (int var = 0; var < MENU_IMAGE_SIZE/2; ++var) {
			*ptrInt = *ptrChar << 8;
			ptrChar++;
			*ptrInt |= *ptrChar;
			ptrChar++;
			ptrInt++;
		}

		if(ptrNewItem->initFunction != NULL) {							// Check if init function for current item is defined.
			ptrNewItem->initFunction(initParam);						// Call init function.
		}

		return MENU_STATUS_SUCCESS;
	}
	else {
		return MENU_STATUS_ERROR;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

