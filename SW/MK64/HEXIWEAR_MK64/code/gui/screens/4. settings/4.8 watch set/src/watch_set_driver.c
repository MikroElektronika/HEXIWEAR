#include "watch_set.h"
#include "watch_set_private.h"
#include "HEXIWEAR_driver.h"
#include "screens_common.h"

#define SETTING_SEGMENT_COUNT 5

// define private variables
static task_handler_t watchSet_taskHandler;
static hostInterface_packet_t watchSet_dataPacket;
static rtc_datetime_t time_toSet;
static int8_t segmentSelected;

static guiLabel_t* settingSegment[SETTING_SEGMENT_COUNT];

// declare private functions
static void watchSet_appTask(task_param_t param);
static void updateSelectedSegmentColors();
static void registerNavigationKeys();
static void unregisterNavigationKeys();
static void initSettingSegments();
static void drawSettingSegments();
static void createGuiElements();
static void destroyGuiElements();
static bool isLeapYear(uint16_t year);
static uint8_t getDaysInMonth(rtc_datetime_t dateTime);
static void correctLeapDay();

static void updateSelectedSegmentColors()
{
	for (int i = 0; i < SETTING_SEGMENT_COUNT; i++)
	{
		settingSegment[i]->textProperties.fontColor = (i == segmentSelected ?  GUI_COLOR_YELLOW : GUI_COLOR_WHITE);
	}
}

static void registerNavigationKeys()
{
	GuiDriver_RegisterForNavigation(GUI_NAVIGATION_UP);
	GuiDriver_RegisterForNavigation(GUI_NAVIGATION_DOWN);
	GuiDriver_RegisterForNavigation(GUI_NAVIGATION_RIGHT);
}

static void unregisterNavigationKeys()
{
	GuiDriver_UnregisterFromNavigation(GUI_NAVIGATION_UP);
	GuiDriver_UnregisterFromNavigation(GUI_NAVIGATION_DOWN);
	GuiDriver_UnregisterFromNavigation(GUI_NAVIGATION_RIGHT);
}

static void initSettingSegments()
{
	settingSegment[0] = &gui_year_label;
	settingSegment[1] = &gui_month_label;
	settingSegment[2] = &gui_day_label;
	settingSegment[3] = &gui_hour_label;
	settingSegment[4] = &gui_minute_label;
	segmentSelected = 0;
}

static void drawSettingSegments()
{
	GuiDriver_LabelDraw(&gui_year_label);
	GuiDriver_LabelDraw(&gui_month_label);
	GuiDriver_LabelDraw(&gui_day_label);
	GuiDriver_LabelDraw(&gui_hour_label);
	GuiDriver_LabelDraw(&gui_minute_label);
}

static void createGuiElements()
{
	GuiDriver_LabelCreate(&gui_year_label);
	GuiDriver_LabelCreate(&gui_month_label);
	GuiDriver_LabelCreate(&gui_day_label);
	GuiDriver_LabelCreate(&gui_time_colon_label);
	GuiDriver_LabelCreate(&gui_hour_label);
	GuiDriver_LabelCreate(&gui_minute_label);
}

static void destroyGuiElements()
{
	GuiDriver_LabelDestroy(&gui_year_label);
	GuiDriver_LabelDestroy(&gui_month_label);
	GuiDriver_LabelDestroy(&gui_day_label);
	GuiDriver_LabelDestroy(&gui_time_colon_label);
	GuiDriver_LabelDestroy(&gui_hour_label);
	GuiDriver_LabelDestroy(&gui_minute_label);;
}

