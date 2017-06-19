// File: sensor_driver.c

// Definitions of main functionalities in the sensors modules.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////
 
#include <string.h>

#include "HEXIWEAR_info.h"

#include "gui_driver.h"
#include "screens_common.h"

#include "sensor_driver.h"
#include "sensor_info.h"
#include "sensor_defs.h"

#include "power.h"

//#include "pedometer_driver.h"

#include "OLED_info.h"
#include "OLED_driver.h"

#include "error.h"

#include "timer_driver.h"

#include "heartRate_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define LED_DecrementCounter()                                                 \
    sensor_LEDCounter = ( sensor_LEDCounter == 0 ) ?                           \
                          sensor_LEDCounterInitVal :                           \
                          sensor_LEDCounter - 1
#define LED_HasCounterExpired() ( sensor_LEDCounter == 0 )

// If the sensorTag mode is active,
// go to sleep instead of waiting or suspending the task.
#define sensor_GoToSleep()                                                     \
if ( power_IsTotalSleepModeActive() == true )                                  \
{                                                                              \
    power_SetSleepSource( POWER_SLEEP_SENSOR_TAG );                            \
    power_GotoStandby();                                                       \
}

// Packet settings macros.
#define packetSettings_HasTargets( packet )                                    \
    ( PACKET_PUSH_NONE != packetSettings[ packet ].targets )
#define packetSettings_HasNoTargets( packet )                                  \
    ( PACKET_PUSH_NONE == packetSettings[ packet ].targets )

#define packetSettings_IncrementCounter( packet )                              \
    packetSettings[ packet ].counter += 1

#define packetSettings_DecrementCounter( packet )                              \
packetSettings[ packet ].counter = ( packetSettings[ packet ].counter == 0 ) ? \
                                     packetSettings[ packet ].initCounterVal : \
                                     packetSettings[ packet ].counter - 1

#define packetSettings_HasCounterExpired( packet )                             \
    ( ( packetSettings[ packet ].counter ) == 0 )
    
// Sensor settings macros.
#define sensorSettings_IsActive( sensor )                                      \
    ( sensorSettings[ sensor ].isActive == true )
#define sensorSettings_IsNotActive( sensor )                                   \
    ( sensorSettings[ sensor ].isActive == false )

#define sensorSettings_Activate( sensor )                                      \
    ( sensorSettings[ sensor ].isActive = true )
#define sensorSettings_Deactivate( sensor )                                    \
    ( sensorSettings[ sensor ].isActive = false )
    
// Helpful macros.

#define START_PACKET ( packetType_batteryLevel )
#define END_PACKET   ( packetType_steps )

#define NextSensor( sensor ) sensor                                            \
    = ( ( ++sensor ) % END_PACKET ) + START_PACKET * ( sensor / END_PACKET )

#define ShouldSensorBeActivated( sensor, packet )                              \
    ( packetSettings_HasTargets( packet )                                      \
    && sensorSettings_IsNotActive( sensor ) )
    
#define ShouldSensorBeDeactivated( sensor, packet )                            \
    ( packetSettings_HasNoTargets( packet )                                    \
    && sensorSettings_IsActive( sensor ) )

#define registerFormatters( sensType )                                         \
    sensor_fmtDef2Float = sensType##_fmtDef2Float;                             \
    sensor_fmtDef2Me    = sensType##_fmtDef2Me;                                \
    sensor_fmtDef2Byte  = sensType##_fmtDef2Byte

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    SEND_YES,
    SEND_NO,
    SEND_TRY_AGAIN,
    SEND_SKIP

} send_t;

typedef enum
{
    TASK_RESUME,
    TASK_SUSPEND

} taskAction_t;

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static sbit KW40_WU at PTD_PDOR.B14;

static bool isSensorTaskActive = true;

static uint32_t oldPeriodVal = 0;
static uint32_t newPeriodVal = 0;

static uint32_t sensor_minDelay_ms = SENSOR_DEFAULT_MINIMUM_DELAY_MS;

static bool FXOS_firstTime = true;
static bool FXAS_firstTime = true;
static bool MPL_firstTime  = true;

static mutex_t taskAccessMutex;

static semaphore_t sensor_sema;

static uint8_t KW40_backupList[ PACKET_ALL ] = { 0 };

static uint8_t sensor_retryCnt = SENSOR_RETRY_NUM;

static uint16_t bat_mvolts = 0;

static uint32_t sensor_LEDCounter = 1;
static uint32_t sensor_LEDCounterInitVal =
    ( ( 1000 * 8000 ) //( 1000 * TIMER_BLINKING_PERIOD_MS )
    / ( 1000 * SENSOR_DEFAULT_MINIMUM_DELAY_MS ) ) - 1;

// Packet settings.
static packet_settings_t packetSettings[ PACKET_ALL ] =
{
    // PACKET_ACC
    {
        PACKET_PUSH_NONE,            // .targets
        ACC_DEFAULT_POLL_PERIOD_MS,  // .defaultDelay_ms
        0,                           // .delay_ms
        0,                           // .initCounterVal
        1                            // .counter
    },

    // PACKET_MAG
    {
        PACKET_PUSH_NONE,            // .targets
        MAG_DEFAULT_POLL_PERIOD_MS,  // .defaultDelay_ms
        0,                           // .delay_ms
        0,                           // .initCounterVal
        1                            // .counter
    },

    // PACKET_GYRO
    {
        PACKET_PUSH_NONE,            // .targets
        GYRO_DEFAULT_POLL_PERIOD_MS, // .defaultDelay_ms
        0,                           // .delay_ms
        0,                           // .initCounterVal
        1                            // .counter
    },

    // PACKET_PRES
    {
        PACKET_PUSH_NONE,            // .targets
        PRES_DEFAULT_POLL_PERIOD_MS, // .defaultDelay_ms
        0,                           // .delay_ms
        0,                           // .initCounterVal
        1                            // .counter
    },

    // PACKET_TEMP
    {
        PACKET_PUSH_NONE,            // .targets
        TEMP_DEFAULT_POLL_PERIOD_MS, // .defaultDelay_ms
        0,                           // .delay_ms
        0,                           // .initCounterVal
        1                            // .counter
    },

    // PACKET_HUM
    {
        PACKET_PUSH_NONE,            // .targets
        HUM_DEFAULT_POLL_PERIOD_MS,  // .defaultDelay_ms
        0,                           // .delay_ms
        0,                           // .initCounterVal
        1                            // .counter
    },

    // PACKET_LUX
    {
        PACKET_PUSH_NONE,            // .targets
        LUX_DEFAULT_POLL_PERIOD_MS,  // .defaultDelay_ms
        0,                           // .delay_ms
        0,                           // .initCounterVal
        1                            // .counter
    },

    // PACKET_HR
    {
        PACKET_PUSH_NONE,            // .targets
        400,                         // .defaultDelay_ms
        0,                           // .delay_ms
        0,                           // .initCounterVal
        1                            // .counter
    },

    // PACKET_BAT
    {
        PACKET_PUSH_NONE,            // .targets
        BAT_DEFAULT_POLL_PERIOD_MS,  // .defaultDelay_ms
        0,                           // .delay_ms
        0,                           // .initCounterVal
        1                            // .counter
    }
};

