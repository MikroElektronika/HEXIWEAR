// File: HEXIWEAR_driver.c

// Definitions of main functionalities in the HEXIWEAR module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "HEXIWEAR_driver.h"
#include "HEXIWEAR_defs.h"
#include "HEXIWEAR_info.h"

#include "sensor_driver.h"
#include "sensor_defs.h"
#include "sensor_types.h"

#include "timer_driver.h"

#include "power_driver.h"

#include "gui_notifications/gui_notifications.h"
#include "apps/flashlight/flashlight.h"

#include "host_mcu_interface.h"
#include "gui_driver.h"

#include "rtc_driver.h"

#include "power_manager.h"

#include "error.h"
#include "error_types.h"

#include "screens_common.h"

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static packet_pushTarget_t *HEXIWEAR_currentBackupList = NULL;

static packet_pushTarget_t HEXIWEAR_currentApp = PACKET_PUSH_NONE;

static event_t HEXIWEAR_versionEvent;

static event_flags_t HEXIWEAR_eventFlag  = 1;

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Hexiwear startup task.
void HEXIWEAR_startup( task_param_t param )
{
    uint8_t status = 0;
    
    power_ResetKW40();

    timer_Init( HEXIWEAR_TIMER_SENSOR );

    RTC_Init();
    Flash_Init();
    
    // RGB off
    FLASH_SetOFF();

    // create basic tasks
    status |= Notification_Init();
    status |= HostInterface_Init();
    status |= sensor_Init();
    status |= GuiDriver_Init();
    
    haptic_MutexCreate();

    sensor_InitAcc();

    // VIBRO
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_9 );

    // Set GPIO interrupt for the tap function.
    GPIO_Digital_Input( &PTC_PDIR, _GPIO_PINMASK_1 );
    IRQC0_PORTC_PCR1_bit = 0;
    IRQC1_PORTC_PCR1_bit = 1;
    IRQC2_PORTC_PCR1_bit = 0;
    IRQC3_PORTC_PCR1_bit = 1;

    // Set charging battery interrupt.
    GPIO_Digital_Input( &PTC_PDIR, _GPIO_PINMASK_12 );
    IRQC0_PORTC_PCR12_bit = 1;
    IRQC1_PORTC_PCR12_bit = 1;
    IRQC2_PORTC_PCR12_bit = 0;
    IRQC3_PORTC_PCR12_bit = 1;

    HEXIWEAR_SetIntPriority(IVT_INT_PORTC, 4);
    NVIC_IntEnable( IVT_INT_PORTC );
    
    if( status != HEXIWEAR_STATUS_SUCCESS )
    {
        error_catch( CATCH_INIT );
    }

    // check for settings in flash at startup
    gui_sensorTag_CheckAtStartup();
    haptic_CheckAtStartup();

    POWER_SYS_Init();

    // turn on regular battery readings
//    sensor_SetPacketTargets( PACKET_BAT,
//        sensor_GetPacketTargets( PACKET_BAT) | PACKET_PUSH_POWER_MGMT, true );
    
    while( 1 )
    {
        power_Init();
        power_TurnScreenON();
        OSA_TaskDestroy( NULL );
    }
}

// Initialises the tasks.
hexiwear_status_t HEXIWEAR_Init()
{
    osa_status_t status;
    
    status = OSA_TaskCreate(
        HEXIWEAR_startup,
        "HEXIWEAR startup",
        HEXIWEAR_STARTUP_STACK_SIZE,
        NULL,
        HEXIWEAR_STARTUP_PRIO,
        0,
        false,
        &hexiwear_startup_handler );

    if( status != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
        return HEXIWEAR_STATUS_INIT_ERROR;
    }
    
    return HEXIWEAR_STATUS_SUCCESS;
}

// Resets the MCU.
void HEXIWEAR_ResetMCU()
{
    asm DSB;
    
    SCB_AIRCR = ( uint32_t )( ( 0x5FAUL << 16U )              |
                              ( SCB_AIRCR & ( 0x7UL << 8U ) ) |
                              ( 0x1UL << 2U ) );
    
    asm DSB;
    
    while( 1 )
        asm NOP;
}

// Returns the app backup list.
void *HEXIWEAR_GetAppBackupList()
{
    return HEXIWEAR_currentBackupList;
}

