// File: wifi_driver.c

// Definitions of main functionalities in the wifi gui module.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "HEXIWEAR_info.h"
#include "HEXIWEAR_types.h"

#include "gui_driver.h"
#include "wireless.h"
#include "watch/watch.h"
#include "wireless_private.h"
#include "settings/haptic/haptic.h"
#include "error.h"
#include "wolksense_wifi/include/wifi_3g_impl.h"
#include "wolksense_wifi/include/mqtt_wolksense_wifi.h"
#include "sensor_driver.h"
#include "sensor_types.h"
#include "apps/flashlight/flashlight.h"
#include "sensorTag/gui_sensorTag.h"
#include "power/power.h"
#include "settings/bluetooth/bluetooth.h"
#include "settings/wireless_conn/wireless_common.h"
#include "settings/reset/reset.h"
#include "mqtt_wolksense_3g.h"
#include "OSA.h"

/******************************************************************************
 * Macro definitions.                                                         *
 ******************************************************************************/

// Converts milliseconds to ticks.
#define MSEC_TO_TICK( msec )                                                   \
    ( ( ( uint32_t )( msec ) + 500uL / ( uint32_t )configTICK_RATE_HZ )        \
    * ( uint32_t )configTICK_RATE_HZ / 1000uL )

#define SetFlashOFF()                                                          \
    isFlashlightOn = false;                                                    \
    FLASH_SetOFF();                                                            \

#define SetFlashON()                                                           \
    isFlashlightOn = true;                                                     \
    FLASH_SetON();
    
    
    
#define NULL 0
#define CR           0x0D
#define LF           0x0A
#define RX_BUFF_LEN 1000
#define ONE_SEC 1000
#define TWO_SEC 2000
#define CONNECTION_TYPE "TCP"

#define RESP_FALSE -1
#define RESP_TRUE 0
#define RESP_CONNECTION_FAIL 99 

#define MEASUREMENT_TIMEOUT 30000
#define QUEUE_TIMEOUT 3000 

#define ERR_CRIT_NUM 5                                                           \

/******************************************************************************
 * Static variable definitions.                                               *
 ******************************************************************************/

typedef enum connection_state
{
    csIDLE,
    csCONNECTING,
    csCONNECTED,
} connection_state_t;

task_handler_t wireless_refreshHandler;
task_handler_t wireless_toggleHandler;
task_handler_t wireless_paramHandler;
task_handler_t wireless_sensorHandler;

static bool isWiFiOn;
static bool isFlashlightOn;
static connection_state_t connectionState;

static mE_t temperatureValue;
static mE_t humidityValue;
static mE_t pressureValue;

static mE_t accelerationValue[3];
static mE_t gyroValue[3];
static mE_t magnetValue[3];

static uint16_t TSL_adcData[2];

static hostInterface_packet_t wireless_dataPacket;

hexiwear_connection_flags_t hexiwear_connectionFlags;
hexiwear_wifi_flags_t hexiwear_wifiFlags;


const char server_addr[] = "52.30.233.2";
const char port[] = "1883";
static char topic[64] = {0};

static int wirelessMissingError = 0;


static bool isG3On;
hexiwear_g3_flags_t g3Flags;

/******************************************************************************
 * Static function definitions.                                               *
 ******************************************************************************/

