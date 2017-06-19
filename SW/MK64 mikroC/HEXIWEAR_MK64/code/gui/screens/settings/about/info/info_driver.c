// File: info_driver.c

// Definitions of main functionalities in the info gui module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "settings/about/info/info.h"
#include "settings/about/info/info_private.h"
#include "gui_driver.h"
#include "screens_common.h"
#include "error.h"
#include "HEXIWEAR_defs.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static task_handler_t info_taskHandler;

static hostInterface_packet_t info_dataPacket;

static hexiwear_hw_rev_t hexiwear_hwVersion;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Task charged with displaying HEXIWEAR system information.
static void info_Task( task_param_t param )
{
    uint8_t infoScrNum = 0;

    GuiDriver_DrawButtonPointers( true, true );

    while( 1 )
    {
        // wait for the user input
        gui_status_t status =
            GuiDriver_QueueMsgGet( &info_dataPacket, OSA_WAIT_FOREVER );

        if( status != GUI_STATUS_SUCCESS )
        {
            error_catch( CATCH_QUEUE );
            continue;
        }

        switch( info_dataPacket.type )
        {
            case packetType_pressUp:
            {
                infoScrNum = ( infoScrNum == ( INFO_SCREENS_NUM - 1 ) ) ?
                             0 :
                             infoScrNum + 1;

                haptic_Vibrate();
                break;
            }

            case packetType_pressDown:
            {
                infoScrNum = ( infoScrNum == 0 ) ?
                             ( INFO_SCREENS_NUM - 1 ) :
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
                GuiDriver_LabelSetCaption( &info_labelTitle,
                    ( uint8_t* )"Manufacturer" );

                GuiDriver_LabelSetCaption( &info_labelData,
                    ( uint8_t* )"Mikroelektronika" );

                GuiDriver_CleanAbout();
                GuiDriver_LabelDraw( &info_labelTitle );
                GuiDriver_LabelDraw( &info_labelData  );
                GuiDriver_LabelDraw( &info_labelData2 );
                break;
            }

            case 1:
            {
                sprintf( ( uint8_t* )info_labelTitle.caption, // 14,
                    ( uint8_t* )"MK64 FW ver." );

                sprintf( ( uint8_t* )info_labelData.caption, // 18,
                    ( uint8_t* )"%u.%u.%u", HEXIWEAR_VERSION_MAJOR,
                    HEXIWEAR_VERSION_MINOR, HEXIWEAR_VERSION_PATCH );

                GuiDriver_LabelDraw( &info_labelTitle );
                GuiDriver_LabelDraw( &info_labelData  );
                break;
            }

            case 2:
            {
                sprintf( ( uint8_t* )info_labelTitle.caption, // 14,
                    ( uint8_t* )"KW40 FW ver." );

                sprintf( ( uint8_t* )info_labelData.caption, // 18,
                    ( uint8_t* )"%u.%u.%u",
                    hexiwear_kw40version.ver_majorNumber,
                    hexiwear_kw40version.ver_minorNumber,
                    hexiwear_kw40version.ver_patchNumber );

                GuiDriver_LabelDraw( &info_labelTitle );
                GuiDriver_LabelDraw( &info_labelData  );
                break;
            }

            case 3:
            {
                sprintf( ( uint8_t* )info_labelTitle.caption, // 14,
                    ( uint8_t* )"HW ver." );

                sprintf( ( uint8_t* )info_labelData.caption, // 18,
                    ( uint8_t* )"%u.%u.%u",
                    hexiwear_hwVersion.hexiwear_major_ver,
                    hexiwear_hwVersion.hexiwear_minor_ver,
                    hexiwear_hwVersion.hexiwear_patch_ver );

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

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the About screen.
void info_Init( void* param )
{
    uint8_t buf[8];

    GuiDriver_ImageAddToScr( &screen_buttonBack );

    GuiDriver_LabelCreate( &info_labelTitle );
    GuiDriver_LabelSetCaption( &info_labelTitle, ( uint8_t* )"Manufacturer" );
    GuiDriver_LabelAddToScr( &info_labelTitle );

    GuiDriver_LabelCreate( &info_labelData );
    GuiDriver_LabelSetCaption(
        &info_labelData, ( uint8_t* )"Mikroelektronika" );
    GuiDriver_LabelAddToScr(&info_labelData);

    GuiDriver_LabelCreate( &info_labelData2 );
    GuiDriver_LabelSetCaption( &info_labelData2, ( uint8_t* )"www.mikroe.com" );
    GuiDriver_LabelAddToScr( &info_labelData2 );

    Flash_ReadOnce( 0, buf );
    
    hexiwear_hwVersion.hexiwear_major_ver = buf[0];
    hexiwear_hwVersion.hexiwear_minor_ver = buf[1];
    hexiwear_hwVersion.hexiwear_patch_ver = buf[2];
    hexiwear_hwVersion.hexiwear_build_ver = buf[3];

    hexiwear_hwVersion.pcb_main_ver       = buf[4];
    hexiwear_hwVersion.pcb_hr_ver         = buf[5];
    hexiwear_hwVersion.pcb_cs_ver         = buf[6];
    hexiwear_hwVersion.padding            = buf[7];

    // register buttons
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_UP );
    GuiDriver_RegisterForNavigation( GUI_NAVIGATION_DOWN );
}

// Initialises the info task.
void info_CreateTasks( void* param )
{
    osa_status_t taskStatus = OSA_TaskCreate(
                                              info_Task,
                                              ( uint8_t* )"info window task",
                                              INFO_STACK_SIZE,
                                              NULL,
                                              INFO_PRIO,
                                              ( task_param_t )0,
                                              false,
                                              &info_taskHandler
                                            );

    if( taskStatus != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
    }
}

// Destroys the info task.
void info_DestroyTasks( void* param )
{
    OSA_TaskDestroy( info_taskHandler );

    OLED_DestroyDynamicArea();

    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_UP );
    GuiDriver_UnregisterFromNavigation( GUI_NAVIGATION_DOWN );

    GuiDriver_LabelDestroy( &info_labelTitle );
    GuiDriver_LabelDestroy( &info_labelData );
    GuiDriver_LabelDestroy( &info_labelData2 );
}