// sensors settings
static sensor_settings_t sensorSettings[ SENSOR_ALL ] =
{
    // SENSOR_FXOS
    {
        false // .isActive
    },

    // SENSOR_FXAS
    {
        false // .isActive
    },

    // SENSOR_MPL
    {
        false // .isActive
    },

    // SENSOR_HTU
    {
        false // .isActive
    },

    // SENSOR_TSL
    {
        false // .isActive
    },

    // SENSOR_MAXIM
    {
        false // .isActive
    },

    // SENSOR_BATT
    {
        false // .isActive
    }
};

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Formats raw to float.
static void bat_fmtDef2Float(
                              const void* src,
                                    void* dst,
                                 uint32_t idx
                            )
{
    // helper pointers
    uint16_t* input = ( uint16_t* )src;
    float* output = ( float* )dst;

    // convert data
    output[idx] = ( float )input[idx] * ( 3.3 / 65536.0 );
}

// Formats raw to mE format.
static void bat_fmtDef2Me(
                           const void* src,
                                 void* dst,
                              uint32_t idx
                         )
{
    // helper pointers
    uint16_t* input = ( uint16_t* )src;
    mE_t* output = ( mE_t* )dst;

    // convert data to milivolts
    bat_mvolts = ( uint16_t )
        ( ( ( float )input[idx] * ( 3.3 / 65535.0 ) ) * 1000 );

    if( bat_mvolts > 2670 )
    {
        output[idx] = 100;
    }
    else if( bat_mvolts > 2500 )
    {
        output[idx] = ( mE_t )( 50 + 50.0 * ( ( bat_mvolts - 2500 ) / 170.0 ) );
    }
    else if ( bat_mvolts > 2430 )
    {
        output[idx] = ( mE_t )( 30 + 20.0 * ( ( bat_mvolts - 2430 ) / 70.0 ) );
    }
    else if ( bat_mvolts > 2370 )
    {
        output[idx] = ( mE_t )( 10 + 20.0 * ( ( bat_mvolts - 2370 ) / 60.0 ) );
    }
    else
    {
        output[idx] = 0;
    }
}

// Formats raw to byte - currently unimplemented.
static void bat_fmtDef2Byte (
                              const void* src,
                                    void* dst,
                                 uint32_t idx
                            )
{}

// Formats sensor data to various formats.
static void sensor_FormatData(
                                  const void* src,
                                        void* dst,
                                const uint8_t fmtOptions
                              )
{
    // counting index
    uint8_t idx;
    // data length
    uint8_t dataLen;
    // fmtOptions bit-field [3:0] - sensor type
    uint8_t dataType      = Extract( fmtOptions, DATA_TYPE );
    // fmtOptions bit-field [5:4] - old format
    uint8_t oldDataFormat = Extract( fmtOptions, DATA_FORMAT_FROM );
    // fmtOptions bit-field [7:6] - new format
    uint8_t newDataFormat = Extract( fmtOptions, DATA_FORMAT_TO );

    // Register formatting functions and determine data length.

    switch( dataType )
    {
        // battery level
        case DATA_TYPE_BATTERYLEVEL:
            registerFormatters( bat );
            dataLen = TypeMember_SCALAR;
            break;

        // motion data
        case DATA_TYPE_ACCEL:
            registerFormatters( acc );
            dataLen = TypeMember_NumEl( motionData_t, accData );
            break;
                          
        case DATA_TYPE_MAG:
            registerFormatters( mag );
            dataLen = TypeMember_NumEl( motionData_t, magData );
            break;

        case DATA_TYPE_GYRO:
            registerFormatters( gyro );
            dataLen = TypeMember_NumEl( motionData_t, gyroData );
            break;

        // weather data

        case DATA_TYPE_AMBI:
            registerFormatters( ambi );
            // dataLen = TypeMember_NumEl( weatherData_t, ambiData );
            dataLen = TypeMember_SCALAR;
            break;

        case DATA_TYPE_TEMP:
            registerFormatters( temp );
            dataLen = TypeMember_SCALAR;
            break;

        case DATA_TYPE_HUMID:
            registerFormatters( hum );
            dataLen = TypeMember_SCALAR;
            break;

        case DATA_TYPE_PRES:
            registerFormatters( pres );
            dataLen = TypeMember_SCALAR;
            break;

        // health data

        case DATA_TYPE_HR:
            // registerFormatters( hr );
            dataLen = TypeMember_SCALAR;
            break;

        case DATA_TYPE_STEPS:
            break;
            
        case DATA_TYPE_CALORIES:
            break;

        default:
            // To bypass the warning.
            dataLen = TypeMember_SCALAR;
            break;
    } // switch( dataType )

    // Format data to its new format.

    switch( oldDataFormat )
    {
        case DATA_FORMAT_FROM_DEFAULT:
        {
            switch( newDataFormat )
            {
                case DATA_FORMAT_TO_DEFAULT:
                    break;

                case DATA_FORMAT_TO_BYTE:
                    for( idx = 0; idx < dataLen; idx++ )
                    {
                        sensor_fmtDef2Byte(src, dst, idx);
                    }
                    break;

                case DATA_FORMAT_TO_mE:
                    for( idx = 0; idx < dataLen; idx++ )
                    {
                        sensor_fmtDef2Me(src, dst, idx);
                    }
                    break;


                case DATA_FORMAT_TO_FLOAT:
                    for( idx = 0; idx < dataLen; idx++ )
                    {
                        sensor_fmtDef2Float(src, dst, idx);
                    }
                    break;

                default:
                    break;
            }

            break;
        } // case DATA_FORMAT_FROM_DEFAULT

        case DATA_FORMAT_FROM_FLOAT: 
        {
            switch( newDataFormat )
            {
                case DATA_FORMAT_TO_DEFAULT:
                    break;
                case DATA_FORMAT_TO_FLOAT:
                    break;
                case DATA_FORMAT_TO_mE:
                    break;
                default:
                    break;
            }

            break;
        } // case DATA_FORMAT_FROM_FLOAT

        case DATA_FORMAT_FROM_mE:
        {
            switch( newDataFormat )
            {
                case DATA_FORMAT_TO_DEFAULT: 
                    break;
                case DATA_FORMAT_TO_FLOAT:
                    break;
                case DATA_FORMAT_TO_mE:
                    break;
                default:
                    break;
            }
            
            break;
        } // case DATA_FORMAT_FROM_mE
        
        default:
            break;
    }
}


