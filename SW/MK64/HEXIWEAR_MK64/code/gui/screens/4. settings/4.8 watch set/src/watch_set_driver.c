#include "watch_set.h"
#include "watch_set_private.h"
#include "HEXIWEAR_driver.h"
#include "screens_common.h"

#define SETTING_SEGMENT_COUNT 2

task_handler_t watchSet_taskHandler;
hostInterface_packet_t watchSet_dataPacket;
rtc_datetime_t time_toSet;
int8_t segmentSelected;
void watchSet_appTask(task_param_t param);

guiLabel_t settingSegment[SETTING_SEGMENT_COUNT];

void updateSelectedSegmentColors()
{
	settingSegment[0].textProperties.fontColor = ((0 == segmentSelected) ? GUI_COLOR_YELLOW : GUI_COLOR_WHITE);
	settingSegment[1].textProperties.fontColor = ((1 == segmentSelected) ? GUI_COLOR_YELLOW : GUI_COLOR_WHITE);
}

void watchSet_Init( void* param )
{
	settingSegment[0] = gui_hour_label;
	settingSegment[1] = gui_minute_label;

	GuiDriver_RegisterForNavigation(GUI_NAVIGATION_UP);
	GuiDriver_RegisterForNavigation(GUI_NAVIGATION_DOWN);
	GuiDriver_RegisterForNavigation(GUI_NAVIGATION_RIGHT);

	GuiDriver_LabelCreate(&gui_hour_label);
	GuiDriver_LabelCreate(&gui_minute_label);

	RTC_GetCurrentTime(&time_toSet);
	time_toSet.second = 0;

	segmentSelected = 0;
	updateSelectedSegmentColors();

	snprintf( (char*)gui_hour_label.caption, 3, "%02d", time_toSet.hour);
	GuiDriver_LabelAddToScr(&gui_hour_label);

	snprintf( (char*)gui_minute_label.caption, 3, "%02d", time_toSet.minute);
	GuiDriver_LabelAddToScr(&gui_minute_label);
}

void watchSet_CreateTasks( void* param )
{
    osa_status_t taskStatus = OSA_TaskCreate(
    									watchSet_appTask,
                                        (uint8_t*) "watch set task",
										WATCH_SET_STACK_SIZE,
                                        NULL,
										WATCH_SET_PRIO,
                                        (task_param_t)0,
                                        false,
                                        &watchSet_taskHandler
                                    );

    if ( kStatus_OSA_Success != taskStatus )
    {
        catch( CATCH_INIT );
    }
}

void watchSet_DestroyTasks( void* param )
{
	OSA_TaskDestroy( watchSet_taskHandler );
	OLED_DestroyDynamicArea();

	GuiDriver_LabelDestroy( &gui_hour_label );
	GuiDriver_LabelDestroy( &gui_minute_label );

	GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_UP );
	GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_DOWN );
	GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );
}

void watchSet_appTask(task_param_t param)
{

	while (true) {
		gui_status_t clickStatus = GuiDriver_QueueMsgGet( &watchSet_dataPacket , OSA_WAIT_FOREVER );

		if( GUI_STATUS_SUCCESS == clickStatus )
		{
			switch ( watchSet_dataPacket.type )
			{
				case packetType_pressUp:
				{

					segmentSelected++;
					segmentSelected %= 2;
					updateSelectedSegmentColors();
					haptic_Vibrate();
					break;
				}

				case packetType_pressDown:
				{
					switch (segmentSelected)
					{
						case 0: // hour
						{
							time_toSet.hour++;
							time_toSet.hour %= 24;
							GuiDriver_LabelAddToScr(&gui_hour_label);
							break;
						}
						case 1: // minute
						{
							time_toSet.minute++;
							time_toSet.minute %= 60;
							GuiDriver_LabelAddToScr(&gui_minute_label);
							break;
						}
					}
					haptic_Vibrate();
					break;
				}

				case packetType_pressRight:
				{
					RTC_SetCurrentTime(time_toSet);
					haptic_Vibrate();
					break;
				}

				default:
				{
					break;
				}
			}
		}
	}
}
