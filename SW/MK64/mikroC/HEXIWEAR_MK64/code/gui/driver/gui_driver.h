// File: gui_driver.h

// Declarations of main functionalities of the gui driver module.

#ifndef _gui_driver_h_
#define _gui_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include "OSA.h"
#include "OLED_driver.h"

#include "gui_defs.h"
#include "gui_resources.h"

#include "sensor_info.h"
#include "sensor_types.h"

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialise the gui driver module.
gui_status_t GuiDriver_Init();

// Handler for gui buttons.
gui_status_t GuiDriver_ButtonsHandler( hostInterface_packet_t* packet );

// Navigates from the current to the next screen.
gui_status_t GuiDriver_Navigation(
    guiNavigationDir_t navigationDir, void *param );

// Puts a message into the gui driver message queue.
gui_status_t GuiDriver_QueueMsgPut( hostInterface_packet_t* packet );

// Gets a message from the gui driver message queue.
gui_status_t GuiDriver_QueueMsgGet(
    hostInterface_packet_t* packet, uint32_t timeout );

// Updates the main screen buffer.
void GuiDriver_UpdateScreen (
    uint8_t xCrd,
    uint8_t yCrd,
    uint8_t width,
    uint8_t height,
    const uint8_t* image );

// Creates a label.
gui_status_t GuiDriver_LabelCreate( guiLabel_t *label );

// Destroys a label.
gui_status_t GuiDriver_LabelDestroy( guiLabel_t *label );

// Sets the caption of a label.
void GuiDriver_LabelSetCaption( guiLabel_t *label, uint8_t *caption );

// Formats the caption of a label.
gui_status_t GuiDriver_LabelFormatCaption( guiLabel_t *label, uint8_t *caption,
    uint8_t *length, guiLabelCutFormat_t format );

// Draws the given label.
void GuiDriver_LabelDraw( guiLabel_t *label );

// Adds a label to the screen.
void GuiDriver_LabelAddToScr( guiLabel_t *label );

// Draws the given image.
void GuiDriver_ImageDraw( guiImage_t *image );

// Adds an image to the screen.
void GuiDriver_ImageAddToScr( guiImage_t *image );

// Draws button pointers on the screen.
void GuiDriver_DrawButtonPointers( bool upButtonFlag, bool downButtonFlag );

// Clears the screen.
void GuiDriver_ClearScr();

// Registers for sensor data.
void GuiDriver_RegisterForSensors(
    packet_t packetToReceive, uint32_t delay_ms, bool shouldToggleTask );

// Sets minimum delay for sensors.
void GuiDriver_RegisterMinPollDelay( uint32_t delay );

// Adds navigation to the navigation register.
void GuiDriver_RegisterForNavigation( guiNavigationDir_t navigations );

// Un-registers for sensor data.
void GuiDriver_UnregisterFromSensors(
    packet_t packetToReceive, bool shouldDeactivateTask );

// Removes a navigation from the navigation register.
void GuiDriver_UnregisterFromNavigation( guiNavigationDir_t navigations );

// Cleans the main area of the screen.
void GuiDriver_CleanMainArea();

// Cleans most of the screen.
void GuiDriver_CleanAbout();

// Notifies KW40 about the current app.
gui_status_t GuiDriver_NotifyKW40( gui_current_app_t currentApp );

// Writes formatted output to sized buffer.
//uint8_t snprintf( uint8_t * s, uint8_t n, const code uint8_t * format, ... );

#endif