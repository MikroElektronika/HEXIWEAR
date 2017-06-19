// File: gui_notifications_driver.c

// Definitions of main functionalities in the notifications gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "gui_notifications.h"
#include "gui_notifications_private.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static task_handler_t gui_notifications_taskHandler;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Gui notifications task.
// Waits for the appropriate event, modifies appropriate counters,
// updates appropriate labels.
static void gui_notifications_Task( task_param_t param )
{
    notification_type_t notifType;

    while( 1 )
    {
        notification_status_t eventStatus
            = Notification_WaitForEvent( &notifType, OSA_WAIT_FOREVER );

        if( eventStatus == NOTIF_STATUS_SUCCESS )
        {
            switch( notifType )
            {
                case NOTIF_TYPE_CALL:
                {
                    uint8_t callNotifCnt =
                        Notification_GetUnreadCounter( NOTIF_TYPE_CALL );

                    if( callNotifCnt != 0 )
                    {
                        gui_notifications_callIcon.img =
                            gui_notifications_call_blue_bmp;
                    }
                    else
                    {
                        gui_notifications_callIcon.img =
                            gui_notifications_call_white_bmp;
                    }
                    GuiDriver_ImageDraw( &gui_notifications_callIcon );

                    sprintf( ( char* )gui_notifications_labelCall.caption,
                        "%i", callNotifCnt ); // 4,
                    GuiDriver_LabelDraw( &gui_notifications_labelCall );
                    break;
                }

                case NOTIF_TYPE_MAIL:
                {
                    uint8_t mailNotifCnt =
                        Notification_GetUnreadCounter( NOTIF_TYPE_MAIL );

                    if( 0 != mailNotifCnt )
                    {
                        gui_notifications_mailIcon.img =
                            gui_notifications_mail_blue_bmp;
                    }
                    else
                    {
                        gui_notifications_mailIcon.img =
                            gui_notifications_mail_white_bmp;
                    }
                    GuiDriver_ImageDraw( &gui_notifications_mailIcon );

                    sprintf( ( char* )gui_notifications_labelMail.caption,
                        "%i", mailNotifCnt ); // 4,
                    GuiDriver_LabelDraw( &gui_notifications_labelMail );
                    break;
                }

                case NOTIF_TYPE_SMS:
                {
                    uint8_t smsNotifCnt =
                        Notification_GetUnreadCounter( NOTIF_TYPE_SMS );

                    if( 0 != smsNotifCnt )
                    {
                        gui_notifications_smsIcon.img =
                            gui_notifications_sms_blue_bmp;
                    }
                    else
                    {
                        gui_notifications_smsIcon.img =
                            gui_notifications_sms_white_bmp;
                    }
                    GuiDriver_ImageDraw( &gui_notifications_smsIcon );

                    sprintf( ( char* )gui_notifications_labelSms.caption,
                        "%i", smsNotifCnt ); // 4,
                    GuiDriver_LabelDraw( &gui_notifications_labelSms );
                    break;
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises gui notifications module.
void gui_notifications_Init( void* param )
{
    uint8_t mailNotifCnt;
    uint8_t smsNotifCnt;
    uint8_t callNotifCnt;

    GuiDriver_LabelCreate( &gui_notifications_labelMail );
    GuiDriver_LabelCreate( &gui_notifications_labelSms );
    GuiDriver_LabelCreate( &gui_notifications_labelCall );

    mailNotifCnt = Notification_GetUnreadCounter( NOTIF_TYPE_MAIL );

    if( mailNotifCnt != 0 )
    {
        gui_notifications_mailIcon.img = gui_notifications_mail_blue_bmp;
    }
    else
    {
        gui_notifications_mailIcon.img = gui_notifications_mail_white_bmp;
    }
    GuiDriver_ImageAddToScr( &gui_notifications_mailIcon );

    sprintf( ( char* )gui_notifications_labelMail.caption,
        "%i", mailNotifCnt ); // 4,
    GuiDriver_LabelAddToScr( &gui_notifications_labelMail );
    
    smsNotifCnt = Notification_GetUnreadCounter( NOTIF_TYPE_SMS );

    if( smsNotifCnt != 0 )
    {
        gui_notifications_smsIcon.img = gui_notifications_sms_blue_bmp;
    }
    else
    {
        gui_notifications_smsIcon.img = gui_notifications_sms_white_bmp;
    }
    GuiDriver_ImageAddToScr( &gui_notifications_smsIcon );

    sprintf( ( char* )gui_notifications_labelSms.caption,
        "%i", smsNotifCnt ); // 4,
    GuiDriver_LabelAddToScr( &gui_notifications_labelSms );

    callNotifCnt = Notification_GetUnreadCounter( NOTIF_TYPE_CALL );

    if( callNotifCnt != 0 )
    {
        gui_notifications_callIcon.img = gui_notifications_call_blue_bmp;
    }
    else
    {
        gui_notifications_callIcon.img = gui_notifications_call_white_bmp;
    }
    GuiDriver_ImageAddToScr( &gui_notifications_callIcon );

    sprintf( ( char* )gui_notifications_labelCall.caption,
        "%i", callNotifCnt ); // 4,
    GuiDriver_LabelAddToScr( &gui_notifications_labelCall );
}

// Creates the gui notifications tasks.
void gui_notifications_CreateTasks( void* param )
{
    OSA_TaskCreate(
                    gui_notifications_Task,
                    ( uint8_t* )"notifications window",
                    GUI_NOTIFICATIONS_STACK_SIZE,
                    NULL,
                    GUI_NOTIFICATIONS_PRIO,
                    ( task_param_t )0,
                    false,
                    &gui_notifications_taskHandler
                  );
}

// Destroys the gui notifications tasks.
void gui_notifications_DestroyTasks( void* param )
{
    OSA_TaskDestroy( gui_notifications_taskHandler );
    OLED_DestroyDynamicArea();

    GuiDriver_LabelDestroy( &gui_notifications_labelMail );
    GuiDriver_LabelDestroy( &gui_notifications_labelSms );
    GuiDriver_LabelDestroy( &gui_notifications_labelCall );
}