// Creates a binary semaphore for the sensors module.
static osa_status_t sensor_CreateBinSema( semaphore_t* semaphore )
{
    *semaphore = xSemaphoreCreateCounting( 0x1, 0 );
    
    if( *semaphore == NULL )
    {
        return kStatus_OSA_Error;
    }
    
    return kStatus_OSA_Success;
}

// Check if there are any flags active.
static bool sensor_AreThereNoTargets()
{
    packet_t pktIdx;
    bool confirmDestroy = true;
    
    for( pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
    {
        if( packetSettings_HasTargets( pktIdx ) )
        {
            confirmDestroy = false;
            break;
        }
    }
    
    return confirmDestroy;
}

// Gets number of active packets.
static uint8_t GetActivePacketsNum()
{
    packet_t pktIdx;
    uint8_t activePacketsNum = 0;

    for( pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
    {
        if( packetSettings_HasTargets( pktIdx ) )
        {
            activePacketsNum++;
        }
    }

    return activePacketsNum;
}

// Registers the counter value for the packet.
static void UpdatePacketCounters()
{
    packet_t pktIdx;
    uint8_t activePacketNum = GetActivePacketsNum();
    
    if( activePacketNum != 0 )
    {
        for( pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
        {
            if( packetSettings_HasTargets( pktIdx ) )
            {
                uint32_t oldInitVal = packetSettings[ pktIdx ].initCounterVal;
                packetSettings[ pktIdx ].initCounterVal =
                    ceil( ( 1000 * packetSettings[ pktIdx ].delay_ms )
                    / ( ( 1000 * sensor_minDelay_ms )
                    /* / activePacketNum */ ) ) - 1;

                // If there was a change in counter values,
                // trigger new sensor reading.
                if( oldInitVal != packetSettings[ pktIdx ].initCounterVal )
                    sensor_ResetPacketcounter( pktIdx );
            }
        }
        
        // By the same logic, update the LED counter reload value
        // and reset the counter, if appropriate.
        sensor_LEDCounterInitVal = ( ceil( ( 1000 * TIMER_BLINKING_PERIOD_MS )
                                   / ( ( 1000 * sensor_minDelay_ms ) ) )
                                   * activePacketNum ) - 1;
    }
}

// Waits on the sensor semaphore.
static sensor_status_t sensor_Wait()
{
    osa_status_t status = OSA_SemaWait( &sensor_sema, OSA_WAIT_FOREVER );

    if( status != kStatus_OSA_Success )
    {
        return SENSOR_STATUS_ERROR;
    }

    return SENSOR_STATUS_SUCCESS;
}

// Gets the timer period.
// Converts to [us] and divides by the number of active packets.
static uint32_t sensor_GetTimerPeriod()
{
    uint8_t activePacketNum = GetActivePacketsNum();
    
    if( activePacketNum != 0 )
    {
        return sensor_minDelay_ms * 1000 / activePacketNum;
    }
    else
    {
        return sensor_minDelay_ms * 1000;
    }
}

// Sets the timer period.
// Converts to [us] and divides by the number of active packets.
static void sensor_SetTimerPeriod( uint32_t newPeriod )
{
    if( newPeriod != 0 )
        timer_SetPeriod( HEXIWEAR_TIMER_SENSOR, newPeriod );
}

// Updates the sensor timer period.
static void sensor_UpdateTimer()
{
    oldPeriodVal = newPeriodVal;
    newPeriodVal = sensor_GetTimerPeriod();

    if( oldPeriodVal != newPeriodVal )
        sensor_SetTimerPeriod( newPeriodVal );
}

// Pushes sensor data.
static void sensor_PushData(
                             hostInterface_packet_t* dataPacket,
                                 packet_pushTarget_t pushTargets )
{
    if( ( pushTargets & PACKET_PUSH_KW40 ) != 0 )
    {
        if( power_GetCurrentMode() == POWER_CURRENT_MODE_SLEEP_SENSOR_TAG )
        {
            KW40_WU = !KW40_WU;
            OSA_TimeDelay( 10 );
        }
        HostInterface_TxQueueMsgPut( dataPacket, false );
    }
    
    if( ( pushTargets & PACKET_PUSH_OLED ) != 0 )
    {
        if( power_IsActive( POWER_OLED ) == true )
            GuiDriver_QueueMsgPut( dataPacket );
    }
    
    if( ( pushTargets & PACKET_PUSH_APP_PEDOMETER ) != 0 )
    {
        // pedometer_QueueMsgPut( dataPacket ); TODO: pedometer
    }
    
    if( ( pushTargets & PACKET_PUSH_APP_HEART_RATE ) != 0 )
    {
        // Do nothing.
    }
    
    if( ( pushTargets & PACKET_PUSH_POWER_MGMT ) != 0 )
    {
        switch( dataPacket->type )
        {
            case packetType_batteryLevel:
                if( bat_mvolts != 0 )
                {
                    if( bat_mvolts < 2267 )
                    {
                        power_SetBatteryLow();
                    }
                    else if( bat_mvolts >= 2400 )
                    {
                        power_UnsetBatteryLow();
                    }
                }
                break;

            default:
                break;
        }
    }
}

// Initialises sensors' modules.
static void sensor_InitModules()
{
#ifdef SENSOR_FXOS_PRESENT
    if( ShouldSensorBeActivated( SENSOR_FXOS, PACKET_ACC )
        || ShouldSensorBeActivated( SENSOR_FXOS, PACKET_MAG ) )
    {
        if( FXOS_firstTime == true )
            FXOS_Init();

        sensorSettings_Activate( SENSOR_FXOS );
        if( FXOS_firstTime == true )
            FXOS_firstTime = false;
    }
#endif

#ifdef SENSOR_FXAS_PRESENT
    if( ShouldSensorBeActivated( SENSOR_FXAS, PACKET_GYRO ) )
    {
        if( FXAS_firstTime == true )
            FXAS_Init();
        else
            FXAS_SetActive();
        
        sensorSettings_Activate( SENSOR_FXAS );
        if( FXAS_firstTime == true )
            FXAS_firstTime = false;
    }
#endif

#ifdef SENSOR_MPL_PRESENT
    if( ShouldSensorBeActivated( SENSOR_MPL, PACKET_PRES ) )
    {
        if( MPL_firstTime == true )
            MPL_Init();
        else
            MPL_SetActive();

        sensorSettings_Activate( SENSOR_MPL );
        if( MPL_firstTime == true )
            MPL_firstTime = false;
    }
#endif

#ifdef SENSOR_HTU_PRESENT
    if( ShouldSensorBeActivated( SENSOR_HTU, PACKET_HUM )
        || ShouldSensorBeActivated( SENSOR_HTU, PACKET_TEMP ) )
    {
        if( power_IsActive( POWER_HTU_TSL ) == true )
        {
            HTU_Init();
            
            sensorSettings_Activate( SENSOR_HTU );
        }
        else
        {
            error_catch( CATCH_SENSOR );
        }
    }
#endif

#ifdef SENSOR_TSL_PRESENT
    if( ShouldSensorBeActivated( SENSOR_TSL, PACKET_LUX ) )
    {
        if( power_IsActive( POWER_HTU_TSL ) == true )
        {
            TSL_Init();
            
            sensorSettings_Activate( SENSOR_TSL );
        }
        else
        {
            error_catch( CATCH_SENSOR );
        }
    }
#endif

#ifdef SENSOR_MAXIM_PRESENT
    if( ShouldSensorBeActivated( SENSOR_MAXIM, PACKET_HR ) )
    {
        if( power_IsActive( POWER_MAXIM ) == true )
        {
            MAXIM_Init();

            MAXIM_Enable();
            sensorSettings_Activate( SENSOR_MAXIM );
            MAXIM_InstallCallback( heartRate_Process );
        }
        else
        {
            error_catch( CATCH_SENSOR );
        }
    }
#endif
}

// Put NXP sensors to standby or just mark non-NXP sensors as inactive.
static void sensor_DeinitModules()
{
#ifdef SENSOR_FXOS_PRESENT

#endif

#ifdef SENSOR_FXAS_PRESENT
    if( ShouldSensorBeDeactivated( SENSOR_FXAS, PACKET_GYRO ) )
    {
        sensorSettings_Deactivate( SENSOR_FXAS );
        
        FXAS_GotoStandby();
    }
#endif

#ifdef SENSOR_MPL_PRESENT
    if( ShouldSensorBeDeactivated( SENSOR_MPL, PACKET_PRES ) )
    {
        sensorSettings_Deactivate( SENSOR_MPL );

        MPL_GotoStandby();
    }
#endif

#ifdef SENSOR_HTU_PRESENT
    if( ShouldSensorBeDeactivated( SENSOR_HTU, PACKET_HUM ) 
        && ShouldSensorBeDeactivated( SENSOR_HTU, PACKET_TEMP ) )
    {
        sensorSettings_Deactivate( SENSOR_HTU );
    }
#endif

#ifdef SENSOR_TSL_PRESENT
    if( ShouldSensorBeDeactivated( SENSOR_TSL, PACKET_LUX ) )
    {
        sensorSettings_Deactivate( SENSOR_TSL );
    }
#endif

#ifdef SENSOR_MAXIM_PRESENT
    if( ShouldSensorBeDeactivated( SENSOR_MAXIM, PACKET_HR ) )
    {
        // MAXIM_Disable(); - not needed
        sensorSettings_Deactivate( SENSOR_MAXIM );
    }
#endif
}

// Pauses/resumes the sensor task, depending on the active sensors.
static void sensor_ChangeTaskState( taskAction_t taskAction )
{
    osa_status_t mutexStatus;

    mutexStatus = OSA_MutexLock( &taskAccessMutex, OSA_WAIT_FOREVER );

    if( kStatus_OSA_Success == mutexStatus )
    {
        // Checks for the current flag state.
        bool confirmDestroy = sensor_AreThereNoTargets();

        switch( taskAction )
        {
            // If the task is to be suspended, the correct sequence is:
            // init/deinit -> power supply on/off -> suspend.
            case TASK_SUSPEND:
            {
                sensor_InitModules();
                sensor_DeinitModules();

                power_SensorManagement();

                if( confirmDestroy == true )
                {
                    OSA_MutexUnlock( &taskAccessMutex );
                    sensor_Suspend();
                }

                break;
            }

            // If the task is to be resumed, the sequence is:
            // power supply on/off -> resume -> init/deinit
            // (the last step will occur during the task execution).
            case TASK_RESUME:
            {
                power_SensorManagement();

                if( confirmDestroy == false )
                    sensor_Resume();

                break;
            }

           default:
               break;
        } // switch( taskAction )
    }
    else
    {
        error_catch( CATCH_MUTEX );
    }

    OSA_MutexUnlock( &taskAccessMutex );
}

// Retrieves data from various sensors.
static void sensor_GetData( task_param_t param )
{
    // Data packet to be sent.
    hostInterface_packet_t sensorPacket;
    
    // Use this to announce if the packet is ready to be sent.
    send_t isReadyToSend = SEND_NO;
    
    // Packet type.
    hostInterface_packetType_t sensorToSend = START_PACKET;
    
    // Formatting options.
    uint8_t fmtOptions = 0;
    
    // Battery level.
    uint16_t adcData = 0;
    
    void *dataStart = NULL;
    
    packet_pushTarget_t pushTargets;
    
    // Format for all the data: RAW -> mE or byte.
    Write( fmtOptions, DATA_FORMAT_FROM, DATA_FORMAT_FROM_DEFAULT );
    
    while( 1 )
    {
        sensor_UpdateTimer();
        Write( fmtOptions, DATA_FORMAT_TO, DATA_FORMAT_TO_mE );
        
        // (De)Initialise appropriate sensors, power supplies,
        // suspends the task, if appropriate.
        sensor_ChangeTaskState( TASK_SUSPEND );
        isReadyToSend = SEND_NO;
        
        // Prepare the data packet.
        sensorPacket.type = sensorToSend;
        
        // Read, format and insert data into the packet.
        switch( sensorToSend )
        {
            // Battery level
            
            case packetType_batteryLevel:
            {
                if( packetSettings_HasTargets( PACKET_BAT ) )
                {
                    packetSettings_DecrementCounter( PACKET_BAT );
                    isReadyToSend = SEND_SKIP;
                    if( packetSettings_HasCounterExpired( PACKET_BAT ) )
                    {
                        // configure ADC0 channel
                        ADC0_SC1A = 0x10;
                        // wait for conversion to complete
                        while( COCO_bit == 0 );
                        // read ADC0 data
                        adcData = ADC0_RA;
                        // pause current ADC0 conversion
                        ADC0_SC1A = 0x1F;
                        
                        dataStart           = ( void* )&( adcData );
                        sensorPacket.length = TypeMember_SCALAR;
                        pushTargets = packetSettings[ PACKET_BAT ].targets;
                        isReadyToSend       = SEND_YES;
                        sensor_retryCnt     = SENSOR_RETRY_NUM;
                    }
                    else
                    {
                        asm NOP;
                    }
                }
                break;
            }
            
            // MOTION
            
            case packetType_accel:
            {
#ifdef SENSOR_FXOS_PRESENT
                if( packetSettings_HasTargets( PACKET_ACC ) )
                {
                    packetSettings_DecrementCounter( PACKET_ACC );
                    isReadyToSend = SEND_SKIP;
                    if( packetSettings_HasCounterExpired( PACKET_ACC ) )
                    {
                        uint8_t fxosStatus;

                        if( sensorSettings_IsActive( SENSOR_FXOS ) )
                        {
                            uint8_t sensorStatus;
                            fxosStatus = 0;

                            FXOS_ReadStatus( &sensorStatus );

                            if( sensorStatus == 0x00 )
                            {
                                fxosStatus = 1;
                            }
                            // Also check if tap is enabled.
                            else if( FXOS_CheckForTap() == false )
                            {
                                fxosStatus = 1;
                            }
                            else
                            {
                                FXOS_ReadRawData( ( int16_t* )&motionData );
                            }
                        }
                        else
                        {
                            fxosStatus = 2;
                        }

                        if( fxosStatus == 0 )
                        {
                            dataStart           
                                = ( void* )&( motionData.accData[0] );
                            sensorPacket.length 
                                = TypeMember_NumEl( motionData_t, accData );
                            pushTargets         
                                = packetSettings[PACKET_ACC].targets;
                            isReadyToSend       
                                = SEND_YES;
                            sensor_retryCnt     
                                = SENSOR_RETRY_NUM;
                        }
                        // Try again, when the initialisation is successful.
                        else if( fxosStatus == 2 )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_ACC );
                        }
                        // Else, report the error and eventually move on.
                        else
                        {
                            if( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_ACC );
                                sensor_retryCnt--;
                            }
                            else
                            {
                                FXOS_firstTime = true;
                                FXOS_SoftReset();
                                sensorSettings_Deactivate( SENSOR_FXOS );
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                error_catch( CATCH_MOTION );
                            }
                        }
                    }
                }
#endif
                break;
            }
            
            case packetType_magnet:
            {
#ifdef SENSOR_FXOS_PRESENT
                if( packetSettings_HasTargets( PACKET_MAG ) )
                {
                    packetSettings_DecrementCounter( PACKET_MAG );
                    isReadyToSend = SEND_SKIP;
                    if ( packetSettings_HasCounterExpired( PACKET_MAG ) )
                    {
                        uint8_t fxosStatus;

                        if( sensorSettings_IsActive( SENSOR_FXOS ) )
                        {
                            fxosStatus = 0;
                            
                            FXOS_ReadRawData( (int16_t*)&motionData );
                        }
                        else
                        {
                            fxosStatus = 2;
                        }

                        if( fxosStatus == 0 )
                        {
                            dataStart           
                                = ( void* )&( motionData.magData[0] );
                            sensorPacket.length 
                                = TypeMember_NumEl( motionData_t, magData );
                            pushTargets         
                                = packetSettings[ PACKET_MAG ].targets;
                            isReadyToSend       
                                = SEND_YES;
                            sensor_retryCnt     
                                = SENSOR_RETRY_NUM;
                        }
                        // Try again, when the initialisation is successful.
                        else if( fxosStatus == 2 )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_MAG );
                        }
                        // Else, report the error and eventually move on.
                        else
                        {
                            if( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_MAG );
                                sensor_retryCnt--;
                            }
                            else
                            {
                                FXOS_firstTime = true;
                                FXOS_SoftReset();
                                sensorSettings_Deactivate( SENSOR_FXOS );
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                error_catch( CATCH_MOTION );
                            }
                        }
                    }
                }
#endif
                break;
            }
            
            case packetType_gyro:
            {
#ifdef SENSOR_FXAS_PRESENT
                if( packetSettings_HasTargets( PACKET_GYRO ) )
                {
                    packetSettings_DecrementCounter( PACKET_GYRO );
                    isReadyToSend = SEND_SKIP;
                    if( packetSettings_HasCounterExpired( PACKET_GYRO ) )
                    {
                        uint8_t fxasStatus;

                        if( sensorSettings_IsActive( SENSOR_FXAS ) )
                        {
                            fxasStatus = 0;
                            FXAS_ReadRawData(
                                ( int16_t* )&( motionData.gyroData[0] ) );
                        }
                        else
                        {
                            fxasStatus = 2;
                        }

                        if( fxasStatus == 0 )
                        {
                            dataStart           
                                = ( void* )&( motionData.gyroData[0] );
                            sensorPacket.length 
                                = TypeMember_NumEl( motionData_t, gyroData );
                            pushTargets         
                                = packetSettings[PACKET_GYRO].targets;
                            isReadyToSend       
                                = SEND_YES;
                            sensor_retryCnt     
                                = SENSOR_RETRY_NUM;
                        }
                        // Try again, when the initialisation is successful.
                        else if( fxasStatus == 2 )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_GYRO );
                        }
                        // Else, report the error and eventually move on.
                        else
                        {
                            if( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_GYRO );
                                sensor_retryCnt--;
                            }
                            else
                            {
                                FXAS_firstTime = true;
                                FXAS_SoftReset();
                                sensorSettings_Deactivate( SENSOR_FXAS );
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                error_catch( CATCH_MOTION );
                            }
                        }
                    }
                }