static void wireless_SensorTask( task_param_t param )
{
    int ret = 1;
    int retry_count = 0;
    int error_count;

    osa_status_t mutexStatus;
    int8_t tmp8;
    int16_t tmp16;
    volatile int32_t tmp32;

    char message_pt1[256] = {0};
    char message_pt2[64] = {0};

    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_29 ); // PWR_HR
    PTA_PDOR.B29 = 0;
    OSA_TimeDelay( 10 );
    PTA_PDOR.B29 = 1;
    do
    {

        memset (message_pt1, 0, 256);
        memset(message_pt2, 0, 64);

        strcat (message_pt1,"RTC 1485161653;READINGS R:1485161653,");

        tmp16 = HTU_TempFormatInt(temperatureValue);
        if (tmp16>=0)
        {
            sprintf(message_pt1 + strlen(message_pt1), "T:+%d", temperatureValue/10 );
        }
        else
        {
            sprintf(message_pt1 + strlen(message_pt1), "T:%d", temperatureValue/10 );
        }

        tmp32 = pressureValue;
        tmp16 = MPL_FormatInt( tmp32 );
        sprintf(message_pt1 + strlen(message_pt1), ",P:+%d", pressureValue);

        tmp16 = HTU_HumFormatInt( humidityValue );
        sprintf(message_pt1 + strlen(message_pt1), ",H:+%d", humidityValue / 10);


        TSL_CalculateLux( TSL_adcData, &tmp32 );
        TSL_FormatLux( tmp32, &tmp8 );
        sprintf(message_pt1 + strlen(message_pt1), ",LT:+%d", tmp8 * 10 );

        tmp16 = FXOS_AccFormatInt( accelerationValue[0] );
        if( tmp16 >= 0 )
        {
          sprintf(message_pt1 + strlen(message_pt1), ",ACL:+%02i", accelerationValue[0] / 10 );
        }
        else
        {
          sprintf(message_pt1 + strlen(message_pt1), ",ACL:-%02i", abs( accelerationValue[0] / 10 ));
        }

        tmp16 = FXOS_AccFormatInt( accelerationValue[1] );
        if( tmp16 >= 0 )
        {
          sprintf(message_pt1 + strlen(message_pt1), "+%02i", accelerationValue[1] / 10 );
        }
        else
        {
          sprintf(message_pt1 + strlen(message_pt1), "-%02i", abs( accelerationValue[1] / 10 ));
        }

        tmp16 = FXOS_AccFormatInt( accelerationValue[2] );
        if( tmp16 >= 0 )
        {
          sprintf(message_pt1 + strlen(message_pt1), "+%02i", accelerationValue[2] / 10 );
        }
        else
        {
          sprintf(message_pt1 + strlen(message_pt1), "-%02i", abs( accelerationValue[2] / 10 ));
        }

        tmp16 = FXOS_MagFormatInt( magnetValue[0] );
        if( tmp16 >= 0 )
        {
          sprintf(message_pt1 + strlen(message_pt1), ",MAG:+%02i", magnetValue[0] / 10);
        }
        else
        {
          sprintf(message_pt1 + strlen(message_pt1), ",MAG:-%02i", abs(magnetValue[0]) / 10);
        }

        tmp16 = FXOS_MagFormatInt( magnetValue[1] );
        if( tmp16 >= 0 )
        {
          sprintf(message_pt1 + strlen(message_pt1), "+%02i", magnetValue[1]);
        }
        else
        {
          sprintf(message_pt1 + strlen(message_pt1), "-%02i", abs(magnetValue[1]) / 10);
        }

        tmp16 = FXOS_MagFormatInt( magnetValue[2] );
        if( tmp16 >= 0 )
        {
          sprintf(message_pt1 + strlen(message_pt1), "+%02i", magnetValue[2] / 10);
        }
        else
        {
          sprintf(message_pt1 + strlen(message_pt1), "-%02i", abs( magnetValue[2]) / 10);
        }
        sprintf(message_pt1 + strlen(message_pt1), ";");


        sprintf(message_pt2,"RTC 1485161653;READINGS R:1485161653,");
        tmp16 = FXAS_FormatInt( gyroValue[0]) * 10;
        if (tmp16>=0)
        {
          sprintf(message_pt2 + strlen(message_pt2), "GYR:+%02i", gyroValue[0] * 10);
        }
        else
        {
          sprintf(message_pt2 + strlen(message_pt2), "GYR:-%02i", abs(gyroValue[0]) * 10);
        }

        tmp16 = FXAS_FormatInt(gyroValue[1]) * 10;
        if (tmp16>=0)
        {
          sprintf(message_pt2 + strlen(message_pt2), "+%02i", gyroValue[1] * 10);
        }
        else
        {
          sprintf(message_pt2 + strlen(message_pt2), "-%02i", abs(gyroValue[1]) * 10);
        }

        tmp16 = FXAS_FormatInt(gyroValue[2]) * 10;
        if (tmp16>=0)
        {
          sprintf(message_pt2 + strlen(message_pt2), "+%02i", gyroValue[2] * 10);
        }
        else
        {
          sprintf(message_pt2 + strlen(message_pt2), "-%02i", abs(gyroValue[2]) * 10);
        }


        sprintf(message_pt2 + strlen(message_pt2), ";" );


        if(isWiFiOn)
        {
            if(connectionState == csIDLE)
            {
                connectionState = csCONNECTING;
                SetFlashON();

                // Initialize WiFI module
                watch_LinkStateWiFiUpdate( linkState_wifi_disconnected );
                init_wifi(hexiwear_connectionFlags.socketPosition);
                if(configure_wifi(hexiwear_wifiFlags.ssid, hexiwear_wifiFlags.ssid_password) == 0)
                {
                   break;
                }
                connectionState = csCONNECTED;
            }
            
            //Sending message 1
            if (wifi_send_to_cloud (message_pt1)!=0)
            {
                //error
                OSA_TimeDelay(1000);
                watch_LinkStateWiFiUpdate( linkState_wifi_disconnected );
                continue;
             }

             //Sending message 2
             if (wifi_send_to_cloud (message_pt2)!=0)
             {
                 //error
                 OSA_TimeDelay(1000);
                 watch_LinkStateWiFiUpdate( linkState_wifi_disconnected );
                 continue;
             }
             SetFlashOFF();

             watch_LinkStateWiFiUpdate( linkState_wifi_connected );


        } else if (isG3On)
        {
             if(connectionState == csIDLE)
             {
                watch_LinkState3gUpdate( linkState_3g_disconnected );
                SetFlashON();
                connectionState = csCONNECTING;
                init_3g(hexiwear_connectionFlags.socketPosition);
                while (configure_3g(g3Flags.g3_name, g3Flags.g3_username, g3Flags.g3_password)!=0 && retry_count < 5)
                {
                      OSA_TimeDelay(1000);
                      retry_count++;
                }

                if (retry_count == 5)
                {
                     break;
                }

                connectionState = csCONNECTED;
             }

             if (g3_send_to_cloud (message_pt1)!=0)
             {
                 watch_LinkState3gUpdate( linkState_3g_disconnected );
                 error_count++;
                 if (error_count==ERR_CRIT_NUM)
                 {
                     recover_3g(hexiwear_connectionFlags.socketPosition);
                     error_count=0;
                     connectionState = csIDLE;
                 }
                 OSA_TimeDelay(1000);
                 continue;
             }
             watch_LinkState3gUpdate( linkState_3g_connected );
             OSA_TimeDelay(1000);

             if (g3_send_to_cloud (message_pt2)!=0)
             {
                 watch_LinkState3gUpdate( linkState_3g_disconnected );
                 error_count++;
                 if (error_count==ERR_CRIT_NUM)
                 {
                     recover_3g(hexiwear_connectionFlags.socketPosition);
                     error_count=0;
                     connectionState = csIDLE;
                 }
                 OSA_TimeDelay(1000);
                 continue;
             }
             SetFlashOFF();
             error_count = 0;
             watch_LinkState3gUpdate( linkState_3g_connected);
        }
        OSA_TimeDelay(MEASUREMENT_TIMEOUT);
    }
    while (1);
    if ( hexiwear_connectionFlags.activeConnectionType == 1)
    {
         watch_LinkStateWiFiUpdate( linkState_wifi_off );
    }
    else if ( hexiwear_connectionFlags.activeConnectionType == 2 )
    {
         watch_LinkState3gUpdate( linkState_3g_off );
    }
    stopSensorTasks(wirelessMissingError, false);
    writeConnectionToFlash();
    OSA_TaskDestroy( wireless_sensorHandler );
}

