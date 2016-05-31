/**
 * about hexiwear window functionality
 * Project HEXIWEAR, 2015
 */

#include "info.h"
#include "info_private.h"
#include "gui_driver.h"
#include "screens_common.h"
#include "flash_boot_kinetis.h"

static task_handler_t
    info_taskHandler;

static hostInterface_packet_t
  info_dataPacket;

static hexiwear_hw_rev_t
	hexiwear_hwVersion;

static void info_Task( task_param_t param );

 /**
  * [info_Init description]
  * @param param [description]
  */
void info_Init( void* param )
{
	GuiDriver_ImageAddToScr(&screen_buttonBack);

	GuiDriver_LabelCreate(&info_labelTitle);
	GuiDriver_LabelSetCaption(&info_labelTitle, (uint8_t *) "Manufacturer");
	GuiDriver_LabelAddToScr(&info_labelTitle);

	GuiDriver_LabelCreate(&info_labelData);
	GuiDriver_LabelSetCaption(&info_labelData, (uint8_t *) "Mikroelektronika");
	GuiDriver_LabelAddToScr(&info_labelData);

	GuiDriver_LabelCreate(&info_labelData2);
	GuiDriver_LabelSetCaption(&info_labelData2, (uint8_t *) "www.mikroe.com");
	GuiDriver_LabelAddToScr(&info_labelData2);

	 uint8_t
	 	 flashStatus = INTFLASH_ReadHwRev( &hexiwear_hwVersion );

	// register buttons for toggling fitness processes
	GuiDriver_RegisterForNavigation( GUI_NAVIGATION_UP );
	GuiDriver_RegisterForNavigation( GUI_NAVIGATION_DOWN );
}

/**
 * [info_CreateTasks description]
 * @param param [description]
 */
void info_CreateTasks( void* param )
{
	osa_status_t
		taskStatus = OSA_TaskCreate (
										info_Task,
										(uint8_t*) "info window task",
										INFO_STACK_SIZE,
										NULL,
										INFO_PRIO,
										(task_param_t)0,
										false,
										&info_taskHandler
									);

    if ( kStatus_OSA_Success != taskStatus )
    {
        catch( CATCH_INIT );
    }
}

/**
 * [info_DestroyTasks description]
 * @param param [description]
 */
void info_DestroyTasks( void* param )
{
    OSA_TaskDestroy( info_taskHandler );

    OLED_DestroyDynamicArea();

    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_UP );
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_DOWN );

    GuiDriver_LabelDestroy(&info_labelTitle);
    GuiDriver_LabelDestroy(&info_labelData);
}

/**
 * [info_Task description]
 * @param param [description]
 */
static void info_Task( task_param_t param )
{
	uint8_t
		infoScrNum = 0;

	GuiDriver_DrawButtonPointers( true, true );

    while (1)
    {
    	// wait for the user input
		gui_status_t
			status = GuiDriver_QueueMsgGet( &info_dataPacket, OSA_WAIT_FOREVER );

		if ( GUI_STATUS_SUCCESS != status )
		{
		  catch( CATCH_QUEUE );
		  continue;
		}

		switch( info_dataPacket.type )
		{
			case packetType_pressUp:
			{
				infoScrNum = ( (INFO_SCREENS_NUM-1) == infoScrNum ) ?
				    0 :
				    infoScrNum+1;

				haptic_Vibrate();
				break;
			}

			case packetType_pressDown:
			{
				infoScrNum = ( 0 == infoScrNum ) ?
				    (INFO_SCREENS_NUM-1) :
				    infoScrNum-1;

				haptic_Vibrate();
				break;
			}

			default: {}
		}

	    switch ( infoScrNum )
	    {
	        case 0:
	        {
	            GuiDriver_LabelSetCaption   (
	                                            &info_labelTitle,
	                                            (uint8_t *) "Manufacturer"
	                                        );

	            GuiDriver_LabelSetCaption   (
	                                            &info_labelData,
	                                            (uint8_t *) "Mikroelektronika"
	                                        );

	            GuiDriver_CleanAbout();
	    	    GuiDriver_LabelDraw( &info_labelTitle );
	    	    GuiDriver_LabelDraw( &info_labelData  );
	    	    GuiDriver_LabelDraw( &info_labelData2 );
	            break;
	        }

	        case 1:
	        {
	            snprintf(
	                        (char*)info_labelTitle.caption,
	                        14,
	                        (char*) "MK64 FW ver."
	                    );

	            snprintf(
	                        (char*)info_labelData.caption,
	                        18,
	                        (char*) "%u.%u.%u",
	                        HEXIWEAR_VERSION_MAJOR,
	                        HEXIWEAR_VERSION_MINOR,
	                        HEXIWEAR_VERSION_PATCH
	                    );

	    	    GuiDriver_LabelDraw( &info_labelTitle );
	    	    GuiDriver_LabelDraw( &info_labelData  );
	            break;
	        }

	        case 2:
	        {
	            snprintf(
	                        (char*)info_labelTitle.caption,
	                        14,
	                        (char*) "KW40 FW ver."
	                    );

	            snprintf(
	                        (char*)info_labelData.caption,
	                        18,
	                        (char*) "%u.%u.%u",
	                        hexiwear_kw40version.ver_majorNumber,
	                        hexiwear_kw40version.ver_minorNumber,
	                        hexiwear_kw40version.ver_patchNumber
	                    );

	    	    GuiDriver_LabelDraw( &info_labelTitle );
	    	    GuiDriver_LabelDraw( &info_labelData  );
	            break;
	        }

	        case 3:
	        {
	            snprintf(
	                        (char*)info_labelTitle.caption,
	                        14,
	                        (char*) "HW ver."
	                    );

	            snprintf(
	                        (char*)info_labelData.caption,
	                        18,
	                        (char*) "%u.%u.%u",
							hexiwear_hwVersion.hexiwear_major_ver,
							hexiwear_hwVersion.hexiwear_minor_ver,
							hexiwear_hwVersion.hexiwear_patch_ver
	                    );

	            GuiDriver_CleanAbout();
	    	    GuiDriver_LabelDraw( &info_labelTitle );
	    	    GuiDriver_LabelDraw( &info_labelData  );
	    	    GuiDriver_LabelDraw( &info_labelData2 );
	            break;
	        }

	        case 4:
	        {
	        	GuiDriver_CleanAbout();
	            GuiDriver_ImageDraw( &about_qrHexiwearIcon );
	            break;
	        }

	        default: {}
	    }

    }
}