#endif
                break;
            }
            
            // WEATHER
            
            case packetType_temperature:
            {
#ifdef SENSOR_HTU_PRESENT
                if( packetSettings_HasTargets( PACKET_TEMP ) )
                {
                    packetSettings_DecrementCounter( PACKET_TEMP );
                    isReadyToSend = SEND_SKIP;
                    if( packetSettings_HasCounterExpired( PACKET_TEMP ) )
                    {
                        uint8_t htuStatus;

                        if( sensorSettings_IsActive( SENSOR_HTU ) )
                        {
                            htuStatus = 0;
                            HTU_GetTemp(
                                ( int16_t* )&( weatherData.tempData ) );
                        }
                        else
                        {
                            htuStatus = 2;
                        }

                        if( htuStatus == 0 )
                        {
                            dataStart           
                                = ( void* )&( weatherData.tempData );
                            sensorPacket.length 
                                = TypeMember_SCALAR;
                            pushTargets         
                                = packetSettings[PACKET_TEMP].targets;
                            isReadyToSend       
                                = SEND_YES;
                            sensor_retryCnt     
                                = SENSOR_RETRY_NUM;
                        }
                        // Try again, when the initialisation is successful.
                        else if( htuStatus == 2 )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_TEMP );
                        }
                        // Else, report the error and eventually move on.
                        else
                        {
                            if( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_TEMP );
                                sensor_retryCnt--;
                            }
                            else
                            {
                                HTU_SoftReset();
                                sensorSettings_Deactivate( SENSOR_HTU );
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                error_catch( CATCH_WEATHER );
                            }
                        }
                    }
                }
