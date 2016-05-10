
#ifndef _MENU_DEFS
#define _MENU_DEFS

#include <stdint.h>
#include <stddef.h>

#define MENU_IMAGE_SIZE			(96*96*2)

typedef struct MenuNavigation
{
	const struct MenuItem *enter;
	const struct MenuItem *back;
	const struct MenuItem *up;
	const struct MenuItem *down;
	const struct MenuItem *left;
	const struct MenuItem *right;

}
menuNavigation_t;

typedef struct MenuItem
{
    menuNavigation_t	navigation;
    const uint8_t  		*image;
	void    			(*initFunction)(void *param);
	void    			(*callbackFunction)(void *param);
}
menuItem_t;

typedef enum
{
	MENU_STATUS_SUCCESS,     // success
	MENU_STATUS_ERROR,       // fail
}
menuStatus_t;

typedef enum
{
  MENU_NAVIGATION_ENTER,
  MENU_NAVIGATION_BACK,
  MENU_NAVIGATION_UP,
  MENU_NAVIGATION_DOWN,
  MENU_NAVIGATION_LEFT,
  MENU_NAVIGATION_RIGHT,
  MENU_NAVIGATION_ROOT
}
menuNavigationDir_t;

#endif
