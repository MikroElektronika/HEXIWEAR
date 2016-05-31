/**
 * \file gui_driver.c
 * \version 1.00
 * \brief this file contains GUI functionality
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
 * Project HEXIWEAR, 2015
 */

#include "HEXIWEAR_info.h"

#include "notifications.h"
#include "bond.h"

#include "sensor_defs.h"

#include "power_driver.h"

#include "gui_driver.h"
#include "gui_types.h"
#include "gui_info.h"
#include "gui_types.h"
#include "screens_common.h"

#include "string.h"

#include "OLED_info.h"
#include "OLED_defs.h"
#include "OLED_driver.h"

#include "GPIO.h"

#include "rtc_driver.h"

#include "power_driver.h"

#include "error.h"
#include "error_types.h"
#include "CLOCK.h"
#include <stdio.h>

static guiNavigationDir_t
    guiScreenRegNav = 0;

static mutex_t
  buttonHandlerAccess;

MSG_QUEUE_DECLARE( GuiDriver_queue, QUEUE_GUI_LENGTH, sizeof(hostInterface_packet_t) );

/*! Private prototypes */
static void GuiDriver_AddButtonPointers(guiNavigation_t *navigation);

/**
 *    This function puts a message to the end of the Tx message queue.
 *
 *    @param    packet   Packet that will be placed into Tx message queue.
 *
 *    @return                          kStatus_OSA_Success  Message successfully put into the queue.
 *                                     kStatus_OSA_Error    Process fail.
 */
gui_status_t GuiDriver_QueueMsgPut ( hostInterface_packet_t* packet )
{

  BaseType_t
    status = xQueueSendToBack( GuiDriver_queueHnd, (hostInterface_packet_t*)packet, OSA_WAIT_FOREVER );

    if ( pdPASS == status )
    {
      return GUI_STATUS_SUCCESS;
    }

    else
    {
      catch( CATCH_QUEUE );
      return GUI_STATUS_ERROR;
    }
}

/**
 *    This function gets a message from the head of the designated queue
 *
 *    @param    packet   Pointer to a memory to save the packet.
 *
 *    @return                          kStatus_OSA_Success  Message successfully obtained from the queue.
 *                                     kStatus_OSA_Error    Process fail.
 */
gui_status_t GuiDriver_QueueMsgGet(
                                     hostInterface_packet_t* packet,
                                                    uint32_t timeout
                                   )
{
  osa_status_t
    status = OSA_MsgQGet( GuiDriver_queueHnd, (hostInterface_packet_t*)packet, timeout);

  if ( kStatus_OSA_Error == status )
  {
    catch( CATCH_QUEUE );
    return GUI_STATUS_ERROR;
  }
  else
  {
    return GUI_STATUS_SUCCESS;
  }
}

/**
 * initialize GUI
 */

gui_status_t GuiDriver_Init()
{

  // create mutex for the access to handling the buttons
  OSA_MutexCreate( &buttonHandlerAccess );

  // create the queue
  GuiDriver_queueHnd = OSA_MsgQCreate(
                                        GuiDriver_queue,
                                        gHostInterface_msgNum,
                                        sizeof(hostInterface_packet_t) / sizeof(uint32_t)
                                      );

  if ( NULL == GuiDriver_queueHnd )
  {
    catch( CATCH_QUEUE );
    return GUI_STATUS_ERROR;
  }

#if defined( HEXIWEAR_DEBUG )
  vQueueAddToRegistry( GuiDriver_queueHnd, (const char*)"GUI common Queue" );
#endif

  oled_status_t
    oledStatus = OLED_Init( &oledModule, &oledSettings );

  if ( OLED_STATUS_SUCCESS != oledStatus )
  {
    catch( CATCH_OLED );
    return GUI_STATUS_ERROR;
  }
  GuiDriver_Navigation( GUI_NAVIGATION_SPLASH, NULL );
  OSA_TimeDelay(750);

  // Read link state
  watch_CreateLinkStateUpdateEvent();
  do
  {
    watch_SendGetLinkStateReq();
  }
  while( watch_WaitForLinkStateUpdate(100) != kStatus_OSA_Success );

  // Read active button group
  buttonsGroup_CreateActiveUpdateEvent();
  do
  {
    buttonsGroup_SendGetActiveReq();
  }
  while( buttonsGroup_WaitForActiveUpdate(100) != kStatus_OSA_Success );

  // Read advertise mode
  bluetooth_CreateAdvModeUpdateEvent();
  do
  {
	  bluetooth_SendGetAdvModeReq();
  }
  while( bluetooth_WaitForAdvModeUpdate(100) != kStatus_OSA_Success );

  // exchange version numbers with KW40
  HEXIWEAR_CreateVersionEvent();
  do
  {
	  HEXIWEAR_SendVersionReq();
  }
  while( HEXIWEAR_WaitForVersionUpdate(100) != kStatus_OSA_Success );

  GuiDriver_Navigation( GUI_NAVIGATION_WATCH, NULL );

  return GUI_STATUS_SUCCESS;
}

