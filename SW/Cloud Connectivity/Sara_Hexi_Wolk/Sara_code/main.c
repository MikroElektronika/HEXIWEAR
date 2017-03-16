// File: main.c

// Main file which starts the application.

/******************************************************************************
 * Header file inclusions.                                                    *
 ******************************************************************************/

#include "main.h"
#include "3G_Sara.h"
#include "mqtt_wolksense.h"


/******************************************************************************
 * Global variable definitions.                                               *
 ******************************************************************************/

sbit LED1 at PTA_PDOR.B12;
sbit LED2 at PTA_PDOR.B13;
sbit LED3 at PTA_PDOR.B14;

// Start of the dynamic memory heap, necessary for __Lib_MemManager.
const unsigned long HEAP_START = 0x20000000;
// Size of the dynamic memory heap, necessary for __Lib_MemManager.
const unsigned long HEAP_SIZE  = 0x00020000;

/*Put IP address of wolksense.com*/
const char server_addr[] = "52.30.233.2";
const char port[] = "1883";
const char username_mqtt[] = "serial number";
const char password_mqtt[] = "password";
const char topic[] = "sensors/serial number";
const char carrier[] = "Telenor";
const char username[] = "telenor";
const char password[] = "gprs";

/******************************************************************************
 * Global function definitions.                                               *
 ******************************************************************************/


int send_to_cloud (const char * message)
{
  if(connect_server(server_addr, port)!=0)
  {
    OSA_TimeDelay(1000);
    return 1;
  }

  if(connect_broker(username_mqtt, password_mqtt)!=0)
  {
    OSA_TimeDelay(1000);
    disconnect_server();
    return 1;
  }

  if(publish_broker(message, topic)!=0)
  {
    OSA_TimeDelay(1000);
    disconnect_server();
    return 1;
  }

  if(disconnect_server()!=0)
  {
    OSA_TimeDelay(1000);
    return 1;
  }

  return 0;
}

