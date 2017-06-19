/**
 * \file bootloader_driver.c
 * \version 1.00
 * \brief this file contains bootloader app GUI functionality
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

#include "bootloader.h"
#include "bluetooth.h"
#include "screens_common.h"
#include "bootloader_private.h"
#include "flash_boot_kinetis.h"
#include  "power_driver.h"

/** private variables */

MSG_QUEUE_DECLARE( bootloader_queue, BOOTLOADER_QUEUE_SIZE, sizeof(hostInterface_packet_t) );

static msg_queue_handler_t
  bootloader_queueHnd;

static hostInterface_packet_t
  bootloader_dataPacket;

static task_handler_t
  bootloader_handler;

static bootInfo_t
  bootflags = {
                .newBootImageAvailable[ 0 ] = 0x0
              };

static bool
	isBootloaderQueueCreated = false;

// OTAP counter
static uint32_t
  OTAP_TimeoutCounter = 0;

static guiImage_t*
	loadImages[ LOAD_IMG_NUM ] = { &bootloader_loadImg_white, &bootloader_loadImg_blue };

// macros
#define OTAP_DELAY_PERIOD ( ( 5000 ) / 100 )

#define OTAP_Delay() OSA_TimeDelay(100); OTAP_TimeoutCounter--

#define OTAP_HasCounterExpired() ( 0 == OTAP_TimeoutCounter )
#define OTAP_ResetCounter()  /** pxPreviousWakeTime = xTaskGetTickCount(); */ OTAP_TimeoutCounter = OTAP_DELAY_PERIOD

/** declarations */

static void boootloader_Task( task_param_t param );
static bootloader_status_t bootloader_QueueMsgGet( uint32_t timeout );


/** public API */

/**
 * initialize the bootloader app
 * @param param [description]
 */
void bootloader_Init( void* param )
{
  // create the queue
  bootloader_queueHnd = OSA_MsgQCreate(
                                        bootloader_queue,
                                        BOOTLOADER_QUEUE_SIZE,
                                        sizeof(hostInterface_packet_t) / sizeof(uint32_t)
                                      );

  isBootloaderQueueCreated = true;

#if defined( HEXIWEAR_DEBUG )
  vQueueAddToRegistry( bootloader_queueHnd, (char*)"App Bootloader Queue" );
#endif

  if ( NULL == bootloader_queueHnd )
  {
    catch( CATCH_QUEUE );
  }

  /**
   * insert default screen,
   * which will be updated upon user's input
   */

  OTAP_ResetCounter();

  GuiDriver_LabelCreate( &bootloader_labelLoad );

  GuiDriver_ImageAddToScr(&screen_buttonBack);

  // select KW40 by default
  GuiDriver_ImageAddToScr( &bootloader_selectKW40 );

  // register buttons for toggling fitness processes
  GuiDriver_RegisterForNavigation( GUI_NAVIGATION_UP );
  GuiDriver_RegisterForNavigation( GUI_NAVIGATION_DOWN );

  // If bluetooth advertise disabled, prohibit the OTAP mode.
  if(bluetooth_CurrentAdvModeGet() == bluetooth_advMode_enable)
  {
	  GuiDriver_ImageAddToScr(&screen_buttonStart);
	  GuiDriver_RegisterForNavigation( GUI_NAVIGATION_RIGHT );
  }
  else
  {
	  GuiDriver_ImageAddToScr(&screen_buttonStartDisabled);
  }

}

/**
 * put the packet into the designated bootloader's queue
 * @param  packet data to put
 * @return        status flag
 */
bootloader_status_t boootloader_QueueMsgPut ( hostInterface_packet_t* packet )
{
	if ( true == isBootloaderQueueCreated )
	{
	  BaseType_t
		status = xQueueSendToBack( bootloader_queueHnd, (hostInterface_packet_t*)packet, OSA_WAIT_FOREVER );

		if ( pdPASS == status )
		{
		  return BOOTLOADER_STATUS_SUCCESS;
		}

		else
		{
		  catch( CATCH_QUEUE );
		  return BOOTLOADER_STATUS_ERROR;
		}
	}
	else
	{
		catch( CATCH_QUEUE );
		return BOOTLOADER_STATUS_ERROR;
	}
}

/**
 * create the bootloader app task
 * @param param [description]
 */
void bootloader_CreateTasks( void* param )
{
  osa_status_t
    status = OSA_TaskCreate (
                              boootloader_Task,
                              (uint8_t *) "Bootloader task",
                              BOOTLOADER_STACK_SIZE,
                              NULL,
                              BOOTLOADER_PRIO,
                              (task_param_t)0,
                              false,
                              &bootloader_handler
                            );

  if ( kStatus_OSA_Success != status )
  {
    catch( CATCH_INIT );
  }
}

/**
 * destroy the bootloader app task, queue
 * and unregister from listening to touch buttons
 */
void bootloader_DestroyTasks( void* param )
{
  osa_status_t
    status = OSA_TaskDestroy( bootloader_handler );

  if ( kStatus_OSA_Success != status )
  {
    catch( CATCH_INIT );
  }

  OSA_MsgQDestroy( bootloader_queueHnd );

  GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_UP );
  GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_DOWN );
  GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );

  OLED_DestroyDynamicArea();

  GuiDriver_LabelDestroy( &bootloader_labelLoad );

  power_EnablePowerSave();
}

/** private functions */