#endif
                break;
            }
            
            case packetType_humidity:
            {
#ifdef SENSOR_HTU_PRESENT
                if( packetSettings_HasTargets( PACKET_HUM ) )
                {
                    packetSettings_DecrementCounter( PACKET_HUM );
                    isReadyToSend = SEND_SKIP;
                    if ( packetSettings_HasCounterExpired( PACKET_HUM ) )
                    {
                        uint8_t htuStatus;

                        if( sensorSettings_IsActive( SENSOR_HTU ) )
                        {
                            htuStatus = 0;
                            HTU_GetHum(
                                ( int16_t* )&( weatherData.humidData ) );

                            // If read is 0, try again.
                            if( weatherData.humidData == 0 )
                            {
                                htuStatus = 1;
                            }
                        }
                        else
                        {
                            htuStatus = 2;
                        }

                        if( htuStatus == 0 )
                        {
                            dataStart           
                                = ( void* )&( weatherData.humidData );
                            sensorPacket.length 
                                = TypeMember_SCALAR;
                            pushTargets         
                                = packetSettings[PACKET_HUM].targets;
                            isReadyToSend       
                                = SEND_YES;
                            sensor_retryCnt     
                                = SENSOR_RETRY_NUM;
                        }
                        // Try again, when the initialization is successful.
                        else if( htuStatus == 2 )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_HUM );
                        }
                        // Else, report the error and eventually move on.
                        else
                        {
                            if( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_HUM );
                                sensor_retryCnt--;
                            }
                            else
                            {
                                HTU_SoftReset();
                                sensorSettings_Deactivate( SENSOR_HTU );
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                error_catch( CATCH_WEATHER );
                            }
                        }
                    }
                }