static void wireless_ParamTask( task_param_t param )
{
    while( 1 )
    {
        GuiDriverFlash_QueueMsgGet( &wireless_dataPacket, OSA_WAIT_FOREVER );
        switch( wireless_dataPacket.type )
        {
            case packetType_temperature:
            {
                 temperatureValue = ( mE_t )( wireless_dataPacket._data[0] | ( mE_t)wireless_dataPacket._data[1] << 8 );
                 break;
            }
            case packetType_humidity:
            {
                 humidityValue = ( mE_t )( wireless_dataPacket._data[0] | ( mE_t)wireless_dataPacket._data[1] << 8 );
                 break;
            }
            case packetType_pressure:
            {
                 pressureValue = ( mE_t )( wireless_dataPacket._data[0] | ( mE_t)wireless_dataPacket._data[1] << 8 );
                 break;
            }
            case packetType_ambiLight:
            {
                 TSL_ReadRawData(TSL_CHANNEL_FULL, &(TSL_adcData[0]));
                 TSL_ReadRawData(TSL_CHANNEL_INFRARED, &(TSL_adcData[1]));
                 break;
            }
            case packetType_accel:
            {
                 accelerationValue[0] = (mE_t)(wireless_dataPacket._data[0] | (mE_t)wireless_dataPacket._data[1] << 8);
                 accelerationValue[1] = (mE_t)(wireless_dataPacket._data[2] | (mE_t)wireless_dataPacket._data[3] << 8);
                 accelerationValue[2] = (mE_t)(wireless_dataPacket._data[4] | (mE_t)wireless_dataPacket._data[5] << 8);
                 break;
            }
            case packetType_gyro:
            {
                 gyroValue[0] = (mE_t)(wireless_dataPacket._data[0] | (mE_t)wireless_dataPacket._data[1] << 8);
                 gyroValue[1] = (mE_t)(wireless_dataPacket._data[2] | (mE_t)wireless_dataPacket._data[3] << 8);
                 gyroValue[2] = (mE_t)(wireless_dataPacket._data[4] | (mE_t)wireless_dataPacket._data[5] << 8);
                 break;
            }
            case packetType_magnet:
            {
                 magnetValue[0] = (mE_t)(wireless_dataPacket._data[0] | (mE_t)wireless_dataPacket._data[1] << 8 );
                 magnetValue[1] = (mE_t)(wireless_dataPacket._data[2] | (mE_t)wireless_dataPacket._data[3] << 8);
                 magnetValue[2] = (mE_t)(wireless_dataPacket._data[4] | (mE_t)wireless_dataPacket._data[5] << 8);
                 break;
            }
        }
    }
}

