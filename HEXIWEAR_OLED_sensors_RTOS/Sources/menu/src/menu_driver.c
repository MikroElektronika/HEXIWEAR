
#include "HEXIWEAR_info.h"

#include "sensor_defs.h"

#include "menu_driver.h"
#include "menu_types.h"

#include "menu_info.h"
#include "menu_resources.h"
#include "menu_types.h"

#include "string.h"

#include "OLED_info.h"
#include "OLED_defs.h"
#include "OLED_driver.h"

#include "sensor_driver.h"

#include "GPIO.h"

#include "error.h"
#include "error_types.h"
#include "CLOCK.h"
#include <stdio.h>

#include "apps.h"

//OSA_TASK_DEFINE( MenuDriver_App_Clock, HEXIWEAR_MENU_TASK_APP_RTC_STACK_SIZE );

/**
 * task handlers
 */

//task_handler_t
//  hexiwear_app_WATCH_handler,
//  hexiwear_app_SENSORS_handler,
//  hexiwear_app_FITNESS_handler;

MSG_QUEUE_DECLARE( MenuDriver_queue, QUEUE_MENU_LENGTH, sizeof(hostInterface_packet_t) );

/**
 *    This function puts a message to the end of the Tx message queue.
 *
 *    @param    packet   Packet that will be placed into Tx message queue.
 *
 *    @return                          kStatus_OSA_Success  Message successfully put into the queue.
 *                                     kStatus_OSA_Error    Process fail.
 */
menuStatus_t MenuDriver_QueueMsgPut (
                                      hostInterface_packet_t* packet
                                    )
{
  osa_status_t
    status = kStatus_OSA_Success;

  while (1)
  {
    status = OSA_MsgQPut( MenuDriver_queueHnd, (hostInterface_packet_t*)packet );

    if ( kStatus_OSA_Success == status )
    {
      return MENU_STATUS_SUCCESS;
    }

    else
    {
      catch( CATCH_QUEUE );
      return MENU_STATUS_ERROR;
    }
  }
}

/**
 *    This function gets a message from the head of the Tx message queue.
 *
 *    @param    packet   Pointer to a memory to save the packet.
 *
 *    @return                          kStatus_OSA_Success  Message successfully obtained from the queue.
 *                                     kStatus_OSA_Error    Process fail.
 */
menuStatus_t MenuDriver_QueueMsgGet(
                                     hostInterface_packet_t* packet,
									 uint32_t timeout
                                   )
{
  osa_status_t
    status = OSA_MsgQGet( MenuDriver_queueHnd, (hostInterface_packet_t*)packet, timeout);

  if ( kStatus_OSA_Error == status )
  {
    catch( CATCH_QUEUE );
    return MENU_STATUS_ERROR;
  }
  else
  {
    return MENU_STATUS_SUCCESS;
  }
}

/**
 * initialize menu
 */

