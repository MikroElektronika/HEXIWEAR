#include "apps.h"

#define TEXT_START (75)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * declarations
 */

static void sensorTag_Init( void *param );
static void sensorTag_Callback( void *param );
static void sensorTag_App( task_param_t param );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * screens
 */
const menuItem_t
  sensorTag_item =  {
                      .navigation = {
                                      .enter  = NULL,
                                      .back   = &watch_item,
                                      .up     = NULL,
                                      .down   = NULL,
                                      .left   = NULL,
                                      .right  = NULL,
                                    },

                      .image = sensorTag_bmp,

                      .initFunction     = sensorTag_Init,
                      .callbackFunction = sensorTag_Callback,
                    };

task_handler_t
  sensorTag_handler;

static hostInterface_packet_t
  dataPacket;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * functions
 */

/**
 * [sensorTag_Init description]
 * @param param [description]
 */
static void sensorTag_Init( void *param )
{
  osa_status_t
    status = OSA_TaskCreate (
                              sensorTag_App,
                              (uint8_t*)"Sensor Tag App",
                              SENSOR_TAG_STACK_SIZE,
                              NULL,
                              SENSOR_TAG_PRIO,
                              (task_param_t)0,
                              false,
                              &sensorTag_handler
                            );


  if ( kStatus_OSA_Success != status )
  {
    catch( CATCH_INIT );
  }
}

/**
 * [sensorTag_Callback description]
 * @param param [description]
 */
static void sensorTag_Callback( void *param )
{}

/**
 * [sensorTag_App  description]
 * @param param [description]
 */
static void sensorTag_App (
                            task_param_t param
                          )
{
//  OLED_SetFont  ( menuFont_Tahoma11x13_Regular, MENU_COLOR_YELLOW );
//  OLED_WriteText( "SENSOR TAG",  15,  5, OLED_CHAR_WIDTH_AUTO, OLED_CHAR_HEIGHT_AUTO, OLED_TEXT_ALIGN_NONE );
//  OLED_WriteText( "Temperature:", 5, 30, OLED_CHAR_WIDTH_AUTO, OLED_CHAR_HEIGHT_AUTO, OLED_TEXT_ALIGN_NONE );
//  OLED_WriteText( "Humidity:",    5, 45, OLED_CHAR_WIDTH_AUTO, OLED_CHAR_HEIGHT_AUTO, OLED_TEXT_ALIGN_NONE );
//  OLED_WriteText( "Pressure:",    5, 60, OLED_CHAR_WIDTH_AUTO, OLED_CHAR_HEIGHT_AUTO, OLED_TEXT_ALIGN_NONE );

  mE_t
    sensorValue;

  uint8_t
    ValToScr[8];

  /**
   * run sensors
   */

  /**
   * update sensor push flags
   */

  sensor_pushTarget_t
    targets;

  targets = sensor_GetPushTargets( SENSOR_PACKET_TEMP );
  sensor_SetPushTargets( SENSOR_PACKET_TEMP, targets | SENSOR_PUSH_OLED );

  targets = sensor_GetPushTargets( SENSOR_PACKET_HUM );
  sensor_SetPushTargets( SENSOR_PACKET_HUM, targets | SENSOR_PUSH_OLED );

  targets = sensor_GetPushTargets( SENSOR_PACKET_PRES );
  sensor_SetPushTargets( SENSOR_PACKET_PRES, targets | SENSOR_PUSH_OLED );

  targets = sensor_GetPushTargets( SENSOR_PACKET_BAT );
  sensor_SetPushTargets( SENSOR_PACKET_BAT, targets | SENSOR_PUSH_OLED );

  /**
   * wait for data to display
   */

  while (1)
  {
    osa_status_t
      status = MenuDriver_QueueMsgGet( &dataPacket , 0 );

    /**
     * extract the data
     */

    sensorValue = (mE_t)( dataPacket.data[0] | (mE_t)dataPacket.data[1] << 8 );

    /**
     * update screen data
     */

    if ( kStatus_OSA_Success == status )
    {
      switch ( dataPacket.type )
      {
        // Battery Service
        case packetType_batteryLevel: { break; }

        // Motion Service
        case packetType_accel:        { break; }

        case packetType_gyro:         { break; }

        case packetType_magnet:       { break; }

        /**
         * Weather Service
         */

        case packetType_temperature:  {
                                        sensorValue /= 100;
                                        snprintf( (char*)ValToScr, ArraySize( ValToScr ), "%i", sensorValue );
//                                        OLED_WriteText( ValToScr, TEXT_START, 30, OLED_CHAR_WIDTH_NUM, OLED_CHAR_HEIGHT_AUTO, OLED_TEXT_ALIGN_NONE );
                                        break;
                                      }

        case packetType_humidity:     {
                                        sensorValue /= 100;
                                        snprintf( (char*)ValToScr, ArraySize( ValToScr ), "%i", sensorValue );
//                                        OLED_WriteText( ValToScr, TEXT_START, 45, OLED_CHAR_WIDTH_NUM, OLED_CHAR_HEIGHT_AUTO, OLED_TEXT_ALIGN_NONE );
                                        break;
                                      }

        case packetType_pressure:     {
                                        sensorValue /= 100;
                                        snprintf( (char*)ValToScr, ArraySize( ValToScr ), "%i", sensorValue );
//                                        OLED_WriteText( ValToScr, TEXT_START, 60, OLED_CHAR_WIDTH_NUM, OLED_CHAR_HEIGHT_AUTO, OLED_TEXT_ALIGN_NONE );
                                        break;
                                      }

        case packetType_ambiLight:    { break; }


        // Health Service
        case packetType_heartRate:    { break; }

        case packetType_steps:        { break; }
        case packetType_activityTime: { break; }


        // Alert Service
        case packetType_alertIn:      { break; }
        case packetType_alertOut:     { break; }

        default: {}
      }
    }
  }
}
