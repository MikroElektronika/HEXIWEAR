/**
 * menu-related data type structures
 * Project HEXIWEAR, 2015
 */

#ifndef HG_MENU_TYPES
#define HG_MENU_TYPES

#include <stdint.h>
#include "menu_info.h"

typedef struct MenuNavigation
{
        const struct MenuItem *enter;
        const struct MenuItem *back;
        const struct MenuItem *up;
        const struct MenuItem *down;
        const struct MenuItem *left;
        const struct MenuItem *right;

} menuNavigation_t;

typedef struct MenuItem
{
    menuNavigation_t    navigation;
    const uint8_t       *image;
        void            (*initFunction)(void *param);
        void            (*createTaskFunction)(void *param);
        void            (*destroyTaskFunction)(void *param);

} menuItem_t;

typedef struct
{
  const menuItem_t* menuItem;
            uint8_t image[MENU_IMAGE_SIZE];

} menuScreen_t;

typedef enum
{
  MENU_STATUS_SUCCESS,     // success
  MENU_STATUS_ERROR,       // fail

} menuStatus_t;

typedef enum
{
  MENU_NAVIGATION_ENTER,
  MENU_NAVIGATION_BACK,
  MENU_NAVIGATION_UP,
  MENU_NAVIGATION_DOWN,
  MENU_NAVIGATION_LEFT,
  MENU_NAVIGATION_RIGHT,
  MENU_NAVIGATION_WATCH

} menuNavigationDir_t;

/**
 * color chart
 */

typedef enum
{
  MENU_COLOR_BLACK    = 0x0000,
  MENU_COLOR_BLUE     = 0x001F,
  MENU_COLOR_RED      = 0xF800,
  MENU_COLOR_GREEN    = 0x07E0,
  MENU_COLOR_CYAN     = 0x07FF,
  MENU_COLOR_MAGENTA  = 0xF81F,
  MENU_COLOR_YELLOW   = 0xFFE0,
  MENU_COLOR_WHITE    = 0xFFFF

} menu_color_t;


#endif