menuStatus_t MenuDriver_Init()
{

  // Create Tx Message Queue
  MenuDriver_queueHnd = OSA_MsgQCreate(
                                        MenuDriver_queue,
                                        gHostInterface_msgNum,
                                        sizeof(hostInterface_packet_t) / sizeof(uint32_t)
                                      );

  if ( NULL == MenuDriver_queueHnd )
  {
    catch( CATCH_QUEUE );
    return MENU_STATUS_ERROR;
  }

#if defined( HEXIWEAR_DEBUG )
  vQueueAddToRegistry( MenuDriver_queueHnd, (const char*)"MenuQueue" );
#endif

  oled_status_t
    oledStatus = OLED_Init( &oledModule, &oledSettings );

  if ( OLED_STATUS_SUCCESS != oledStatus )
  {
    catch( CATCH_OLED );
    return MENU_STATUS_ERROR;
  }

  oled_dynamic_area_t dynamic_area =
  {
      .xCrd = 0,
      .yCrd = 0,
      .width = 96,
      .height = 96,
  };

  OLED_SetDynamicArea(&dynamic_area);
  OLED_DrawImage(menuScreen_welcome_bmp);
  OSA_TimeDelay( 500 );

  uint8_t
    width,
    height;

  OLED_GetImageDimensions( &width, &height, battery_3_bmp );

//  while (1)
//  {
//    OLED_DrawScreen( MenuDriver_SkipHeader( battery_3_bmp ), 20, 20, width, height, OLED_TRANSITION_NONE );
//    OSA_TimeDelay( 500 );
//    OLED_DrawScreen( MenuDriver_SkipHeader( battery_3_bmp ), 20, 20, width, height, OLED_TRANSITION_TOP_DOWN );
//    OSA_TimeDelay( 500 );
//    OLED_DrawScreen( MenuDriver_SkipHeader( battery_3_bmp ), 20, 20, width, height, OLED_TRANSITION_DOWN_TOP );
//    OSA_TimeDelay( 500 );
//    OLED_DrawScreen( MenuDriver_SkipHeader( battery_3_bmp ), 20, 20, width, height, OLED_TRANSITION_RIGHT_LEFT );
//    OSA_TimeDelay( 500 );
//    OLED_DrawScreen( MenuDriver_SkipHeader( battery_3_bmp ), 20, 20, width, height, OLED_TRANSITION_LEFT_RIGHT );
//    OSA_TimeDelay( 500 );
//  }

  MenuDriver_LoadScreen( MENU_NAVIGATION_WATCH, NULL );

  return MENU_STATUS_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 *
 *
 */

menuStatus_t MenuDriver_LoadScreen(menuNavigationDir_t navigationDir, void *param)
{
  const menuItem_t*
    ptrNewItem;
  oled_transition_t
    transition;

  const menuNavigation_t*
    navigation = &menuDriver_screen.menuItem->navigation;

  switch(navigationDir) {
          case MENU_NAVIGATION_WATCH: {
                  ptrNewItem = &watch_item;
                  transition = OLED_TRANSITION_RIGHT_LEFT;
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

          case MENU_NAVIGATION_UP: {
                  ptrNewItem = navigation->up;
                  transition = OLED_TRANSITION_DOWN_TOP;
                  break;
          }

          case MENU_NAVIGATION_DOWN: {
                  ptrNewItem = navigation->down;
                  transition = OLED_TRANSITION_TOP_DOWN;
                  break;
          }

          default : {
                  return MENU_STATUS_ERROR;
          }
  }

  // finishing action for the current screen
  if ( NULL != menuDriver_screen.menuItem->destroyFunction )
  {
    menuDriver_screen.menuItem->destroyFunction( param );
  }

  // Update current menu item
  menuDriver_screen.menuItem = ptrNewItem;
  OLED_Swap( (oled_pixel_t)menuDriver_screen.image, MenuDriver_SkipHeader(ptrNewItem->image), OLED_SCREEN_SIZE );

  // starting action for the new screen
  if( NULL != ptrNewItem->initFunction )
  {
    ptrNewItem->initFunction( param );
  }

  uint8_t
    xCrd = 0,
    yCrd = 0,
    width,
    height;

  OLED_GetImageDimensions( &width, &height, (const uint8_t*)menuDriver_screen.menuItem->image );

  oled_status_t
    statusOLED = OLED_DrawScreen( menuDriver_screen.image, xCrd, yCrd, width, height, transition );

  if( OLED_STATUS_SUCCESS == statusOLED )
  {
    // post-load action for the new screen
    if( NULL != ptrNewItem->callbackFunction )
    {
      ptrNewItem->callbackFunction( param );
    }
    return  MENU_STATUS_SUCCESS;
  }

  else
  {
    return   MENU_STATUS_ERROR;
  }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/**
 * update the main screen buffer
 * with the given image
 */
void MenuDriver_UpdateScreen (
                                uint8_t xCrd,
                                uint8_t yCrd,

                                uint8_t width,
                                uint8_t height,

                                const uint8_t* image
                              )
{
  // copy data
  oled_pixel_t
    copyAddr = (oled_pixel_t)menuDriver_screen.image + ( yCrd*OLED_SCREEN_WIDTH + xCrd );

  for ( uint8_t i = 0; i < height; i++ )
  {
    memcpy( (void*)copyAddr, (void*)image, width*OLED_BYTES_PER_PIXEL );
    copyAddr += OLED_SCREEN_WIDTH;
    image    += width*OLED_BYTES_PER_PIXEL;
  }
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

