/**
 * GUI notifications functions
 * Project HEXIWEAR, 2015
 */

#include "gui_notifications.h"
#include "gui_notifications_private.h"

static task_handler_t
    gui_notifications_taskHandler;

static void gui_notifications_Task( task_param_t param );

/**
 * [gui_notifications_Init]
 * @param param [description]
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
 * [gui_notifications_CreateTasks]
 * @param param [description]
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
 * [gui_notifications_DestroyTasks]
 * @param param [description]
 */
void gui_notifications_DestroyTasks( void* param )
{
	OSA_TaskDestroy( gui_notifications_taskHandler );
    OLED_DestroyDynamicArea();

    GuiDriver_LabelDestroy( &gui_notifications_labelMail );
    GuiDriver_LabelDestroy( &gui_notifications_labelSms );
    GuiDriver_LabelDestroy( &gui_notifications_labelCall );
}

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