#endif
                break;
            }
            
            case packetType_pressure:
            {
#ifdef SENSOR_MPL_PRESENT
                if( packetSettings_HasTargets( PACKET_PRES ) )
                {
                    packetSettings_DecrementCounter( PACKET_PRES );
                    isReadyToSend = SEND_SKIP;
                    if( packetSettings_HasCounterExpired( PACKET_PRES ) )
                    {
                        uint8_t mplStatus;

                        if( sensorSettings_IsActive( SENSOR_MPL ) )
                        {
                            mplStatus = 0;
                            MPL_ReadRawData( MPL_MODE_PRESSURE,
                                ( int16_t* )&( weatherData.presAltData ) );
                        }
                        else
                        {
                                mplStatus = 2;
                        }

                        if( mplStatus == 0 )
                        {
                            dataStart           
                                = ( void* )&( weatherData.presAltData );
                            sensorPacket.length 
                                = TypeMember_SCALAR;
                            pushTargets         
                                = packetSettings[PACKET_PRES].targets;
                            isReadyToSend       
                                = SEND_YES;
                            sensor_retryCnt     
                                = SENSOR_RETRY_NUM;
                        }
                        // Try again, when the initialization is successful.
                        else if( mplStatus == 2 )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_PRES );
                        }
                        // Else, report the error and eventually move on.
                        else
                        {
                            if( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_PRES );
                                sensor_retryCnt--;
                            }
                            else
                            {
                                MPL_firstTime = true;
                                MPL_SoftReset();
                                sensorSettings_Deactivate( SENSOR_MPL );
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                error_catch( CATCH_WEATHER );
                            }
                        }
                    }
                }