void startSensorTasks()
{
    osa_status_t status;
    power_DisablePowerSave();
    
    if(connectionState == csIDLE)
    {
        status = OSA_TaskCreate(
            wireless_ParamTask,
            ( uint8_t* )"wireless_ParamTask",
            WIRELESS_STACK_SIZE,
            NULL,
            WIRELESS_PRIO,
            ( task_param_t )0,
            false,
            &wireless_paramHandler
        );

        if( status != kStatus_OSA_Success )
        {
            error_catch( CATCH_INIT );
        }

        status = OSA_TaskCreate(
            wireless_SensorTask,
            ( uint8_t* )"wireless_SensorTask",
            WIRELESS_STACK_SIZE,
            NULL,
            WIRELESS_PRIO,
            ( task_param_t )0,
            false,
            &wireless_sensorHandler
        );

        if( status != kStatus_OSA_Success )
        {
            error_catch( CATCH_INIT );
        }
    }
}

void stopSensorTasks(int messageErrorType, bool stopSensor)
{
    power_EnablePowerSave();
    isWiFiOn = false;
    isG3On = false;

    if(stopSensor)
    {
        OSA_TaskDestroy( wireless_sensorHandler );
    }
    OSA_TaskDestroy( wireless_paramHandler );
    SetFlashOFF();
    connectionState = csIDLE;
    if(messageErrorType > -1)
    {
        watch_LinkStateWiFiUpdate( linkState_wifi_off );
        GuiDriver_Navigation( GUI_NAVIGATION_MESSAGE, ( void* )&messageErrorType );
    }
}

// Toggles the LEDS, making them active/inactive.
static void wireless_RefreshTask( task_param_t param )
{
    while( 1 )
    {
        if (hexiwear_connectionFlags.activeConnectionType == 1)
        {
            wireless_icon.img = isWiFiOn ? wifi_icon_on_bmp : wifi_icon_off_bmp;
            GuiDriver_ImageDraw( &wireless_icon );

        } else if ( hexiwear_connectionFlags.activeConnectionType == 2 )
        {
            wireless_icon.img = isG3On ? g3_icon_on_bmp : g3_icon_off_bmp;
            GuiDriver_ImageDraw( &wireless_icon );
            
        } else if (hexiwear_connectionFlags.activeConnectionType == 0)
        {
            wireless_icon.img = none_icon_bmp;
            GuiDriver_ImageDraw( &wireless_icon );
        
        }
        OSA_TimeDelay( QUEUE_TIMEOUT);
    }
}