#pragma funcall main sensorTask
void sensorTask( void *pvParameters )
{
  int16_t sensorData[512];
  int8_t tmp8;
  int16_t tmp16;
  volatile int32_t tmp32;
  
  // Initialize variables
  char message_pt1[256] = {0};
  char message_pt2[128] = {0};

  GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_12 ); // PWR_SENSORS_NF
  PTB_PDOR.B12 = 1;
  OSA_TimeDelay( 10 );
  PTB_PDOR.B12 = 0;

  GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_29 ); // PWR_HR
  PTA_PDOR.B29 = 0;
  OSA_TimeDelay( 10 );
  PTA_PDOR.B29 = 1;

  OLED_Init();
  OLED_FillScreen( OLED_COLOR_BLACK );
  OLED_SetFont( guiFont_Tahoma_8_Regular, OLED_COLOR_WHITE, 0 );
  OLED_DrawImage( G3_image, 0, 0 );

  FXAS_Init();
  FXOS_Init();
  HTU_Init();
  MPL_Init();
  //MAXIM_Init();
  TSL_Init();

  G3_Init();

  OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
  OLED_WriteText("Connecting", 20, 80 );

  while (G3_Configure(carrier, username, password)!=0)
  {
               OSA_TimeDelay(1000);
  }
  OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
  OLED_WriteText("Connected ", 20, 80 );

  while (1)
  {
    sprintf(message_pt1,"");
    sprintf(message_pt2,"");
    strcat (message_pt1,"RTC 1485161653;READINGS R:1485161653,");
    HTU_GetTemp( sensorData );
    tmp16 = HTU_TempFormatInt( sensorData[0] );

    if (tmp16>=0)
    {
      sprintf(message_pt1 + strlen(message_pt1), "T:+%d", tmp16/10 );
    } else
    {
      sprintf(message_pt1 + strlen(message_pt1), "T:%d", tmp16/10 );
    }
    
    MPL_ReadRawData( MPL_MODE_PRESSURE, &tmp32 );

    tmp16 = MPL_FormatInt( tmp32 );

    sprintf(message_pt1 + strlen(message_pt1), ",P:+%d", tmp16 );

    HTU_GetHum( sensorData );
    tmp16 = HTU_HumFormatInt( sensorData[0] );
    sprintf(message_pt1 + strlen(message_pt1), ",H:+%d", tmp16/10 );

    TSL_ReadRawData( TSL_CHANNEL_FULL, sensorData );
    TSL_ReadRawData( TSL_CHANNEL_INFRARED, sensorData + 1 );

    TSL_CalculateLux( sensorData, &tmp32 );
    TSL_FormatLux( tmp32, &tmp8 );
    sprintf(message_pt1 + strlen(message_pt1), ",LT:+%d", tmp8*10 );

    FXOS_ReadRawData( sensorData );

    tmp16 = FXOS_AccFormatInt( sensorData[0] );
    if( tmp16 >= 0 )
    {
      sprintf(message_pt1 + strlen(message_pt1), ",ACL:+%02i", tmp16 / 10 );
    }else
    {
      sprintf(message_pt1 + strlen(message_pt1), ",ACL:-%02i", abs( tmp16 / 10 ));
    }

    tmp16 = FXOS_AccFormatInt( sensorData[1] );
    if( tmp16 >= 0 )
    {
      sprintf(message_pt1 + strlen(message_pt1), "+%02i", tmp16 / 10 );
    } else
    {
      sprintf(message_pt1 + strlen(message_pt1), "-%02i", abs( tmp16 / 10 ));
    }

    tmp16 = FXOS_AccFormatInt( sensorData[2] );
    if( tmp16 >= 0 )
    {
      sprintf(message_pt1 + strlen(message_pt1), "+%02i", tmp16 / 10 );
    }else
    {
      sprintf(message_pt1 + strlen(message_pt1), "-%02i", abs( tmp16 / 10 ));
    }
    
    tmp16 = FXOS_MagFormatInt( sensorData[3] );
    if( tmp16 >= 0 )
    {
      sprintf(message_pt1 + strlen(message_pt1), ",MAG:+%02i", tmp16 / 10 );
    }else
    {
      sprintf(message_pt1 + strlen(message_pt1), ",MAG:-%02i", abs( tmp16 / 10 ));
    }

    tmp16 = FXOS_MagFormatInt( sensorData[4] );
    if( tmp16 >= 0 )
    {
      sprintf(message_pt1 + strlen(message_pt1), "+%02i", tmp16 / 10 );
    }else
    {
      sprintf(message_pt1 + strlen(message_pt1), "-%02i", abs( tmp16 / 10 ));
    }

    tmp16 = FXOS_MagFormatInt( sensorData[5] );
    if( tmp16 >= 0 )
    {
      sprintf(message_pt1 + strlen(message_pt1), "+%02i", tmp16 / 10 );
    }else
    {
      sprintf(message_pt1 + strlen(message_pt1), "-%02i", abs( tmp16 / 10 ));
    }

    sprintf(message_pt1 + strlen(message_pt1), ";");
    
    sprintf(message_pt2,"RTC 1485161653;READINGS R:1485161653,");

    FXAS_ReadRawData( sensorData );

    tmp16 = FXAS_FormatInt( sensorData[0] );

    if (tmp16>0)
    {
      sprintf(message_pt2 + strlen(message_pt2), ",GYR:+%i", tmp16 * 10 );
    }else
    {
      sprintf(message_pt2 + strlen(message_pt2), ",GYR:%i", tmp16 * 10 );
    }

    tmp16 = FXAS_FormatInt( sensorData[1] );
    if (tmp16>0)
    {
      sprintf(message_pt2 + strlen(message_pt2), "+%i", tmp16 * 10 );
    }else
    {
      sprintf(message_pt2 + strlen(message_pt2), "%i", tmp16 * 10 );
    }

    tmp16 = FXAS_FormatInt( sensorData[2] );

    if (tmp16>0)
    {
      sprintf(message_pt2 + strlen(message_pt2), "+%i", tmp16 * 10 );
    }else
    {
      sprintf(message_pt2 + strlen(message_pt2), "%i", tmp16 * 10 );
    }

    MAXIM_ReadRawData( sensorData, &tmp8 );

    sprintf(message_pt2 + strlen(message_pt2), ",BPM:+%d", tmp8 );

    sprintf(message_pt2 + strlen(message_pt2),",STP:+0,KCAL:+0;");

    OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
    OLED_WriteText("Sending", 20, 80 );

    if (send_to_cloud (message_pt1)!=0)
    {
      OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
      OLED_WriteText("Error", 12, 80 );
      OSA_TimeDelay(1000);
      continue;
    }

    if (send_to_cloud (message_pt2)!=0)
    {
      OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
      OLED_WriteText("Error", 12, 80 );
      OSA_TimeDelay(1000);
      continue;
    }
        
    OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
    OLED_WriteText("Success", 20, 80 );
    OSA_TimeDelay(1000);
    OLED_DrawBox( 0, 80, 96, 16, OLED_COLOR_BLACK );
    OSA_TimeDelay(10000);
  }
}

// Main function.
void main()
{
    MM_Init();

    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_12 );
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_13 );
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_14 );

    // Task creation.
    xTaskCreate(
                 ( TaskFunction_t ) sensorTask,
                 "SensorTask",
                 configMINIMAL_STACK_SIZE,
                 NULL,
                 10,
                 NULL
               );


    // Starts the scheduler which controls task execution.
    vTaskStartScheduler();

    // Should never reach here.
    while (1) {}
}