/**
 * [GuiDriver_NavigationHandler description]
 * @param packet [description]
 */

gui_status_t GuiDriver_ButtonsHandler(hostInterface_packet_t* packet)
{
    gui_status_t
        status = GUI_STATUS_SUCCESS;


    	guiNavigationDir_t navigationDir;

    	switch(packet->type)
    	{
    		case packetType_pressUp :
    		{
    			navigationDir = GUI_NAVIGATION_UP;
    			break;
    		}

    		case packetType_pressDown :
    		{
    			navigationDir = GUI_NAVIGATION_DOWN;
    			break;
    		}

    		case packetType_pressLeft :
    		{
    			navigationDir = GUI_NAVIGATION_LEFT;
    			break;
    		}

    		case packetType_pressRight :
    		{
    			navigationDir = GUI_NAVIGATION_RIGHT;
    			break;
    		}

    		default :
    		{
    			return GUI_STATUS_ERROR;
    		}
    	}



    	if (guiScreenRegNav & navigationDir)
    	{
//    		if ( haptic_CurrentStateGet() == hapticState_enable )
//			{
//				haptic_MutexLock(OSA_WAIT_FOREVER);
//				VIBRO_HAPTIC();
//				OSA_TimeDelay(200);
//				haptic_MutexUnlock();
//			}

    		status = GuiDriver_QueueMsgPut(packet);
    	}
    	else
    	{
			status = GuiDriver_Navigation(navigationDir, NULL);
        }

//        if ( GUI_STATUS_SUCCESS == status )
//        {
//        	RTC_UpdateAlarm();
//    	}

	return status;
}

/**
 * [GuiDriver_NavigationDefault description]
 * @param navigationDir [description]
 * @param param [description]
 */