static void wireless_ToggleTask( task_param_t param )
{
    while( 1 )
    {
        OSA_TimeDelay(10);
        GuiDriver_QueueMsgGet( &wireless_dataPacket, OSA_WAIT_FOREVER );

        if (hexiwear_connectionFlags.activeConnectionType == 1)
        {
            isG3On = false;
            watch_LinkState3gUpdate( 2 );
            wireless_icon.img = isWiFiOn ? wifi_icon_on_bmp : wifi_icon_off_bmp;
            GuiDriver_ImageDraw( &wireless_icon );
            if(wireless_dataPacket.type == packetType_pressRight )
            {
                if(isWiFiOn)
                {
                    isWiFiOn = false;
                    watch_LinkStateWiFiUpdate( linkState_wifi_off );
                    stopSensorTasks(-1, true);
                    writeToFlash();
                    wireless_icon.img = wifi_icon_off_bmp;
                    GuiDriver_ImageDraw( &wireless_icon );
                }
                else if(strlen(hexiwear_wifiFlags.ssid) > 0 && strlen(hexiwear_connectionFlags.mqtt_username) > 0 && strlen(hexiwear_connectionFlags.mqtt_password) > 0)
                {
                    isWiFiOn = true;
                    watch_LinkStateWiFiUpdate( linkState_wifi_on );
                    startSensorTasks();
                    writeToFlash();
                    wireless_icon.img = wifi_icon_on_bmp;
                    GuiDriver_ImageDraw( &wireless_icon );
                }
            }
        } else if (hexiwear_connectionFlags.activeConnectionType == 2)
        {
            isWiFiOn = false;
            watch_LinkStateWiFiUpdate( linkState_wifi_off );
            wireless_icon.img = isG3On ? g3_icon_on_bmp : g3_icon_off_bmp;
            GuiDriver_ImageDraw( &wireless_icon );
            if(isG3On)
            {
                isG3On = false;
                watch_LinkState3gUpdate( linkState_3g_off );
                stopSensorTasks(-1, true);
                g3_writeToFlash();
                wireless_icon.img = g3_icon_off_bmp;
                GuiDriver_ImageDraw( &wireless_icon );
            }
            else if(strlen(hexiwear_connectionFlags.mqtt_username) > 0 && strlen(hexiwear_connectionFlags.mqtt_password) > 0)
            {
                isG3On = true;
                watch_LinkState3gUpdate( linkState_3g_on );
                startSensorTasks();
                g3_writeToFlash();
                wireless_icon.img = g3_icon_on_bmp;
                GuiDriver_ImageDraw( &wireless_icon );
            }
        }
    }
}

/******************************************************************************
 * Global function definitions.                                               *
 ******************************************************************************/

void registerSensors()
{
    if(connectionState == csIDLE)
    {
        GuiDriver_RegisterForSensorsFlash( PACKET_TEMP, 1000, false);
        GuiDriver_RegisterForSensorsFlash( PACKET_PRES, 1000, false);
        GuiDriver_RegisterForSensorsFlash( PACKET_HUM, 1000, false);
        GuiDriver_RegisterForSensorsFlash( PACKET_ACC, 1000, false);
        GuiDriver_RegisterForSensorsFlash( PACKET_GYRO, 1000, false);
        GuiDriver_RegisterForSensorsFlash( PACKET_MAG, 1000, false);
        GuiDriver_RegisterForSensorsFlash( PACKET_LUX, 1000, false);
    }
}

// Initialises wireless GUI.
void wireless_Init( void *param )
{
    GuiDriver_ImageAddToScr( &wireless_icon );
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
    //3G related
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_12 );
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_13 );
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_14 );
}

// Creates wireless GUI tasks.
void wireless_CreateTasks( void *param )
{
    osa_status_t status;

    status = OSA_TaskCreate(
         wireless_ToggleTask,
         ( uint8_t* )"wireless ToggleTask",
         WIRELESS_STACK_SIZE,
         NULL,
         WIRELESS_PRIO,
         ( task_param_t )0,
         false,
         &wireless_toggleHandler
    );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }
    
    status = OSA_TaskCreate(
        wireless_RefreshTask,
        ( uint8_t* )"wireless RefreshTask",
        WIRELESS_STACK_SIZE,
        NULL,
        WIRELESS_PRIO,
        ( task_param_t )0,
        false,
        &wireless_refreshHandler
    );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }

    registerSensors();
}

// Destroys wireless GUI tasks.
void wireless_DestroyTasks( void *param )
{
    osa_status_t status;

    if(wireless_toggleHandler)
    {
        status = OSA_TaskDestroy( wireless_toggleHandler );
    }
    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }
    
    
    if(wireless_refreshHandler)
    {
        status = OSA_TaskDestroy( wireless_refreshHandler );
    }
    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }

    if(connectionState == csIDLE)
    {
        GuiDriver_UnregisterFromSensorsFlash( PACKET_TEMP, false);
        GuiDriver_UnregisterFromSensorsFlash( PACKET_PRES, false);
        GuiDriver_UnregisterFromSensorsFlash( PACKET_HUM, false);
        GuiDriver_UnregisterFromSensorsFlash( PACKET_ACC, false);
        GuiDriver_UnregisterFromSensorsFlash( PACKET_GYRO, false);
        GuiDriver_UnregisterFromSensorsFlash( PACKET_MAG, false);
        GuiDriver_UnregisterFromSensorsFlash( PACKET_LUX, false);
    }

    OLED_DestroyDynamicArea();
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}