static bool isLeapYear(uint16_t year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static uint8_t getDaysInMonth(rtc_datetime_t dateTime)
{
	return daysInMonth[dateTime.month - 1] + (dateTime.month == 2 ? (uint8_t)isLeapYear(dateTime.year) : 0);
}

static void correctLeapDay()
{
	if (time_toSet.day > getDaysInMonth(time_toSet))
	{
		time_toSet.day = getDaysInMonth(time_toSet);
		snprintf( (char*)gui_day_label.caption, 4, "%02d.", time_toSet.day);
		GuiDriver_LabelDraw(&gui_day_label);
	}
}

void watchSet_Init( void* param )
{
	registerNavigationKeys();
	initSettingSegments();
	updateSelectedSegmentColors();
	createGuiElements();

	RTC_GetCurrentTime(&time_toSet);
	time_toSet.second = 0;

	snprintf( (char*)gui_year_label.caption, 6, "%04d.", time_toSet.year);
	GuiDriver_LabelAddToScr(&gui_year_label);

	const char *monthsOfYearPtr;
	monthsOfYearPtr = monthsOfYearStr[time_toSet.month - 1];
	snprintf( (char*)gui_month_label.caption, 4, "%s", monthsOfYearPtr);
	GuiDriver_LabelAddToScr(&gui_month_label);

	snprintf( (char*)gui_day_label.caption, 4, "%02d.", time_toSet.day);
	GuiDriver_LabelDraw(&gui_day_label);

	snprintf( (char*)gui_hour_label.caption, 3, "%02d", time_toSet.hour);
	GuiDriver_LabelAddToScr(&gui_hour_label);

	snprintf( (char*)gui_time_colon_label.caption, 2, ":");
	GuiDriver_LabelAddToScr(&gui_time_colon_label);

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
	destroyGuiElements();
	unregisterNavigationKeys();
}

static void updateAfterSelectionChange()
{
	updateSelectedSegmentColors();
	drawSettingSegments();
	haptic_Vibrate();
}

static void watchSet_appTask(task_param_t param)
{
	while (true)
	{
		gui_status_t clickStatus = GuiDriver_QueueMsgGet( &watchSet_dataPacket , OSA_WAIT_FOREVER );

		if( GUI_STATUS_SUCCESS == clickStatus )
		{
			switch ( watchSet_dataPacket.type )
			{
				case packetType_pressUp:
				{
					segmentSelected++;
					segmentSelected %= SETTING_SEGMENT_COUNT;
					updateAfterSelectionChange();
					break;
				}

				case packetType_pressDown:
				{
					switch (segmentSelected)
					{
						case 0: // year
						{
							time_toSet.year++;
							if (time_toSet.year > 2099) time_toSet.year = 1970;
							snprintf( (char*)gui_year_label.caption, 6, "%04d.", time_toSet.year);
							GuiDriver_LabelDraw(&gui_year_label);
							correctLeapDay();
							break;
						}
						case 1: // month
						{
							time_toSet.month++;
							if (time_toSet.month > 12) time_toSet.month = 1;
							const char *monthsOfYearPtr;
							monthsOfYearPtr = monthsOfYearStr[time_toSet.month - 1];
							snprintf( (char*)gui_month_label.caption, 4, "%s", monthsOfYearPtr);
							GuiDriver_LabelDraw(&gui_month_label);
							correctLeapDay();
							break;
						}
						case 2: // day
						{
							time_toSet.day++;
							if (time_toSet.day > getDaysInMonth(time_toSet)) time_toSet.day = 1;
							snprintf( (char*)gui_day_label.caption, 4, "%02d.", time_toSet.day);
							GuiDriver_LabelDraw(&gui_day_label);
							break;
						}
						case 3: // hour
						{
							time_toSet.hour++;
							time_toSet.hour %= 24;
							snprintf( (char*)gui_hour_label.caption, 3, "%02d", time_toSet.hour);
							GuiDriver_LabelDraw(&gui_hour_label);
							break;
						}
						case 4: // minute
						{
							time_toSet.minute++;
							time_toSet.minute %= 60;
							snprintf( (char*)gui_minute_label.caption, 3, "%02d", time_toSet.minute);
							GuiDriver_LabelDraw(&gui_minute_label);
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