/**
 * bootloader app task
 * listen for user's input and
 * start the appropriate boot procedure
 *
 * @param param [description]
 */
 static void boootloader_Task ( task_param_t param )
{
	bool_t
		isOtapStarted = false;

	hostInterface_packetType_t
		bootloadTarget = packetType_otapKW40Started;

	hostInterface_packet_t
		bootloaderPacket =
		{
			.start1 = gHostInterface_startByte1,
			.start2 = gHostInterface_startByte2,
			.type   = packetType_otapKW40Started,
			.length = 0
		};
	bootloaderPacket.data[ bootloaderPacket.length ] = gHostInterface_trailerByte;

	GuiDriver_DrawButtonPointers( true, true );

	while (1)
	{
		// wait for the user input
		bootloader_status_t
			status = GuiDriver_QueueMsgGet( &bootloader_dataPacket, OSA_WAIT_FOREVER );

		if ( BOOTLOADER_STATUS_SUCCESS != status )
		{
		  catch( CATCH_QUEUE );
		  continue;
		}

		switch( bootloader_dataPacket.type )
		{
			// select MK64
			case packetType_pressUp:
			{
				/** display the chosen option */
				GuiDriver_ImageDraw( &bootloader_selectMK64 );

				/** save chosen option and designate the packet type */

				bootloaderPacket.type = packetType_otapMK64Started;
				bootloadTarget = packetType_otapMK64Started;
				haptic_Vibrate();
				break;
			}

			// select MKW40
			case packetType_pressDown:
			{
				/** display the chosen option */
				GuiDriver_ImageDraw( &bootloader_selectKW40 );

				/** save chosen option and designate the packet type */

				bootloaderPacket.type = packetType_otapKW40Started;
				bootloadTarget = packetType_otapKW40Started;
				haptic_Vibrate();
				break;
			}

			// start the process
			case packetType_pressRight:
			{
				/**
				* send the OTAP packet
				*/

				isOtapStarted = true;
				haptic_Vibrate();
				break;
			}

			default: {}
		}

		if ( true == isOtapStarted )
		{
			/**
			 * make both of the buttons unavailable during the process,
			 * and gray them out to give the visual feedback
             * disable the power save feature
			 */

            power_DisablePowerSave();

			GuiDriver_RegisterForNavigation( GUI_NAVIGATION_LEFT  );

			GuiDriver_ImageDraw(&screen_buttonStartDisabled);
			GuiDriver_ImageDraw(&screen_buttonBackDisabled);

			GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_UP );
			GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_DOWN );
			GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_RIGHT );

			// send the packet and start to measure for timeout
			HostInterface_TxQueueMsgPut( &bootloaderPacket, true );

			GuiDriver_CleanMainArea();

			uint8_t
				loadImgIdx = 0;

			while (1)
			{
				// start waiting for the new firmware download confirmation
				bootloader_status_t
					bootStatus = bootloader_QueueMsgGet(0);

				if ( BOOTLOADER_STATUS_SUCCESS == bootStatus )
				{
					switch ( bootloader_dataPacket.type )
					{
						case packetType_otapCompleted:
						{
							GuiDriver_ImageDraw( &bootloader_success );
							OLED_DrawBox( 0, 76, 48, 20, 0x0 );

							switch ( bootloadTarget )
							{
								case packetType_otapMK64Started:
								{
									// set the flags in FLASH, announcing that a new image is available
									bootflags.newBootImageAvailable[ 0 ] = 0x1;

									// erase the sector before programming
                                    if  (
                                            INTFLASH_OK != INTFLASH_EraseSector( (uint32_t)BOOT_IMAGE_FLAGS_ADDRESS )
                                        )
                                    {
                                        catch( CATCH_INTERN_FLASH );
                                    }

									if  (
											INTFLASH_OK != INTFLASH_Program(
																				(uint32_t)BOOT_IMAGE_FLAGS_ADDRESS,
																				(uint32_t)&bootflags,
																				sizeof(bootflags)
																			)
										)
									{
										catch( CATCH_INTERN_FLASH );
									}

									// reset the MCU
									OSA_TimeDelay( 3000 );
									HEXIWEAR_ResetMCU();
									break;
								}

								case packetType_otapKW40Started:
								{
									OSA_TimeDelay( 3000 );
									HEXIWEAR_ResetMCU();
									break;
								}

								default: {}
							}
							break;
						}

						case packetType_otapFailed:
						{
							GuiDriver_ImageDraw( &bootloader_failure );
							break;
						}

						default: {}
					}

					// exit the boot-loop and let user go back
                    power_EnablePowerSave();
					GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_LEFT );
					break;
				}

				else
				{
					GuiDriver_ImageDraw( loadImages[ loadImgIdx ] );
					loadImgIdx = ( LOAD_IMG_NUM-1 == loadImgIdx ) ? 0 : loadImgIdx+1;
					OTAP_Delay();
				}
			}

			/** if we got here, either timeout occurred or KW40 finished with the image download for itself */
		}
	}
}

/**
 *    This function gets a message from the head of the designated queue
 *
 *    @param    packet   Pointer to a memory to save the packet.
 *
 *    @return                          kStatus_OSA_Success  Message successfully obtained from the queue.
 *                                     kStatus_OSA_Error    Process fail.
 */

static bootloader_status_t bootloader_QueueMsgGet ( uint32_t timeout )
{
  osa_status_t
    status = OSA_MsgQGet( bootloader_queueHnd, (hostInterface_packet_t*)&bootloader_dataPacket, timeout);

  if ( kStatus_OSA_Success != status )
  {
    catch( CATCH_QUEUE );
    return BOOTLOADER_STATUS_ERROR;
  }
  else
  {
    return BOOTLOADER_STATUS_SUCCESS;
  }
}