int wifi_send_to_cloud (const char * message)
{
    if(connect_server_wifi(server_addr, port) != 0)
    {
      OSA_TimeDelay(1000);
      return 1;
    }

    if(connect_broker_wifi(hexiwear_connectionFlags.mqtt_username, hexiwear_connectionFlags.mqtt_password) != 0)
    {
      OSA_TimeDelay(1000);
      return 1;
    }


    if(publish_broker_wifi(message, topic) != 0)
    {
      OSA_TimeDelay(1000);
      return 1;
    }

    if(disconnect_server_wifi() != 0)
    {
      OSA_TimeDelay(1000);
      return 1;
    }

    return 0;

}

void wifi_setSSID(char* id)
{
    memset(hexiwear_wifiFlags.ssid, 0, 32);
    strncpy(hexiwear_wifiFlags.ssid, id, 32);
    writeWiFiToFlash();
}

void wifi_setSSIDPassword(char* password)
{
    memset(hexiwear_wifiFlags.ssid_password, 0, 64);
    strncpy(hexiwear_wifiFlags.ssid_password, password, 64);
    writeWiFiToFlash();
}

void wifi_setWiFiAuth(int wifiAuth)
{
    hexiwear_wifiFlags.wifi_auth = wifiAuth;
    writeWiFiToFlash();
}

void wifi_setMQTTUsername(char* username)
{
    sprintf(topic,"sensors/%s", username) ;
    memset(hexiwear_connectionFlags.mqtt_username, 0, 32);
    strncpy(hexiwear_connectionFlags.mqtt_username, username, 32);
    writeConnectionToFlash();
}

void wifi_setMQTTPassword(char* password)
{
    memset(hexiwear_connectionFlags.mqtt_password, 0, 32);
    strncpy(hexiwear_connectionFlags.mqtt_password, password, 32);
    writeConnectionToFlash();
}

void wifi_setClickPosition(int clickPosition)
{

    hexiwear_connectionFlags.socketPosition  = clickPosition;
    writeConnectionToFlash();
}

void setConnStatus (int status)
{
     hexiwear_connectionFlags.activeConnectionType = status;
     writeConnectionToFlash();
}

int wireless_CheckAtStartup()
{
    int ret_val = -1;
    isWiFiOn = false;
    isG3On = false;

    memcpy( ( void* )&hexiwear_connectionFlags, (const void*)HEXIWEAR_CONNECTION_FLAGS, sizeof(hexiwear_connectionFlags));
    memcpy( ( void* )&hexiwear_wifiFlags, (const void*)HEXIWEAR_WIFI_FLAGS, sizeof(hexiwear_wifiFlags));
    memcpy( ( void* )&g3Flags, (const void*)HEXIWEAR_G3_FLAGS, sizeof(g3Flags));
        
    if(HEXIWEAR_CONNECTION_FLAGS->toggledConnection >= 0 && HEXIWEAR_CONNECTION_FLAGS->toggledConnection <= 2)
    {
        sprintf(topic, "sensors/%s", hexiwear_connectionFlags.mqtt_username) ;
    }

    if (hexiwear_connectionFlags.activeConnectionType == 1)
    {
        if(hexiwear_connectionFlags.toggledConnection == 1)
        {
            isWiFiOn = true;
            OSA_TimeDelay(1000);
            watch_LinkStateWiFiUpdate( linkState_wifi_on ); //TODO: fix hardcoded value
            registerSensors();
            startSensorTasks();
        }
    } else if (hexiwear_connectionFlags.activeConnectionType == 2)
    {
        if(hexiwear_connectionFlags.toggledConnection == 2)
        {
            watch_LinkState3gUpdate( linkState_3g_on ); //TODO: fix hardcoded value
            isG3On = true;
            OSA_TimeDelay(1000);
            registerSensors();
            startSensorTasks();
        }
    }else
    {
        hexiwear_connectionFlags.activeConnectionType = 0;
    }
    
    return ret_val;
}

void writeWiFiToFlash()
{
    if (strlen(hexiwear_wifiFlags.ssid) > 0 &&
        strlen(hexiwear_wifiFlags.ssid_password) > 0 &&
        hexiwear_wifiFlags.wifi_auth >= 0 &&
        hexiwear_wifiFlags.wifi_auth <= 2)
    {
        HEXIWEAR_SetFlags((uint32_t )HEXIWEAR_WIFI_FLAG_ADDRESS, (void*)&hexiwear_wifiFlags, sizeof(hexiwear_wifiFlags));
    }
}