#endif
                break;
            }
            
            case packetType_ambiLight:
            {
#ifdef SENSOR_TSL_PRESENT
                if( packetSettings_HasTargets( PACKET_LUX ) )
                {
                    packetSettings_DecrementCounter( PACKET_LUX );
                    isReadyToSend = SEND_SKIP;
                    if( packetSettings_HasCounterExpired( PACKET_LUX ) )
                    {
                        uint8_t tslStatus = 0;
                        uint32_t luxVal;
                        uint16_t TSL_adcData[2];

                        if( sensorSettings_IsActive( SENSOR_TSL ) )
                        {
                            tslStatus = 0;
                            TSL_ReadRawData(
                                TSL_CHANNEL_FULL, &( TSL_adcData[0] ) );
                            TSL_ReadRawData(
                                TSL_CHANNEL_INFRARED, &( TSL_adcData[1] ) );
                        }
                        else
                        {
                            tslStatus = 2;
                        }

                        if( tslStatus == 0 )
                        {
                            TSL_CalculateLux( &( TSL_adcData[0] ), &luxVal );
                            TSL_FormatLux( luxVal, &( weatherData.ambiData ) );

                            Write( fmtOptions,
                                DATA_FORMAT_TO, DATA_FORMAT_TO_BYTE );
                            dataStart 
                                = ( void* )&( weatherData.ambiData );
                            sensorPacket.length 
                                = TypeMember_SCALAR;
                            pushTargets         
                                = packetSettings[PACKET_LUX].targets;
                            isReadyToSend       
                                = SEND_YES;
                            sensor_retryCnt     
                                = SENSOR_RETRY_NUM;
                        }
                        // Try again, when the initialization is successful.
                        else if( tslStatus == 2 )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_LUX );
                        }
                        // Else, report the error and eventually move on.
                        else
                        {
                            if( sensor_retryCnt > 0 )
                            {
                                isReadyToSend = SEND_TRY_AGAIN;
                                packetSettings_IncrementCounter( PACKET_LUX );
                                sensor_retryCnt--;
                            }
                            else
                            {
                                isReadyToSend   = SEND_NO;
                                sensor_retryCnt = SENSOR_RETRY_NUM;
                                error_catch( CATCH_WEATHER );
                            }
                        }
                    }
                }
#endif
                break;
            }
            
            case packetType_heartRate:
            {
#ifdef SENSOR_MAXIM_PRESENT
                if( packetSettings_HasTargets( PACKET_HR ) )
                {
                    packetSettings_DecrementCounter( PACKET_HR );
                    isReadyToSend = SEND_SKIP;
                    if( packetSettings_HasCounterExpired( PACKET_HR ) )
                    {
                        uint8_t maximStatus;

                        if( sensorSettings_IsActive( SENSOR_MAXIM ) )
                        {
                            maximStatus = 0;
                            MAXIM_ReadRawData( NULL, NULL );
                        }
                        else
                        {
                            maximStatus = 2;
                        }

                        if( maximStatus == 0 )
                        {
                            // ...
                        }
                        else if( maximStatus == 2 )
                        {
                            isReadyToSend = SEND_TRY_AGAIN;
                            packetSettings_IncrementCounter( PACKET_HR );
                        }
                        else
                        {
                            isReadyToSend = SEND_NO;
                            error_catch( CATCH_HEALTH );
                        }
                    }
                }
#endif
                break;
            }
            
            default:
            {
                break;
            }
        } // switch
        
        // Blink a LED if needed.
        if( isReadyToSend != SEND_NO )
        {
            LED_DecrementCounter();
            if( LED_HasCounterExpired() )
            {
                if( flashlight_isFlashlightOn() == false )
                {
                    switch( power_GetCurrentMode() )
                    {
                        // in normal or shallow sleep case, blink normally
                        case POWER_CURRENT_MODE_NORMAL:
                        case POWER_CURRENT_MODE_SLEEP_SHALLOW:
                        {
                            if( power_IsBatteryLow() == true )
                            {
                                RED_LED_ON();
                                OSA_TimeDelay( 10 );
                                RED_LED_OFF();
                            }
                            else if( ( true == gui_sensorTag_IsActive() ) &&
                                ( watch_CurrentLinkStateGet()
                                    == linkState_connected ) )
                            {
                                BLUE_LED_ON();
                                OSA_TimeDelay( 10 );
                                BLUE_LED_OFF();
                            }
                            break;
                        }

                        // blink BLUE or RED, depending on the battery state
                        case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
                        {
                            if( power_IsBatteryLow() == true )
                            {
                                RED_LED_ON();
                                OSA_TimeDelay( 10 );
                                RED_LED_OFF();
                            }
                            else
                            {
                                BLUE_LED_ON();
                                OSA_TimeDelay( 10 );
                                BLUE_LED_OFF();
                            }

                            break;
                        }

                        // do nothing
                        case POWER_CURRENT_MODE_SLEEP_TOTAL:
                        {
                            break;
                        }
                    } // switch( power_GetCurrentMode() )
                }
            }
        }
        
        // Finish with packet formation and push the packet.
        switch( isReadyToSend )
        {
            case SEND_YES:
            {
                switch( Extract( fmtOptions, DATA_FORMAT_TO ) )
                {
                    case DATA_FORMAT_TO_DEFAULT:
                        break;

                    case DATA_FORMAT_TO_BYTE:
                        sensorPacket.length *= sizeof( uint8_t );
                        break;
                        
                    case DATA_FORMAT_TO_mE:
                        sensorPacket.length *= sizeof( mE_t );
                        break;

                    case DATA_FORMAT_TO_FLOAT:
                        sensorPacket.length *= sizeof( float );
                        break;

                    default:
                        break;
                } // switch( Extract( ... ) )
                
                // Format data.
                Write( fmtOptions, DATA_TYPE, sensorToSend );
                sensor_FormatData(
                                   dataStart,
                                   ( void* )&( sensorPacket._data[0] ),
                                   fmtOptions
                                 );
                                 
                // Add trailer byte, denoting the packet end.
                sensorPacket._data[sensorPacket.length]
                    = gHostInterface_trailerByte;

                // Push data.
                sensor_PushData( &sensorPacket, pushTargets );
                
                // Wait.
                sensor_Wait();
                
                // Goto next sensor.
                NextSensor( sensorToSend );
                
                break;
            } // case SEND_YES
            
            case SEND_SKIP:
            {
                switch( power_GetCurrentMode() )
                {
                    case POWER_CURRENT_MODE_NORMAL:
                    case POWER_CURRENT_MODE_SLEEP_SHALLOW:
                        // Wait.
                        sensor_Wait();
                        break;

                    case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
                        power_SetSleepSource( POWER_SLEEP_SRC_SENSOR_TAG );
                        power_GoToSleep();
                        sensor_Wait();
                        break;

                    case POWER_CURRENT_MODE_SLEEP_TOTAL:
                        // Shouldn't be here.
                        break;
                } // switch( power_GetCurrentMode() )
                
                // Goto next sensor.
                NextSensor( sensorToSend );
                break;
            } // case SEND_SKIP
            
            case SEND_NO:
            {
                // Go to next sensor.
                NextSensor( sensorToSend );
                break;
            } // case SEND_NO
            
            case SEND_TRY_AGAIN:
            {
                // Try to read the same sensor again.
                break;
            } // case SEND_TRY_AGAIN
        } // switch( isReadyToSend )
    } // while( 1 )
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Creates the sensor task.
osa_status_t sensor_Init()
{
    osa_status_t osaStatus = kStatus_OSA_Success;
    
    // Create a mutex for controlling the access to toggling the task.
    osaStatus = OSA_MutexCreate( &taskAccessMutex );
    
    if( osaStatus != kStatus_OSA_Success )
    {
        error_catch( CATCH_MUTEX );
        return SENSOR_STATUS_ERROR;
    }
    
    // Create a semaphore for sinalising when to acquire new sensor readings.
    osaStatus = sensor_CreateBinSema( &sensor_sema );
    
    if( osaStatus != kStatus_OSA_Success )
    {
        error_catch( CATCH_SEMAPHORE );
        return SENSOR_STATUS_ERROR;
    }

    osaStatus = OSA_TaskCreate(
                                sensor_GetData,
                                "Sensor Task Get Data",
                                SENSOR_GET_DATA_STACK_SIZE,
                                NULL,
                                SENSOR_GET_DATA_PRIO,
                                (task_param_t)0,
                                false,
                                &hexiwear_sensor_TAG_handler
                              );

    if( osaStatus != kStatus_OSA_Success )
    {
        error_catch( CATCH_INIT );
        return SENSOR_STATUS_ERROR;
    }
    
    return osaStatus;
}

