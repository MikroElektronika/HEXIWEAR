
#ifndef _GUI_DRIVER
#define _GUI_DRIVER

#include <stdint.h>
#include <stddef.h>

#include <stdio.h>
#include "fsl_os_abstraction.h"
#include "host_mcu_interface.h"
#include "HEXIWEAR_types.h"
#include "sensor_driver.h"
#include "OLED_driver.h"

#include "error.h"

#include "gui_defs.h"
#include "gui_resources.h"

gui_status_t GuiDriver_Init();
gui_status_t GuiDriver_ButtonsHandler(hostInterface_packet_t* packet);
gui_status_t GuiDriver_Navigation(guiNavigationDir_t navigationDir, void *param);

/**
 * queues
 */

/**
 * push to menu queue
 * @param  packet [description]
 * @return        [description]
 */
gui_status_t GuiDriver_QueueMsgPut(
                                    hostInterface_packet_t* packet
                                  );


/**
 *    This function gets a message from the head of the Tx message queue.
 *
 *    @param    packet   Pointer to a memory to save the packet.
 *
 *    @return                          kStatus_OSA_Success  Message successfully obtained from the queue.
 *                                     kStatus_OSA_Error    Process fail.
 */
gui_status_t GuiDriver_QueueMsgGet(
                                    hostInterface_packet_t* packet,
					                uint32_t timeout
                                  );

// update the main screen buffer
void GuiDriver_UpdateScreen (
						      uint8_t xCrd,
							  uint8_t yCrd,

							  uint8_t width,
							  uint8_t height,

							  const uint8_t* image
						    );

/**
 * [GuiDriver_LabelCreate description]
 * @param label [description]
 */
gui_status_t GuiDriver_LabelCreate(guiLabel_t *label);

/**
 * [GuiDriver_LabelDestroy description]
 * @param label [description]
 */
gui_status_t GuiDriver_LabelDestroy(guiLabel_t *label);

/**
 * [GuiDriver_LabelDraw description]
 * @param label [description]
 * @param caption [description]
 * @param length [description]
 */
void GuiDriver_LabelSetCaption(guiLabel_t *label, uint8_t *caption);

/**
 * [GuiDriver_LabelFormatCaption description]
 * @param label [description]
 * @param caption [description]
 * @param length [description]
 * @param format [description]
 */
gui_status_t GuiDriver_LabelFormatCaption(guiLabel_t *label, uint8_t *caption, uint8_t *length, guiLabelCutFormat_t format);

/**
 * [GuiDriver_LabelDraw description]
 * @param label [description]
 */
void GuiDriver_LabelDraw(guiLabel_t *label);

/**
 * [GuiDriver_LabelAddToScr description]
 * @param label [description]
 */
void GuiDriver_LabelAddToScr(guiLabel_t *label);

/**
 * [GuiDriver_ImageDraw description]
 * @param image [description]
 */
void GuiDriver_ImageDraw(guiImage_t *image);

/**
 * [GuiDriver_ImageAddToScr description]
 * @param image [description]
 */
void GuiDriver_ImageAddToScr(guiImage_t *image);

/**
 * [GuiDriver_DrawButtonPointers description]
 * @param upButtonFlag [description]
 * @param downButtonFlag [description]
 */
void GuiDriver_DrawButtonPointers(bool upButtonFlag, bool downButtonFlag);

/**
 * [GuiDriver_ClearScr description]
 * @param color [description]
 */

void GuiDriver_ClearScr(void);

/**
 * [GuiDriver_RegisterForSensor description]
 * @param packetToReceive [description]
 */
void GuiDriver_RegisterForSensors( packet_t packetToReceive, uint32_t delayMultiple, bool shouldToggleTask );

/**
 * [GuiDriver_RegisterForSensor description]
 * @param packetToReceive [description]
 */
void GuiDriver_RegisterMinPollDelay( uint32_t delay );

/**
 * [GuiDriver_RegisterForNavigation description]
 * @param navigationDir [description]
 */
void GuiDriver_RegisterForNavigation( guiNavigationDir_t navigations );

/**
 * [GuiDriver_UnregisterForSensor description]
 * @param packetToReceive [description]
 */
void GuiDriver_UnregisterFromSensors( packet_t packetToReceive, bool shouldDeactivateTask );

/**
 * [GuiDriver_UnregisterFromNavigation description]
 * @param navigationDir [description]
 */
void GuiDriver_UnregisterFromNavigation( guiNavigationDir_t navigations );

/**
 * [GuiDriver_CleanMainArea description]
 */
void GuiDriver_CleanMainArea();

/**
 * notify KW40 which app is being runned currently
 * @param  currentApp current app descriptor
 * @return            [description]
 */
gui_status_t GuiDriver_NotifyKW40( gui_current_app_t currentApp );

/**
 * [GuiDriver_CleanMainArea description]
 */
void GuiDriver_CleanAbout();

#endif