// Returns target to the current app.
packet_pushTarget_t HEXIWEAR_GetAppTarget()
{
    return HEXIWEAR_currentApp;
}

// Sets the backup list.
void HEXIWEAR_SetBackupList( packet_pushTarget_t* currentBackupList )
{
    HEXIWEAR_currentBackupList = currentBackupList;
}

// Sets the current app target.
void HEXIWEAR_SetTargetApp( packet_pushTarget_t currentApp )
{
    HEXIWEAR_currentApp = currentApp;
}

// Sets flags in the internal flash.
hexiwear_status_t HEXIWEAR_SetFlags (
    uint32_t flashAddress,
       void* flags,
    uint32_t flagSize )
{
    
    if ( ( flagSize % 8 ) != 0 )
        return HEXIWEAR_STATUS_INIT_ERROR;

    OSA_EnterCritical( kCriticalDisableInt );
    PTA_PDOR.B12 = 1;
    Flash_EraseSector( flashAddress );
    PTA_PDOR.B12 = 0;
    OSA_ExitCritical( kCriticalDisableInt );
    while( flagSize > 0 )
    {
        OSA_EnterCritical( kCriticalDisableInt );
        Flash_ProgramPhrase( flashAddress, ( uint8_t* )flags );
        OSA_ExitCritical( kCriticalDisableInt );
        
        flashAddress = ( uint8_t* )flashAddress + 8;
        flags = ( uint8_t* )flags + 8;
        flagSize = flagSize - 8;
    }
    
    return HEXIWEAR_STATUS_SUCCESS;
}

void vApplicationIdleHook( void )
{
    asm NOP;
}

// Creates the HEXIWEAR version event.
void HEXIWEAR_CreateVersionEvent()
{
    OSA_EventCreate( &HEXIWEAR_versionEvent, kEventAutoClear );
}

// Sends the version info via MKW40.
void HEXIWEAR_SendVersionReq()
{
    static hostInterface_packet_t dataPacket;
    
    dataPacket.length  = 3;
    dataPacket.type    = packetType_buildVersion;

    dataPacket._data[0] = HEXIWEAR_VERSION_MAJOR;
    dataPacket._data[1] = HEXIWEAR_VERSION_MINOR;
    dataPacket._data[2] = HEXIWEAR_VERSION_PATCH;

    dataPacket._data[3] = gHostInterface_trailerByte;
    
    while( HostInterface_TxQueueMsgPut( &dataPacket, true )
        != kStatus_OSA_Success ) {}
}

// Waits for HEXIWEAR version update.
osa_status_t HEXIWEAR_WaitForVersionUpdate( uint32_t timeout )
{
    osa_status_t status;
    event_flags_t setFlags;
    
    status = OSA_EventWait(
        &HEXIWEAR_versionEvent, HEXIWEAR_eventFlag, false, timeout, &setFlags );

    if( status != kStatus_OSA_Success )
        return kStatus_OSA_Error;

    return status;
}

// Updates the HEXIWEAR version.
osa_status_t HEXIWEAR_UpdateVersion()
{
    OSA_EventSet( &HEXIWEAR_versionEvent, (event_flags_t)HEXIWEAR_eventFlag );
    
    return kStatus_OSA_Success;
}

//----------

// Sets interrupt priority.
void HEXIWEAR_SetIntPriority(uint8_t ivt, uint8_t priority)
{
    uint32_t *p;
    uint8_t shift;

    // Is this a user interrupt or a system one?
    if (ivt > 15)
    {
        // user interrupt
        p = &NVIC_IPR0 + ((ivt - 16) >> 2);  // four interrupts in a register
        shift = (((ivt - 16) % 4) << 3);
    }
    else if (ivt > 3)
    {
        // system interrupt (exception)
        p = &SCB_SHPR1 + ((ivt - 4) >> 2);  // four interrupts in a register
        shift = (((ivt - 4) % 4) << 3);
    }
    else
    {
        // error
        return;
    }
    
    // Is the priority given in the lower nibble?
    if (priority & 0x0F)
        priority <<= 4;

    *p &= ~(0xF0UL << shift);          // delete the old value
    *p |= (uint32_t)priority << shift; // write new value
}