// Resets the packet counter, to trigger reading during the next sensor loop.
void sensor_ResetPacketcounter( packet_t packetToUpdate )
{
    packetSettings[ packetToUpdate ].counter = 1;
}

// Sets targets for the particular sensor packet.
void sensor_SetPacketTargets(
                                         packet_t packetToUpdate,
                              packet_pushTarget_t newPushTarget,
                                             bool shouldToggleTask
                            )
{
    packetSettings[ packetToUpdate ].targets = newPushTarget;
    sensor_ResetPacketcounter( packetToUpdate );

    // Update all counter initial values, according to new active packets.
    UpdatePacketCounters();

    if( shouldToggleTask == true )
    {
        sensor_ChangeTaskState( TASK_RESUME );
    }
}

// Retrieves a sensor's targets.
packet_pushTarget_t sensor_GetPacketTargets ( packet_t oldPushTargets )
{
    return packetSettings[ oldPushTargets ].targets;
}

// Assign polling delay in [ms] to the particular packet.
void sensor_RegisterPacketDelay(
                                 packet_t packetToUpdate,
                                 uint32_t delay_ms
                               )
{
    packetSettings[ packetToUpdate ].delay_ms = ( delay_ms == 0 ) ?
        packetSettings[ packetToUpdate ].defaultDelay_ms :
        delay_ms;
}

// Sets minimum delay for the sensor loop.
void sensor_SetMinimumDelay( uint32_t delay )
{
    sensor_minDelay_ms = ( delay == 0 ) ?
        SENSOR_DEFAULT_MINIMUM_DELAY_MS :
        delay;
}

// Backups all the sensors which have KW40 as its targets.
void sensor_SaveTargetsForKW40()
{
    packet_t pktIdx;
    
    for( pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
    {
        if( ( packetSettings[ pktIdx ].targets & PACKET_PUSH_KW40 ) != 0 )
        {
            packetSettings[ pktIdx ].targets &= ~PACKET_PUSH_KW40;
            KW40_backupList[ pktIdx ] = 1;
        }
    }
    
    // No need to pause the sensor task, since it will check for it itself
    // at the beginning of the loop.
    // Just check for potentially new counter values.
    
    UpdatePacketCounters();
}

// Restores all the sensors which have KW40 as its targets.
void sensor_RestoreTargetsForKW40()
{
    packet_t pktIdx;
    
    for( pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
    {
        if( KW40_backupList[ pktIdx ] == 1 )
        {
            packetSettings[ pktIdx ].targets |= PACKET_PUSH_KW40;
            KW40_backupList[ pktIdx ] = 0;
        }
    }
    
    // Potentially resume the sensor task.
    UpdatePacketCounters();
    sensor_ChangeTaskState( TASK_RESUME );
}

// Flushes the backup KW40 list.
void sensor_ResetTargetsForKW40()
{
    packet_t pktIdx;

    for( pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
    {
        KW40_backupList[ pktIdx ] = 0;
    }
}

// Checks if there are sensor packets with KW40 as their target.
bool sensor_CheckForKW40Targets()
{
    packet_t pktIdx;
    
    for( pktIdx = PACKET_ACC; pktIdx < PACKET_ALL; pktIdx++ )
    {
        if ( ( packetSettings[ pktIdx ].targets & PACKET_PUSH_KW40 ) != 0 )
        {
            return true;
        }
    }

    return false;
}

// Initiates the accelerometer.
void sensor_InitAcc()
{
    OSA_TimeDelay( 25 );
    FXOS_Init();

    sensorSettings_Activate( SENSOR_FXOS );
    if( FXOS_firstTime == true )
    {
        FXOS_firstTime = false;
    }
}

// Resets LED counter.
void sensor_ResetLEDIndicator()
{
    sensor_LEDCounter = 1;
}

// Turns LED off.
void sensor_ClearLEDIndicator()
{
    BLUE_LED_OFF();
}

// Stops waiting for semaphore.
void sensor_StopWait()
{
    OSA_SemaPost( &sensor_sema );
}

// Suspends the sensor task.
void sensor_Suspend()
{
    if( isSensorTaskActive == true )
    {
        isSensorTaskActive = false;
        timer_Stop( HEXIWEAR_TIMER_SENSOR );
        vTaskSuspend( hexiwear_sensor_TAG_handler );
    }
}

// Resumes the sensor task.
void sensor_Resume()
{
    if( isSensorTaskActive == false )
    {
        isSensorTaskActive = true;
        timer_Start( HEXIWEAR_TIMER_SENSOR );
        vTaskResume( hexiwear_sensor_TAG_handler );
    }
}