void writeConnectionToFlash()
{
    if (strlen(hexiwear_connectionFlags.mqtt_password) > 0 &&
        strlen(hexiwear_connectionFlags.mqtt_username) > 0 &&
        hexiwear_connectionFlags.socketPosition >= 1 &&
        hexiwear_connectionFlags.socketPosition <=3)
    {
        if (isWiFiOn == true)
        {
             hexiwear_connectionFlags.toggledConnection = 1;
        } else if (isG3On == true)
        {
             hexiwear_connectionFlags.toggledConnection = 2;
        } else
        {
             hexiwear_connectionFlags.toggledConnection = 0;
        }
        HEXIWEAR_SetFlags((uint32_t )HEXIWEAR_CONNECTION_FLAG_ADDRESS, (void*)&hexiwear_connectionFlags, sizeof(hexiwear_connectionFlags));
    }
}

void writeToFlash()
{
    writeWiFiToFlash();
    writeConnectionToFlash();
}

void resetPacket(hostInterface_packet_t *packet, int packetType, int packetLength)
{
    packet->start1 =  gHostInterface_startByte1;
    packet->start2 =  gHostInterface_startByte2;
    packet->type = packetType_alertOut;
    packet->length = packetLength;
    
    packet->_data[0] = packetType;
    packet->_data[packetLength] = gHostInterface_trailerByte;
    
}

void wifi_SendInt(int value, int type)
{

    hostInterface_packet_t hostInterface_txPacket;

    resetPacket(&hostInterface_txPacket, type, 4);
    hostInterface_txPacket._data[1] = 1;
    hostInterface_txPacket._data[2] = 1;
    hostInterface_txPacket._data[3] = value;
    while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != kStatus_OSA_Success)
    {
        OSA_TimeDelay(5);
    }
}

void wifi_SendSSID(char ssid[32])
{

    int ssidLength = 0;
    int currentLength = 0;
    hostInterface_packet_t hostInterface_txPacket;
    
    ssidLength = strlen(ssid);
    currentLength = ssidLength <= 17 ? ssidLength : 17;
    resetPacket(&hostInterface_txPacket, alertIn_type_wifiSSID, currentLength + 3);

    hostInterface_txPacket._data[1] = 1;
    hostInterface_txPacket._data[2] = ssidLength;

    memcpy( &hostInterface_txPacket._data[3], ssid, currentLength );
    while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != kStatus_OSA_Success)
    {
        OSA_TimeDelay(5);
    }

    if(ssidLength > 17)
    {
        hostInterface_txPacket._data[1] = 2;
        currentLength = ssidLength - currentLength;
        resetPacket(& hostInterface_txPacket, alertIn_type_wifiSSID, currentLength + 2);

        memcpy( &hostInterface_txPacket._data[2], &ssid[17], currentLength );
        while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != kStatus_OSA_Success)
        {
            OSA_TimeDelay(5);
        }
    }
}

wifi_SendSSIDPassword(char password[64])
{
    int ssidPasswordLength = 0;
    int currentLength = 0;
    int currentPosition = 0;
    hostInterface_packet_t hostInterface_txPacket;

    ssidPasswordLength = strlen(password);
    currentLength = ssidPasswordLength <= 17 ? ssidPasswordLength : 17;
    resetPacket(&hostInterface_txPacket, alertIn_type_wifiPass, currentLength + 3);
    hostInterface_txPacket._data[1] = 1;
    hostInterface_txPacket._data[2] = ssidPasswordLength;

    memcpy( &hostInterface_txPacket._data[3], password, currentLength );
    while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != kStatus_OSA_Success)
    {
        OSA_TimeDelay(5);
    }

    currentPosition = currentLength;
    while(currentPosition < ssidPasswordLength)
    {
        currentLength = (ssidPasswordLength - currentPosition <= 18) ? (ssidPasswordLength - currentPosition) : 18;
        resetPacket(& hostInterface_txPacket, alertIn_type_wifiPass, currentLength + 2);
        hostInterface_txPacket._data[1] = 2;

        memcpy( &hostInterface_txPacket._data[2], &password[currentPosition], currentLength );
        while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != kStatus_OSA_Success)
        {
            OSA_TimeDelay(5);
        }
        currentPosition += currentLength;
    }


}