gui_status_t GuiDriver_Navigation(guiNavigationDir_t navigationDir, void *param)
{
	const guiScreen_t* ptrNewScreen;
	oled_transition_t transition;
	void *destroyParam = NULL;
	void *initParam = NULL;
	void *createParam = NULL;

	const guiNavigation_t* navigation = &guiDriver_display.guiItem->navigation;

	switch(navigationDir)
	{
		/**
		 * splash screen
		 */
		case GUI_NAVIGATION_SPLASH:
		{
			ptrNewScreen = &splashScreen;
			transition = OLED_TRANSITION_NONE;
			break;
		}

		/**
		 * goto watch directly
		 */

		 case GUI_NAVIGATION_WATCH:
		 {
			 ptrNewScreen = &watchScreen;
			 transition = OLED_TRANSITION_NONE;
			 break;
		 }

		  case GUI_NAVIGATION_BOND: {
			  uint32_t passkey;
			  memcpy((uint8_t *)&passkey, (uint8_t *)param, 4);
			  bond_SetPasskey(passkey);
			  ptrNewScreen = &bondScreen;
			  initParam    = guiDriver_display.guiItem;
			  transition = OLED_TRANSITION_RIGHT_LEFT;
			  break;
		  }

      /**
       * regular navigation cases
       */

		  case GUI_NAVIGATION_LEFT: {
				  ptrNewScreen = navigation->left;
				  transition = OLED_TRANSITION_LEFT_RIGHT;
				  break;
		  }

		  case GUI_NAVIGATION_RIGHT: {
				  ptrNewScreen = navigation->right;
				  transition = OLED_TRANSITION_RIGHT_LEFT;
				  break;
		  }

		  case GUI_NAVIGATION_UP: {
				  ptrNewScreen = navigation->up;
				  transition = OLED_TRANSITION_DOWN_TOP;
				  break;
		  }

		  case GUI_NAVIGATION_DOWN: {
				  ptrNewScreen = navigation->down;
				  transition = OLED_TRANSITION_TOP_DOWN;
				  break;
		  }

		  default : {
				  return GUI_STATUS_ERROR;
		  }
	}

	if(ptrNewScreen == NULL)
	{
		return GUI_STATUS_ERROR;
	}


	if(haptic_CurrentStateGet() == hapticState_enable)
	 {
	 	haptic_MutexLock(OSA_WAIT_FOREVER);
	 	haptic_Run();
	 }

	// end action for the current screen
	if ( NULL != guiDriver_display.guiItem->destroyTaskFunction )
	{
	    osa_status_t
	        mutexStatus;

        mutexStatus = OSA_MutexLock( &spiAccessMutex, OSA_WAIT_FOREVER );
        if ( kStatus_OSA_Success != mutexStatus )
        {
			catch( CATCH_MUTEX );
        }

        // release the mutex, in case destroy function uses OLED
        OSA_MutexUnlock( &spiAccessMutex );

        guiDriver_display.guiItem->destroyTaskFunction(destroyParam);
        OSA_TimeDelay(20); // todo, fine-tune the delay
	}

	// update the current gui item
	guiDriver_display.guiItem = (guiScreen_t*)ptrNewScreen;

	if ( NULL != guiDriver_display.guiItem->image )
	{
		OLED_Swap( (oled_pixel_t)guiDriver_display.image, GuiDriver_SkipHeader(ptrNewScreen->image), OLED_SCREEN_SIZE );
	}
	else
	{
		memset(guiDriver_display.image, 0, OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL);
	}

	// starting action for the new screen
	if( NULL != ptrNewScreen->initFunction )
	{
		ptrNewScreen->initFunction(initParam);
	}

	oled_status_t
	  statusOLED = OLED_STATUS_SUCCESS;

	uint8_t
	  xCrd = 0,
	  yCrd = 0,
	  width,
	  height;

	if ( NULL != guiDriver_display.guiItem->image )
	{
          OLED_GetImageDimensions( &width, &height, (const uint8_t*)guiDriver_display.guiItem->image );
	}
	else
	{
          width = 96;
          height = 96;
	}

	GuiDriver_AddButtonPointers(&guiDriver_display.guiItem->navigation);

	while (1)
    {
        statusOLED = OLED_DrawScreen(
                                        guiDriver_display.image,
                                        xCrd,
                                        yCrd,
                                        width,
                                        height,
                                        transition
                                    );
        if ( OLED_STATUS_SUCCESS == statusOLED )
        {
            break;
        }
    }

	if(haptic_CurrentStateGet() == hapticState_enable)
	{
		//OSA_TimeDelay(50);
		haptic_MutexUnlock();
	}

	if( OLED_STATUS_SUCCESS == statusOLED )
	{
	  // post-load action for the new screen
	  if( NULL != ptrNewScreen->createTaskFunction )
	  {
		ptrNewScreen->createTaskFunction(createParam);
	  }

	  return GUI_STATUS_SUCCESS;
	}

	else
	{
	  return GUI_STATUS_ERROR;
	}
}

/**
 * update the main screen buffer
 * with the given image
 */
void GuiDriver_UpdateScreen (
                                uint8_t xCrd,
                                uint8_t yCrd,

                                uint8_t width,
                                uint8_t height,

                                const uint8_t* image
                              )
{
  // copy data
  oled_pixel_t
    copyAddr = (oled_pixel_t)guiDriver_display.image + ( yCrd*OLED_SCREEN_WIDTH + xCrd );

  for ( uint8_t i = 0; i < height; i++ )
  {
    memcpy( (void*)copyAddr, (void*)image, width*OLED_BYTES_PER_PIXEL );
    copyAddr += OLED_SCREEN_WIDTH;
    image    += width*OLED_BYTES_PER_PIXEL;
  }
}

/**
 * [GuiDriver_LabelCreate description]
 * @param label [description]
 */
gui_status_t GuiDriver_LabelCreate(guiLabel_t *label)
{
	if(label->caption != NULL)
	{
		return GUI_STATUS_ERROR;
	}

	label->caption = (uint8_t *)OSA_MemAlloc(label->captionLength);

	if(label->caption != NULL)
	{
		return GUI_STATUS_SUCCESS;
	}
	else
	{
		return GUI_STATUS_ERROR;
	}
}

/**
 * [GuiDriver_LabelDestroy description]
 * @param label [description]
 */
gui_status_t GuiDriver_LabelDestroy(guiLabel_t *label)
{
	if(label->caption != NULL)
	{
		if(OSA_MemFree(label->caption) != kStatus_OSA_Success)
		{
			return GUI_STATUS_ERROR;
		}
		else
		{
			label->caption = NULL;
			return GUI_STATUS_SUCCESS;
		}
	}

	return GUI_STATUS_ERROR;
}

