/**
 * \file info_driver.c
 * \version 1.00
 * \brief this file contains HEXIWEAR About Screen functionality
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * Neither the name of NXP, nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * visit: http://www.mikroe.com and http://www.nxp.com
 *
 * get support at: http://www.mikroe.com/forum and https://community.nxp.com
 *
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
 * initialize the About screen
 * @param param optional parameter
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
 * initialize the info task
 * @param param optional parameter
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
 * destroy the info task
 * @param param optional parameter
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
 * task charged with displaying
 * HEXIWEAR system information
 * @param param optional parameter
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