void wifi_SendBluetoothParameters()
{
     if(HEXIWEAR_CONNECTION_FLAGS->toggledConnection >= 0 && HEXIWEAR_CONNECTION_FLAGS->toggledConnection <= 2)
     {
          if(hexiwear_wifiFlags.wifi_auth >= 0 && hexiwear_wifiFlags.wifi_auth <= 2)
          {
              wifi_SendInt(hexiwear_wifiFlags.wifi_auth, alertIn_type_wifiAuth);
          }
          OSA_TimeDelay(200);
          
          if(hexiwear_connectionFlags.socketPosition >= 1 && hexiwear_connectionFlags.socketPosition <= 3)
          {
              wifi_SendInt(hexiwear_connectionFlags.socketPosition, alertIn_type_WiFiClick);
          }
           OSA_TimeDelay(200);

          if(hexiwear_wifiFlags.ssid[0] != 255)
          {
              wifi_SendSSID(hexiwear_wifiFlags.ssid);
          }
          OSA_TimeDelay(200);
          if(hexiwear_wifiFlags.ssid_password[0] != 255)
          {
              wifi_SendSSIDPassword(hexiwear_wifiFlags.ssid_password);
          }
          OSA_TimeDelay(200);
     }
}


//3G Functions
int g3_send_to_cloud (const char* message)
{
    if(connect_server_3g(server_addr, port) != 0)
    {
        OSA_TimeDelay(1000);
        return 1;
    }
    OSA_TimeDelay(1000);
    if(connect_broker_3g(hexiwear_connectionFlags.mqtt_username, hexiwear_connectionFlags.mqtt_password) != 0)
    {
        OSA_TimeDelay(1000);
        return 1;
    }

    OSA_TimeDelay(1000);
    if(publish_broker_3g(message, topic) != 0)
    {
        OSA_TimeDelay(1000);
        return 1;
    }
    OSA_TimeDelay(1000);
    if(disconnect_server_3g() != 0)
    {
        OSA_TimeDelay(1000);
        return 1;
    }

    return 0;
}

void g3_writeG3ToFlash()
{
    if(strlen(g3Flags.g3_name) > 0 && strlen(g3Flags.g3_username) > 0 && strlen(g3Flags.g3_password) > 0)
    {
        HEXIWEAR_SetFlags((uint32_t )HEXIWEAR_G3_FLAG_ADDRESS, (void*)&g3Flags, sizeof(g3Flags));
    }
}

void g3_writeToFlash()
{
    writeConnectionToFlash();
    g3_writeG3ToFlash();
}

void g3_SendG3Param(char param[32], int type)
{
    int paramLength = 0;
    int currentLength = 0;
    hostInterface_packet_t hostInterface_txPacket;

    paramLength = strlen(param);
    currentLength = paramLength <= 17 ? paramLength : 17;
    resetPacket(&hostInterface_txPacket, type, currentLength + 3);

    hostInterface_txPacket._data[1] = 1;
    hostInterface_txPacket._data[2] = paramLength;

    memcpy( &hostInterface_txPacket._data[3], param, currentLength );
    while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != kStatus_OSA_Success)
    {
        OSA_TimeDelay(5);
    }

    if(paramLength > 17)
    {
        hostInterface_txPacket._data[1] = 2;
        currentLength = paramLength - currentLength;
        resetPacket(&hostInterface_txPacket, type, currentLength + 2);

        memcpy( &hostInterface_txPacket._data[2], &param[17], currentLength );
        while(HostInterface_TxQueueMsgPut((hostInterface_packet_t *)&hostInterface_txPacket, true) != kStatus_OSA_Success)
        {
            OSA_TimeDelay(5);
        }
    }
}

void g3_SendBluetoothParameters()
{
    if(HEXIWEAR_CONNECTION_FLAGS->toggledConnection >= 0 && HEXIWEAR_CONNECTION_FLAGS->toggledConnection <= 2)
    {
        if(g3Flags.g3_name[0] != 255)
        {
            g3_SendG3Param(g3Flags.g3_name, alertIn_type_3GName);
        }
        OSA_TimeDelay(200);
        if(g3Flags.g3_username[0] != 255)
        {
            g3_SendG3Param(g3Flags.g3_username, alertIn_type_3GUsername);
        }
        OSA_TimeDelay(200);
        if(g3Flags.g3_password[0] != 255)
        {
            g3_SendG3Param(g3Flags.g3_password, alertIn_type_3GPassword);
        }
        OSA_TimeDelay(200);
    }
}

void g3_setName(char* name)
{
    memset(g3Flags.g3_name, 0, 32);
    strncpy(g3Flags.g3_name, name,32);
    g3_writeG3ToFlash();
}

void g3_setUsername(char* username)
{
    memset(g3Flags.g3_username, 0, 32);
    strncpy(g3Flags.g3_username, username, 32);
    g3_writeG3ToFlash();
}

void g3_setPassword(char* password)
{
    memset(g3Flags.g3_password, 0, 32);
    strncpy(g3Flags.g3_password, password, 32);
    g3_writeG3ToFlash();
}