/**
 * [GuiDriver_LabelSetCaption description]
 * @param label [description]
 * @param caption [description]
 * @param length [description]
 */
void GuiDriver_LabelSetCaption(guiLabel_t *label, uint8_t *caption)
{
	strcpy((char *)label->caption, (char *)caption);
}

/**
 * [GuiDriver_LabelFormatCaption description]
 * @param label [description]
 * @param caption [description]
 * @param length [description]
 * @param format [description]
 */
gui_status_t GuiDriver_LabelFormatCaption(guiLabel_t *label, uint8_t *caption, uint8_t *length, guiLabelCutFormat_t format)
{
	uint8_t tmpLength;
	uint8_t inLength;

	if(length == NULL)
	{
		inLength = strlen((char *)caption);
	}
	else
	{
		inLength = *length;
	}

	if(inLength > (label->captionLength - 1))
	{
		tmpLength = label->captionLength - 1;
	}
	else
	{
		tmpLength = inLength;
	}

	tmpLength = OLED_CharCount(label->dynamicArea.width, label->textProperties.font, caption, tmpLength);
	if(tmpLength == 0)
	{
		return GUI_STATUS_ERROR;
	}

	memcpy(label->caption, caption, tmpLength);
	label->caption[tmpLength] = 0;

	if(tmpLength < inLength)
	{
		if(format == GUI_LABEL_CUT_FORMAT_DOTS)
		{
			if(tmpLength <= 2)
			{
				return GUI_STATUS_ERROR;
			}

			label->caption[tmpLength-1] = '.';
			label->caption[tmpLength-2] = '.';
			tmpLength -= 2;
		}
		else if(format == GUI_LABEL_CUT_FORMAT_SPACE)
		{
			char *tmpPtr;
			tmpPtr = strrchr((char *)label->caption, ' ');
			if(
			    (tmpPtr != NULL) &&
				(tmpPtr != (char *)label->caption)
              )
			{
				*tmpPtr = 0;
				tmpLength = tmpPtr - (char *)label->caption;
			}
		}
	}

	if(length != NULL)
	{
		*length = tmpLength;
	}

	return GUI_STATUS_SUCCESS;
}

/**
 * [GuiDriver_LabelDraw description]
 * @param label [description]
 */
void GuiDriver_LabelDraw(guiLabel_t *label)
{
	OLED_SetTextProperties(&label->textProperties);
	OLED_SetDynamicArea(&label->dynamicArea);
	while (1)
    {
        if ( OLED_STATUS_SUCCESS == OLED_DrawText(label->caption) )
        {
            break;
        }
    }
}

/**
 * [GuiDriver_AddToScrLabel description]
 * @param label [description]
 */
void GuiDriver_LabelAddToScr(guiLabel_t *label)
{
	OLED_SetTextProperties(&label->textProperties);
	OLED_SetDynamicArea(&label->dynamicArea);
	OLED_AddText(label->caption);
}

/**
 * [GuiDriver_ImageDraw description]
 * @param image [description]
 */

void GuiDriver_ImageDraw(guiImage_t *image)
{
	OLED_GetImageDimensions(&image->dynamicArea.width, &image->dynamicArea.height, image->img);
	OLED_SetDynamicArea(&image->dynamicArea);
    while (1)
    {
        if ( OLED_STATUS_SUCCESS == OLED_DrawImage( image->img ) )
        {
            break;
        }
    }
}

/**
 * [GuiDriver_AddToScrImage description]
 * @param image [description]
 */
void GuiDriver_ImageAddToScr(guiImage_t *image)
{
	OLED_GetImageDimensions(&image->dynamicArea.width, &image->dynamicArea.height, image->img);
	OLED_SetDynamicArea(&image->dynamicArea);
	OLED_AddImage(image->img);
}

/**
 *
 * @param upButtonFlag
 * @param downButtonFlag
 */
void GuiDriver_DrawButtonPointers(bool upButtonFlag, bool downButtonFlag)
{
	buttonsGroup_t buttonsGroup;
	guiImage_t *buttonUp;
	guiImage_t *buttonDown;

	buttonsGroup = buttonsGroup_CurrnetActiveGet();

	if(buttonsGroup == buttonsGroup_right)
	{
		buttonUp   = &screen_buttonRightUp;
		buttonDown = &screen_buttonRightDown;
	}
	else
	{
		buttonUp   = &screen_buttonLeftUp;
		buttonDown = &screen_buttonLeftDown;
	}

	if(upButtonFlag)
	{
		GuiDriver_ImageDraw(buttonUp);
	}

	if(downButtonFlag)
	{
		GuiDriver_ImageDraw(buttonDown);
	}

}


