/**
 * \file gui_notifications_driver.c
 * \version 1.00
 * \brief this file contains notifications GUI related functionality
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

#include "gui_notifications.h"
#include "gui_notifications_private.h"

static task_handler_t
    gui_notifications_taskHandler;

static void gui_notifications_Task( task_param_t param );

/**
 * notifications task initialization
 * @param param optional parameter
 */
void gui_notifications_Init( void* param )
{
    GuiDriver_LabelCreate( &gui_notifications_labelMail );
    GuiDriver_LabelCreate( &gui_notifications_labelSms );
    GuiDriver_LabelCreate( &gui_notifications_labelCall );

    uint8_t
        mailNotifCnt = Notification_GetUnreadCounter( NOTIF_TYPE_MAIL );

    if ( 0 != mailNotifCnt )
    {
       gui_notifications_mailIcon.img = gui_notifications_mail_blue_bmp;
    }
    else
    {
	   gui_notifications_mailIcon.img = gui_notifications_mail_white_bmp;
    }
    GuiDriver_ImageAddToScr( &gui_notifications_mailIcon );

    snprintf( (char*)gui_notifications_labelMail.caption, 4, "%i", mailNotifCnt );
    GuiDriver_LabelAddToScr( &gui_notifications_labelMail );

    uint8_t
        smsNotifCnt = Notification_GetUnreadCounter( NOTIF_TYPE_SMS );

    if ( 0 != smsNotifCnt )
    {
       gui_notifications_smsIcon.img = gui_notifications_sms_blue_bmp;
    }
    else
    {
       gui_notifications_smsIcon.img = gui_notifications_sms_white_bmp;
    }
    GuiDriver_ImageAddToScr( &gui_notifications_smsIcon );

    snprintf( (char*)gui_notifications_labelSms.caption, 4, "%i", smsNotifCnt );
    GuiDriver_LabelAddToScr( &gui_notifications_labelSms );

    uint8_t
        callNotifCnt = Notification_GetUnreadCounter( NOTIF_TYPE_CALL );

    if ( 0 != callNotifCnt )
    {
       gui_notifications_callIcon.img = gui_notifications_call_blue_bmp;
    }
    else
    {
       gui_notifications_callIcon.img = gui_notifications_call_white_bmp;
    }
    GuiDriver_ImageAddToScr( &gui_notifications_callIcon );

    snprintf( (char*)gui_notifications_labelCall.caption, 4, "%i", callNotifCnt );
    GuiDriver_LabelAddToScr( &gui_notifications_labelCall );
}

/**
* create the notification task
* @param param optional parameter
 */
void gui_notifications_CreateTasks( void* param )
{
/*	osa_status_t
		taskStatus = */OSA_TaskCreate (
										gui_notifications_Task,
										(uint8_t*) "notifications window",
										GUI_NOTIFICATIONS_STACK_SIZE,
										NULL,
										GUI_NOTIFICATIONS_PRIO,
										(task_param_t)0,
										false,
										&gui_notifications_taskHandler
									);
}

/**
* destroy the notification task
* @param param optional parameter
 */
void gui_notifications_DestroyTasks( void* param )
{
	OSA_TaskDestroy( gui_notifications_taskHandler );
    OLED_DestroyDynamicArea();

    GuiDriver_LabelDestroy( &gui_notifications_labelMail );
    GuiDriver_LabelDestroy( &gui_notifications_labelSms );
    GuiDriver_LabelDestroy( &gui_notifications_labelCall );
}

/**
 * notification task
 * wait for the appropriate event, modify
 * appropriate counters, update appropriate
 * labels
 * @param param optional parameter
 */
static void gui_notifications_Task( task_param_t param )
{
	notification_type_t
		notifType;

    while (1)
    {
		notification_status_t
			eventStatus = Notification_WaitForEvent( &notifType, OSA_WAIT_FOREVER );

		if( NOTIF_STATUS_SUCCESS == eventStatus )
		{
			switch ( notifType )
			{
				case NOTIF_TYPE_CALL:
				{
				    uint8_t
				        callNotifCnt = Notification_GetUnreadCounter( NOTIF_TYPE_CALL );

				    if ( 0 != callNotifCnt )
				    {
				       gui_notifications_callIcon.img = gui_notifications_call_blue_bmp;
				    }
				    else
				    {
				       gui_notifications_callIcon.img = gui_notifications_call_white_bmp;
				    }
				    GuiDriver_ImageDraw( &gui_notifications_callIcon );

				    snprintf( (char*)gui_notifications_labelCall.caption, 4, "%i", callNotifCnt );
				    GuiDriver_LabelDraw( &gui_notifications_labelCall );
					break;
				}

				case NOTIF_TYPE_MAIL:
				{
				    uint8_t
				        mailNotifCnt = Notification_GetUnreadCounter( NOTIF_TYPE_MAIL );

				    if ( 0 != mailNotifCnt )
				    {
				       gui_notifications_mailIcon.img = gui_notifications_mail_blue_bmp;
				    }
				    else
				    {
					   gui_notifications_mailIcon.img = gui_notifications_mail_white_bmp;
				    }
				    GuiDriver_ImageDraw( &gui_notifications_mailIcon );

				    snprintf( (char*)gui_notifications_labelMail.caption, 4, "%i", mailNotifCnt );
				    GuiDriver_LabelDraw( &gui_notifications_labelMail );
					break;
				}

				case NOTIF_TYPE_SMS:
				{
				    uint8_t
				        smsNotifCnt = Notification_GetUnreadCounter( NOTIF_TYPE_SMS );

				    if ( 0 != smsNotifCnt )
				    {
				       gui_notifications_smsIcon.img = gui_notifications_sms_blue_bmp;
				    }
				    else
				    {
				       gui_notifications_smsIcon.img = gui_notifications_sms_white_bmp;
				    }
				    GuiDriver_ImageDraw( &gui_notifications_smsIcon );

				    snprintf( (char*)gui_notifications_labelSms.caption, 4, "%i", smsNotifCnt );
				    GuiDriver_LabelDraw( &gui_notifications_labelSms );
					break;
				}
			}
		}
    }
}
