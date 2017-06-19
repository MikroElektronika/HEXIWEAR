// File: wifi_private.h

// Declarations of resources in the wifi gui module.

#ifndef _wifi_private_h_
#define _wifi_private_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable declarations.                                              //
////////////////////////////////////////////////////////////////////////////////
int wifi_send_to_cloud (const char * message);

static void wifi_SensorTask( task_param_t param );
static void wifi_ParamTask( task_param_t param );
static void wifi_ToggleTask( task_param_t param );
static void wifi_RefreshTask( task_param_t param );

void registerSensors();
void stopSensorTasks(int messageErrortype, bool stopSensor);
void startSensorTasks();

void writeToFlash();
void writeConnectionToFlash();
void writeWiFiToFlash();

void resetPacket(hostInterface_packet_t *packet, int packetType, int packetLength);
void wifi_SendInt(int value, int type);
void wifi_SendSSID(char ssid[32]);
void wifi_SendSSIDPassword(char password[64]);

int send_to_cloud (const char * message);

void g3_writeToFlash();
void g3_writeG3ToFlash();
void recover_3g(const int clickPosition);

void g3_SendG3Param(char param[32], int type);


#endif