static void GuiDriver_AddButtonPointers(guiNavigation_t *navigation)
{
	buttonsGroup_t buttonsGroup;
	guiImage_t *buttonUp;
	guiImage_t *buttonDown;

	buttonsGroup = buttonsGroup_CurrnetActiveGet();

	if(buttonsGroup == buttonsGroup_right)
	{
		buttonUp   = &screen_buttonRightUp;
		buttonDown = &screen_buttonRightDown;
	}
	else
	{
		buttonUp   = &screen_buttonLeftUp;
		buttonDown = &screen_buttonLeftDown;
	}

	if(navigation->up != NULL)
	{
		GuiDriver_ImageAddToScr(buttonUp);
	}

	if(navigation->down != NULL)
	{
		GuiDriver_ImageAddToScr(buttonDown);
	}

}

/**
 * [GuiDriver_ClearScr description]
 */
void GuiDriver_ClearScr(void)
{
	memset( guiDriver_display.image, 0, OLED_SCREEN_WIDTH * OLED_SCREEN_HEIGHT * OLED_BYTES_PER_PIXEL );
	OLED_FillScreen(0);
}

/**
 * [GuiDriver_RegisterForSensor description]
 * @param packetToReceive [description]
 */
void GuiDriver_RegisterForSensors( packet_t packetToReceive, uint32_t delay_ms, bool shouldToggleTask )
{
	if ( 0xFFFFFFFF != delay_ms )
	{
		sensor_RegisterPacketDelay( packetToReceive, delay_ms );
	}
	sensor_SetPacketTargets( packetToReceive, sensor_GetPacketTargets( packetToReceive ) | PACKET_PUSH_OLED, shouldToggleTask );
}

/**
 * [GuiDriver_RegisterForSensor description]
 * @param packetToReceive [description]
 */
void GuiDriver_RegisterMinPollDelay( uint32_t delay )
{
  sensor_SetMinimumDelay( delay );
}

/**
 * [GuiDriver_RegisterForNavigation description]
 * @param navigationDir [description]
 */
void GuiDriver_RegisterForNavigation( guiNavigationDir_t navigations )
{
	guiScreenRegNav |= navigations;
}

/**
 * [GuiDriver_UnregisterFromSensor description]
 * @param packetToReceive [description]
 */
void GuiDriver_UnregisterFromSensors( packet_t packetToReceive, bool shouldDeactivateTask )
{
  sensor_SetPacketTargets( packetToReceive, sensor_GetPacketTargets( packetToReceive ) & ~PACKET_PUSH_OLED, shouldDeactivateTask );
}

/**
 * [GuiDriver_UnregisterFromNavigation description]
 * @param navigationDir [description]
 */
void GuiDriver_UnregisterFromNavigation( guiNavigationDir_t navigations )
{
  guiScreenRegNav &= ~navigations;
}

/**
 * [GuiDriver_CleanMainArea description]
 */
void GuiDriver_CleanMainArea()
{
    while ( OLED_STATUS_SUCCESS != OLED_DrawBox( 0, 20, 90, 55, 0x0 ) ) {}
}

/**
 * [GuiDriver_CleanMainArea description]
 */
void GuiDriver_CleanAbout()
{
    while ( OLED_STATUS_SUCCESS != OLED_DrawBox( 0, 0, 90, 80, 0x0 ) ) {}
}

/**
 * notify KW40 which app is being runned currently
 * @param  currentApp current app descriptor
 * @return            [description]
 */
gui_status_t GuiDriver_NotifyKW40( gui_current_app_t currentApp )
{
//	if ( true == gui_sensorTag_IsActive() )
//	{
//		return GUI_STATUS_SUCCESS;
//	}

    hostInterface_packet_t
        currentAppPacket =
        {
            .type   = packetType_appMode,
            .length = sizeof(currentApp)
        };

    memcpy( (void*)&(currentAppPacket.data[0]), (void*)&currentApp, sizeof(currentApp) );
    currentAppPacket.data[ currentAppPacket.length ] = gHostInterface_trailerByte;

    osa_status_t
        txStatus = HostInterface_TxQueueMsgPut( &currentAppPacket, true );

    if ( kStatus_OSA_Success == txStatus )
    {
        return GUI_STATUS_SUCCESS;
    }
    else
    {
        catch( CATCH_QUEUE );
        return GUI_STATUS_ERROR;
    }
}
