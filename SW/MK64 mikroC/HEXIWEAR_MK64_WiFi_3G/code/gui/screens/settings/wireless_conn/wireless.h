// File: wifi.h

// Declarations of main functionalities in the wireless gui module.

#ifndef _WIRELESS_h_
#define _WIRELESS_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define WIRELESS_STACK_SIZE ( 0x500 )
#define WIRELESS_PRIO       ( HEXIWEAR_GUI_PRIO )

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// screens
//extern guiScreen_t wirelessScreen;
extern task_handler_t wireless_clickHandler;
extern task_handler_t wireless_taskHandler;
extern task_handler_t wireless_parameterHandler;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

void wireless_Init( void *param );
void wireless_CreateTasks( void *param );
void wireless_DestroyTasks( void *param );

void wifi_setSSID(char* ssid);
void wifi_setSSIDPassword(char* password);
void wifi_setMQTTUsername(char* username);
void wifi_setMQTTPassword(char* password);
void wifi_setClickPosition(int clickPosition);
void wifi_setWiFiAuth(int wifiAuth);
void setConnStatus (int status);

void wireless_initializeTasks();
void wifi_SendBluetoothParameters();
int wireless_CheckAtStartup();


/******************************************************************************
 * Global function declarations.                                              *
 ******************************************************************************/


//int send_g3_message (unsigned char message[], int length);
int g3_send_to_cloud (const char* message);

void g3_setName(char* name);
void g3_setUsername(char* username);
void g3_setPassword(char* password);

void g3_SendBluetoothParameters();

#endif