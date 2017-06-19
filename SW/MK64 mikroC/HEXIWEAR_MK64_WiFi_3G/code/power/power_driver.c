// File: power_driver.c

// Definitions of main functionalities in the power module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "power.h"

#include "OLED_driver.h"
#include "OLED_info.h"

#include "sensor_driver.h"

#include "OSA.h"
#include "HEXIWEAR_info.h"

#include "timer_driver.h"
#include "rtc_driver.h"

#include "power_manager.h"

#include "screens_common.h"

#include "error.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define PWR_HTU_TSL_TurnON()                                                   \
    PWR_SENSORS_NF = 0;                                                        \
    OSA_TimeDelay( 50 );                                                       \
    isPowerActive_HTU_TSL = true
    
#define PWR_HTU_TSL_TurnOFF()                                                  \
    isPowerActive_HTU_TSL = false;                                             \
    PWR_SENSORS_NF = 1

#define PWR_HR_TurnON()                                                        \
    PWR_HR = 1;                                                                \
    OSA_TimeDelay( 50 );                                                       \
    isPowerActive_MAXIM = true
    
#define PWR_HR_TurnOFF()                                                       \
    isPowerActive_MAXIM = false;                                               \
    PWR_HR = 0

#define PWR_BATT_TurnON()                                                      \
    PWR_BAT_SENS = 0;                                                          \
    OSA_TimeDelay( 50 );                                                       \
    isPowerActive_BATTERY = true
    
#define PWR_BATT_TurnOFF()                                                     \
    isPowerActive_BATTERY = false;                                             \
    PWR_BAT_SENS = 1

#define PWR_OLED_TurnON()                                                      \
    PWR_OLED = 1;                                                              \
    OSA_TimeDelay( 50 );                                                       \
    isPowerActive_OLED = true

#define PWR_OLED_TurnOFF()                                                     \
    isPowerActive_OLED = false;                                                \
    PWR_OLED = 0

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// MCG mode definitions
typedef enum _mcg_modes {
    kMcgModeFEI    = 0x01 << 0U,   // FEI   - FLL Engaged Internal
    kMcgModeFBI    = 0x01 << 1U,   // FBI   - FLL Bypassed Internal
    kMcgModeBLPI   = 0x01 << 2U,   // BLPI  - Bypassed Low Power Internal
    kMcgModeFEE    = 0x01 << 3U,   // FEE   - FLL Engaged External
    kMcgModeFBE    = 0x01 << 4U,   // FBE   - FLL Bypassed External
    kMcgModeBLPE   = 0x01 << 5U,   // BLPE  - Bypassed Low Power External
    kMcgModePBE    = 0x01 << 6U,   // PBE   - PLL Bypassed Enternal
    kMcgModePEE    = 0x01 << 7U,   // PEE   - PLL Engaged External
    kMcgModeSTOP   = 0x01 << 8U,   // STOP  - Stop
    kMcgModeError  = 0x01 << 9U    // Unknown mode
} mcg_modes_t;

// MCG OSC Clock Select
typedef enum _mcg_oscsel_select
{
    kMcgOscselOsc,                 // Selects System Oscillator (OSCCLK)
    kMcgOscselRtc,                 // Selects 32 kHz RTC Oscillator
    kMcgOscselIrc                  // Selects 48 MHz IRC Oscillator
} mcg_oscsel_select_t;

// MCG PLLCS select
typedef enum _mcg_pll_clk_select
{
    kMcgPllClkSelPll0,             // PLL0 output clock is selected
    kMcgPllClkSelPll1,             // PLL1 output clock is selected
} mcg_pll_clk_select_t;

// MCG clock mode status
typedef enum _mcg_clkout_stat
{
    kMcgClkOutStatFll,      // Output of the FLL is selected (reset default)
    kMcgClkOutStatInternal, // Internal reference clock is selected
    kMcgClkOutStatExternal, // External reference clock is selected
    kMcgClkOutStatPll       // Output of the PLL is selected
} mcg_clkout_stat_t;

// MCG internal reference clock source select
typedef enum _mcg_fll_src
{
    kMcgFllSrcExternal,     // External reference clock is selected
    kMcgFllSrcInternal      // The slow internal reference clock is selected
} mcg_fll_src_t;

// MCG DCO range select
typedef enum _mcg_dco_range_select
{
    kMcgDcoRangeSelLow,          // Low frequency range
    kMcgDcoRangeSelMid,          // Mid frequency range
    kMcgDcoRangeSelMidHigh,      // Mid-High frequency range
    kMcgDcoRangeSelHigh          // High frequency range
} mcg_dco_range_select_t;

// MCG DCO Maximum Frequency with 32.768 kHz Reference
typedef enum _mcg_dmx32_select
{
    kMcgDmx32Default, // DCO has a default range of 25%
    kMcgDmx32Fine     // DCO is fine-tuned for maximum frequency
                      // with 32.768 kHz reference
} mcg_dmx32_select_t;

// MCGOUT clock source.
typedef enum _mcg_clkout_src
{
    kMcgClkOutSrcOut,      // Output of the FLL is selected (reset default)
    kMcgClkOutSrcInternal, // Internal reference clock is selected
    kMcgClkOutSrcExternal  // External reference clock is selected
} mcg_clkout_src_t;

// MCG internal reference clock select.
typedef enum _mcg_irc_mode
{
    kMcgIrcSlow,        // Slow internal reference clock selected
    kMcgIrcFast         // Fast internal reference clock selected
} mcg_irc_mode_t;

// SIM PLLFLLSEL clock source select.
typedef enum _clock_pllfll_sel
{
    kClockPllFllSelFll    = 0U,    // Fll clock
    kClockPllFllSelPll    = 1U,    // Pll0 clock
    kClockPllFllSelIrc48M = 3U     // IRC48MCLK
} clock_pllfll_sel_t;

// SIM external reference clock source select (OSC32KSEL).
typedef enum _clock_er32k_src
{
    kClockEr32kSrcOsc0 = 0U, // OSC0 clock (OSC032KCLK).
    kClockEr32kSrcRtc  = 2U, // RTC 32k clock .
    kClockEr32kSrcLpo  = 3U, // LPO clock.
} clock_er32k_src_t;

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////
 
static sbit PWR_SENSORS_NF at PTB_PDOR.B12;
static sbit PWR_HR         at PTA_PDOR.B29;
static sbit PWR_BAT_SENS   at PTC_PDOR.B14;
static sbit PWR_OLED       at PTC_PDOR.B13;
static sbit KW40_RST       at PTB_PDOR.B23;
static sbit KW40_GPIO      at PTE_PDOR.B26;
static sbit KW40_WU        at PTD_PDOR.B14;

static semaphore_t power_sema;
static semaphore_t power_wakeSrcSema;
static semaphore_t power_STSema;

static bool isBatteryLow = false;

static bool isActive_powerSave = true;

static power_current_mode_t currentPowerMode = POWER_CURRENT_MODE_NORMAL;

static power_sleep_mode_t selectedSleepMode = POWER_SLEEP_MODE_TOTAL;

// Status flags.
static bool isPowerActive_OLED    = false;
static bool isPowerActive_HTU_TSL = false;
static bool isPowerActive_BATTERY = false;
static bool isPowerActive_MAXIM   = false;

// Flags to track who puts the MCU to sleep and wakes it up.

static power_sleep_src_t currentSleepSrc = POWER_SLEEP_SRC_NONE;

static power_wake_src_t currentWakeSrc = POWER_WAKE_SRC_NONE;

static bool isActive_Sleep = false;

static task_handler_t power_handler;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Creates a semaphore for power module purposes.
static osa_status_t power_CreateBinSema(semaphore_t* semaphore )
{
    *semaphore = xSemaphoreCreateCounting( 0x1, 0 );
    
    if( *semaphore == NULL )
        return kStatus_OSA_Error;

    return kStatus_OSA_Success;
}

// Triggers the power task by filling the semaphore that the task is blocked on.
static void power_TriggerTask()
{
    OSA_SemaPost( &power_sema );
}

// Gets current mcg mode.
static mcg_modes_t power_GetMcgMode()
{
    mcg_modes_t               mode   = kMcgModeError;
    mcg_clkout_stat_t         clkst  = MCG_Sbits.CLKST;
    mcg_fll_src_t             irefst = IREFST_bit;
    uint8_t                   lp     = LP_bit;
    bool                      pllst  = PLLST_bit;
    
    switch( clkst )
    {
        case kMcgClkOutStatFll:
        if( !pllst )
        {
            if( irefst == kMcgFllSrcExternal )
            {
                mode = kMcgModeFEE;
            }
            else
            {
                mode = kMcgModeFEI;
            }
        }
        break;
        
        case kMcgClkOutStatInternal:
            if( ( irefst == kMcgFllSrcInternal ) && ( !pllst ) )
            {
                if( lp == 0U )
                {
                    mode = kMcgModeFBI;
                }
                else
                {
                    mode = kMcgModeBLPI;
                }
            }
            break;
        
        case kMcgClkOutStatExternal:
            if( irefst == kMcgFllSrcExternal )
            {
                if( lp == 0U )
                {
                    if( pllst )
                    {
                        mode = kMcgModePBE;
                    }
                    else
                    {
                        mode = kMcgModeFBE;
                    }
                }
                else
                {
                    mode = kMcgModeBLPE;
                }
            }
            break;
        
        case kMcgClkOutStatPll:
            if( ( kMcgFllSrcExternal == irefst ) && pllst )
            {
                mode = kMcgModePEE;
            }
            break;
        
        default:
            break;
    }
    
    return mode;
}

// Sets fbe mode.
static void power_SetFbeMode( mcg_modes_t mode, uint32_t *outClkFreq )
{
    uint32_t extFreq;
    uint32_t coreClk;
    
    extFreq = g_xtal0ClkFreq;
    
    // Set PLLS.
    PLLS_bit = 0;
    while( PLLST_bit != 0 ) {}
    
    // Set LP bit to enable the FLL.
    LP_bit = 0;
    
    if( mode != kMcgModeFEE )
        MCG_C7bits.OSCSEL = kMcgOscselOsc;

    // Set CLKS and IREFS.
    CLKS0_MCG_C1_bit = 0;
    CLKS1_MCG_C1_bit = 1;
    FRDIV0_bit = 0;
    FRDIV1_bit = 0;
    FRDIV2_bit = 0;
    IREFS_bit = kMcgFllSrcExternal;
    
    // Wait for Reference clock Status bit to clear.
    while( IREFST_bit != kMcgFllSrcExternal ) {}

    if( mode == kMcgModeFEE )
    {
        MCG_C7bits.OSCSEL = kMcgOscselOsc;
    }
    
    if( EREFS_bit != 0 )
    {
        while( !OSCINIT0 ) {}
    }
    
    // Set DRST_DRS and DMX32.
    DMX32_bit = kMcgDmx32Default;
    MCG_C4bits.DRST_DRS = kMcgDcoRangeSelLow;

    // Wait for DRS to be set.
    while( MCG_C4bits.DRST_DRS != kMcgDcoRangeSelLow ) {}
    
    // Wait for clock status bits to show clock source is ext ref clk.
    while( MCG_Sbits.CLKST != kMcgClkOutStatExternal) {}
    
    // Wait for fll stable time.
    coreClk = 120000000;
    // Delay 1 ms.
    while( coreClk-- )
    {
        asm NOP;
    }

    // MCGOUT frequency equals external clock frequency.
    *outClkFreq = extFreq;
}


// Sets pbe mode.
static void power_SetPbeMode( mcg_modes_t mode, uint32_t *outClkFreq )
{
    uint32_t extFreq, pllRefFreq;
    
    extFreq = g_xtal0ClkFreq;
    
    if( extFreq == 0U )
        return;
        
    // Check whether PRDIV value is OK.
    pllRefFreq = extFreq / ( 2U + 1);

    if( ( pllRefFreq < 2000000 ) || ( pllRefFreq > 4000000 ) )
        return;
    
    // Set LP bit to enable the FLL.
    LP_bit = 0;
    
    // Change to use external clock first.
//    MCG_C1bits.CLKS = kMcgClkOutSrcExternal;
//    MCG_C1 |= kMcgClkOutSrcExternal
    CLKS0_MCG_C1_bit = 0;
    CLKS1_MCG_C1_bit = 1;


    // Wait for clock status bits to update.
    while( MCG_Sbits.CLKST != kMcgClkOutStatExternal) {}
    
    MCG_C7bits.OSCSEL = kMcgOscselOsc;
    if( EREFS_bit != 0 )
    {
        while( OSCINIT0_bit == 0 ){}
    }

    // Disable PLL first, then configure PLL.
    PLLCLKEN0_bit = 0;
    PLLS_bit = 0;

    // Wait for PLLST status bit to clear.
    while( PLLST_bit != 0 ) {}

    MCG_C5bits.PRDIV0 = 2;

    MCG_C6bits.VDIV0 = 6;

    // Enable PLL.
    PLLS_bit = 1;

    // Wait for PLLST status bit to set.
    while( PLLST_bit != 1 ) {}

    // Wait for LOCK bit to set.
    while( LOCK0_bit == 0 ) {}
    
    *outClkFreq = extFreq;
}

// Sets mcg mode.
static void power_SetMcgMode()
{
    uint32_t outClkFreq;
    // Current mode is only used for PEE mode transition.
    mcg_modes_t curMode;  // Current MCG mode.
    
    mcg_oscsel_select_t oscsel = kMcgOscselOsc;
    
    mcg_pll_clk_select_t pllcs = kMcgPllClkSelPll0;
    
    curMode = power_GetMcgMode();
    
    // If current mode is FEI/FEE/BLPI, then switch to FBE mode first.
    // If current mode is PEE mode, which means need to reconfigure PLL,
    // first switch to PBE mode and configure PLL, then switch to PEE.
    
    if( curMode != kMcgModePEE )
    {
        // Disalbe low power mode.
        LP_bit = 0;

        // Change to FBE mode.
        power_SetFbeMode( curMode, &outClkFreq );
    }

    // Change to PBE mode.
    power_SetPbeMode( curMode, &outClkFreq );

    // Set CLKS to enter PEE mode.
    MCG_C1bits.CLKS = kMcgClkOutSrcOut;
    while( MCG_Sbits.CLKST != kMcgClkOutStatPll) {}
   
    //Enable MCGIRCLK.
    IRCLKEN_bit = 1;
    IREFSTEN_bit = 0;

    // Configure MCGIRCLK.
    IRCS_bit = kMcgIrcSlow;
    while( IRCST_bit != kMcgIrcSlow ) {}
    
     // Enable PLL0.
     MCG_C6bits.VDIV0 = 6;
     MCG_C5bits.PRDIV0 = 2;
     PLLSTEN0_bit = 0;
     PLLCLKEN0_bit = 1;
     while( LOCK0_bit == 0 ) {} // Wait until locked.
}

// Sets sim configuration.
static void power_SetSimConfiguration()
{
    SIM_CLKDIV1 = 0x01440000;
    
    SIM_SOPT2bits.PLLFLLSEL = kClockPllFllSelPll;
    
    SIM_SOPT1bits.OSC32KSEL = kClockEr32kSrcRtc;
}

// Sets oscer configuration.
static void power_SetOscerConfiguration()
{
    ERCLKEN_bit = 1;
    
    EREFSTEN_bit = 0;
}

// Updates clock configuration and switches clock mode.
static void power_updateClockConfiguration()
{
    OSA_EnterCritical( kCriticalDisableInt );
    
    // Set outdiv for safe output clock frequency.
    SIM_CLKDIV1 = 0x01240000;

    // Set MCG mode.
    power_SetMcgMode();

    // Set SIM setting.
    power_SetSimConfiguration();

    // Set OSCERCLK setting.
    power_SetOscerConfiguration();
    
    OSA_ExitCritical( kCriticalDisableInt );
}

// Puts the MCU to sleep.
static power_status_t power_PutMCUToSleep()
{
    bool sensorTimerState = false;
    
    switch( currentPowerMode )
    {
        case POWER_CURRENT_MODE_NORMAL:
        case POWER_CURRENT_MODE_SLEEP_SHALLOW:
            // Shouldn't happen.
            error_catch( CATCH_POWER );
            break;

        case POWER_CURRENT_MODE_SLEEP_TOTAL:
            // Check sensor timer's state to remember for later.
            sensorTimerState = timer_IsActive( HEXIWEAR_TIMER_SENSOR );
            if( sensorTimerState == true )
                timer_Stop( HEXIWEAR_TIMER_SENSOR );
            break;

        case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
            // Do nothing.
            break;
    }
    
    // Set the wake-up source to none, as it will be set
    // by invoking the wake-up function in the appropriate interrupt handler.
    if( currentPowerMode != POWER_CURRENT_MODE_NORMAL )
    {
        // put MCU to sleep (VLPS)
        POWER_SYS_SetMode( 1, kPowerManagerPolicyAgreement );
        power_updateClockConfiguration();
        
        OSA_TimeDelay( 10 );
    }
    
    // MCU is now woken up, undo all the power-save changes from above.
    switch( currentPowerMode )
    {
        case POWER_CURRENT_MODE_NORMAL:
            RTC_EnableAlarm();
            RTC_UpdateAlarm();
            power_TurnScreenOn();
            
            // If the timer was enabled before, enable it.
            if( sensorTimerState == true )
                timer_Start( HEXIWEAR_TIMER_SENSOR );

            break;

        case POWER_CURRENT_MODE_SLEEP_SHALLOW:
            // Shouldn't happen.
            error_catch( CATCH_POWER );
            break;

        case POWER_CURRENT_MODE_SLEEP_TOTAL:
            break;

        case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
            break;
    }
    
    return POWER_STATUS_SUCCESS;
}

// Puts HEXIWEAR to sleep.
static power_status_t power_Sleep()
{
    power_status_t sleepStatus = POWER_STATUS_SUCCESS;
    
    switch( selectedSleepMode )
    {
        // In case of shallow sleep mode just turn off the OLED.
        case POWER_SLEEP_MODE_SHALLOW:
            // Turn OLED off.
            power_TurnScreenOff();

            currentPowerMode = POWER_CURRENT_MODE_SLEEP_SHALLOW;
            return POWER_STATUS_SUCCESS;

        // If the sleep mode has been initiated by RTC, go to total sleep:
        // shutdown sensors, screen and put the core to deep sleep.
        case POWER_SLEEP_MODE_TOTAL:
            if( isPowerActive_MAXIM == true )
                PWR_HR_TurnOFF();
            if( isPowerActive_HTU_TSL == true )
                PWR_HTU_TSL_TurnOFF();
            if( isPowerActive_BATTERY )
                PWR_BATT_TurnOFF();

            // Turn OLED off.
            power_TurnScreenOff();

            currentPowerMode = POWER_CURRENT_MODE_SLEEP_TOTAL;
            break;

        // If the sleep mode has been requested while in sensor tag mode,
        // shutdown the screen initially and then go to sleep.
        case POWER_SLEEP_MODE_SENSOR_TAG:
            currentPowerMode = POWER_CURRENT_MODE_SLEEP_SENSOR_TAG;
            power_TurnScreenOff();
            break;
    }
    
    // Go to sleep.
    if( power_PutMCUToSleep() != POWER_STATUS_SUCCESS )
    {
        // If going to sleep didn't work, act like the user woke up the MCU.
        RTC_UpdateAlarm();
        power_TurnScreenOn();
        
        currentWakeSrc   = POWER_WAKE_SRC_USER;
        currentPowerMode = POWER_CURRENT_MODE_NORMAL;
        sleepStatus      = POWER_STATUS_INIT_ERROR;
    }
    
    while( currentWakeSrc == POWER_WAKE_SRC_NONE ) {}
    
    // Let's see what's next, since it depends
    // on the peripheral that has awoken the MCU.
    switch( currentWakeSrc )
    {
        case POWER_WAKE_SRC_NONE:
            // shouldn't happen
            break;

        case POWER_WAKE_SRC_USER:
        {
            switch( power_GetSleepMode() )
            {
                case POWER_SLEEP_MODE_SHALLOW:
                    break;

                // If we're about to leave the total sleep mode,
                // turn sensors' power supplies on,
                // if they were turned off before entering.
                case POWER_SLEEP_MODE_TOTAL:
                    currentPowerMode = POWER_CURRENT_MODE_NORMAL;
                    
                    if( isPowerActive_MAXIM == true )
                    {
                        PWR_HR_TurnON();
                        MAXIM_Init();
                    }
                    if( isPowerActive_HTU_TSL == true )
                    {
                        PWR_HTU_TSL_TurnON();
                        HTU_Init();
                    }
                    if( isPowerActive_BATTERY == true )
                        PWR_BATT_TurnON();
                        
                    break;

                case POWER_SLEEP_MODE_SENSOR_TAG:
                    break;
            } // switch( power_GetSleepMode() )
            
            break;
        } // case POWER_WAKE_SRC_USER:
        
        case POWER_WAKE_SRC_SENSOR_TIMER:
        {
            // Do nothing, as we'll re-enter the sleep soon enough.
            break;
        }
    }
    
    return sleepStatus;
}

// Task in charge of putting HEXIWEAR to sleep.
static void power_Task( void* param )
{
    osa_status_t status;

    while( 1 )
    {
        status = OSA_SemaWait( &power_sema, OSA_WAIT_FOREVER );
        
        if( status == kStatus_OSA_Success )
        {
            while( power_Sleep() != POWER_STATUS_SUCCESS )
            {
                OSA_TimeDelay( 100 );
            }
        }
        else
        {
            error_catch( CATCH_SEMAPHORE );
        }
    }
}

// Port C interrupt handler routine.
void PortCIntHandler() iv IVT_INT_PORTC ics ICS_AUTO
{
    PORTC_ISFR = 0xFFFFFFFF;

    watch_CheckBatteryStatus();

    RTC_UpdateAlarm();
    
    if( FXOS_IsTapEnabled() )
    {
        switch ( power_GetCurrentMode() )
        {
            // regular work mode, do nothing
            case POWER_CURRENT_MODE_NORMAL:
            {
                break;
            }
            
            // if we were in shallow sleep mode, just turn the OLED ON
            case POWER_CURRENT_MODE_SLEEP_SHALLOW:
            {
                HostInterface_SetWakingTouch();
                power_SetCurrentMode( POWER_CURRENT_MODE_NORMAL );
                break;
            }

            case POWER_CURRENT_MODE_SLEEP_TOTAL:
            {
                HostInterface_SetWakingTouch();
                power_SetCurrentMode( POWER_CURRENT_MODE_NORMAL );

                if( power_SetWakeSource( POWER_WAKE_SRC_USER )
                    != POWER_STATUS_SUCCESS )
                {
                    asm NOP;
                }
                break;
            }

            // special consideration is also required for
            // the sensor tag sleep mode, since we might not be
            // actually sleeping when UART interrupt occurs
            case POWER_CURRENT_MODE_SLEEP_SENSOR_TAG:
            {
                HostInterface_SetWakingTouch();
                power_SetCurrentMode( POWER_CURRENT_MODE_NORMAL );

                if ( power_SetWakeSource( POWER_WAKE_SRC_USER )
                    == POWER_STATUS_SUCCESS )
                {
                }
                else
                {
                    asm NOP;
                }
                break;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the power task and relevant power objects.
power_status_t power_Init()
{
    osa_status_t status;

    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_12 ); // PWR_SENSORS_NF
    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_29 ); // PWR_HR
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_14 ); // PWR_BAT_SENS
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_13 ); // PWR_OLED
    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_23 ); // KW40_RST
    GPIO_Digital_Output( &PTE_PDOR, _GPIO_PINMASK_26 ); // KW40_GPIO
    GPIO_Digital_Output( &PTD_PDOR, _GPIO_PINMASK_14 ); // KW40_WU
    KW40_RST = 1;
    OSA_TimeDelay( 10 );
    KW40_RST = 1;

    if( OSA_SemaCreate( &power_sema, 0 ) != kStatus_OSA_Success )
        return POWER_STATUS_ERROR;

    if( power_CreateBinSema( &power_wakeSrcSema ) != kStatus_OSA_Success )
        return POWER_STATUS_ERROR;

    if( power_CreateBinSema( &power_STSema ) != kStatus_OSA_Success )
        return POWER_STATUS_ERROR;

    status = OSA_TaskCreate(
                             power_Task,
                             "Active power management",
                             POWER_STACK_SIZE,
                             NULL,
                             HEXIWEAR_STARTUP_PRIO,
                             NULL,
                             false,
                             &power_handler
                           );

    if( status != kStatus_OSA_Success )
        return POWER_STATUS_ERROR;

    return POWER_STATUS_SUCCESS;
}

// Activates/deactivates power supplies for sensors.
void power_SensorManagement()
{
    // humidity & ambient light
    if( ( sensor_GetPacketTargets( PACKET_HUM )
        | sensor_GetPacketTargets( PACKET_TEMP )
        | sensor_GetPacketTargets( PACKET_LUX ) ) != PACKET_PUSH_NONE )
    {
        if( isPowerActive_HTU_TSL == false )
            PWR_HTU_TSL_TurnON();
    }
    else
    {
        if( isPowerActive_HTU_TSL == true )
            PWR_HTU_TSL_TurnOFF();
    }
    
    // MAXIM
    if( sensor_GetPacketTargets( PACKET_HR ) != PACKET_PUSH_NONE )
    {
        if( isPowerActive_MAXIM == false )
            PWR_HR_TurnON();
    }
    else
    {
        if( isPowerActive_MAXIM == true )
            PWR_HR_TurnOFF();
    }
    
    // battery reading
    if( sensor_GetPacketTargets( PACKET_BAT ) != PACKET_PUSH_NONE )
    {
        if( isPowerActive_BATTERY == false )
            PWR_BATT_TurnON();
    }
    else
    {
        if( isPowerActive_BATTERY == true )
            PWR_BATT_TurnOFF();
    }
}

// Turns the selected peripheral ON.
power_status_t power_TurnOn( power_peripheral_t peripheral )
{
    switch( peripheral )
    {
        case POWER_OLED:
            PWR_OLED_TurnON();
            break;

        default:
            break;
    }
    
    return POWER_STATUS_SUCCESS;
}

// Turns the selected peripheral OFF.
power_status_t power_TurnOff( power_peripheral_t peripheral )
{
    switch( peripheral )
    {
        case POWER_OLED:
            PWR_OLED_TurnOFF();
            break;

        default:
            break;
    }

    return POWER_STATUS_SUCCESS;
}

// Sets BLE_RST pin to 0 and then releases it.
void power_ResetKW40()
{
    KW40_RST = 0;
    OSA_TimeDelay( 10 );
    KW40_RST = 1;
    OSA_TimeDelay( 200 );
}

// Returns power flags.
bool power_IsActive( power_peripheral_t peripheral )
{
    switch( peripheral )
    {
        case POWER_OLED:
            return isPowerActive_OLED;
            
        case POWER_HTU_TSL:
            return isPowerActive_HTU_TSL;

        case POWER_MAXIM:
            return isPowerActive_MAXIM;

        case POWER_BATTERY:
            return isPowerActive_BATTERY;

        default:
            return false;
    }
}

// Enables the power save feature: OLED and current sensor subscriptions.
void power_EnablePowerSave()
{
    RTC_EnableAlarm();
    isActive_powerSave = true;
}

// Disables the power save feature: OLED and current sensor subscriptions.
void power_DisablePowerSave()
{
    isActive_powerSave = false;
    RTC_DisableAlarm();
}

// Sets sleep source.
void power_SetSleepSource( power_sleep_src_t sleepSrc )
{
    currentSleepSrc = sleepSrc;
}

// Gets sleep source.
power_sleep_src_t power_GetSleepSource()
{
    return currentSleepSrc;
}

// Sets wakeup source.
power_status_t power_SetWakeSource( power_wake_src_t wakeSrc )
{
    if( OSA_SemaWait( &power_wakeSrcSema, 0 ) != kStatus_OSA_Success )
    {
        return POWER_STATUS_ERROR;
    }
    
    currentWakeSrc = wakeSrc;
    return POWER_STATUS_SUCCESS;
}

// Gets wakeup source.
power_wake_src_t power_GetWakeSource()
{
    return currentWakeSrc;
}

// Check if this was the touch that woke the MCU.
bool power_HasJustExitSleep()
{
    return isActive_Sleep;
}

// Puts HEXIWEAR to sleep.
void power_GoToSleep()
{
    if( isActive_powerSave == true )
        power_TriggerTask();
}

// Sets current HEXIWEAR mode.
void power_SetCurrentMode( power_current_mode_t newMode )
{
    if( isActive_powerSave == true )
        currentPowerMode = newMode;
}

// Gets current HEXIWEAR mode.
power_current_mode_t power_GetCurrentMode()
{
    return currentPowerMode;
}

// Sets new power mode.
void power_SetSleepMode( power_sleep_mode_t newMode )
{
    if( isActive_powerSave == true )
        selectedSleepMode = newMode;
}

// Gets currently selected sleep mode.
power_sleep_mode_t power_GetSleepMode()
{
    return selectedSleepMode;
}

// Turns the screen off by sending the command
// and turning off the power supply.
void power_TurnScreenOff()
{
    if( isPowerActive_OLED == true )
    {
        while( OLED_SendCmd( OLED_CMD_DISPLAYOFF, FIRST_BYTE )
            != OLED_STATUS_SUCCESS ) {}

        PWR_OLED_TurnOFF();
        
        KW40_GPIO = 0;
    }
}

// Turn the screen on by switching on the power supply
// and sending the command.
void power_TurnScreenOn()
{
    if( isPowerActive_OLED == false )
    {
        KW40_WU = !KW40_WU;
        OSA_TimeDelay( 10 );
        KW40_GPIO = 1;
        
        PWR_OLED_TurnON();
        
        while( OLED_SendCmd( OLED_CMD_DISPLAYON, FIRST_BYTE )
            != OLED_STATUS_SUCCESS ) {}
    }
}

// Fills the semaphore for wake-up sources to take.
power_status_t power_PostToSTSema()
{
    if( OSA_SemaPost( &power_STSema ) != kStatus_OSA_Success )
        return POWER_STATUS_ERROR;

    return POWER_STATUS_SUCCESS;
}

// Takes semaphore to signalize the wake-up happened.
power_status_t power_TakeFromSTSema()
{
    if( OSA_SemaWait( &power_STSema, 0 ) != kStatus_OSA_Success )
        return POWER_STATUS_ERROR;

    return POWER_STATUS_SUCCESS;
}

// Sends sleep ON/OFF packet to KW40.
power_status_t power_AlertKW40( power_sleepState_t sleepState )
{
    hostInterface_packet_t sleepPacket;
    osa_status_t txStatus;
    
    sleepPacket.length = 0;
    sleepPacket._data[0] = gHostInterface_trailerByte;
    
    switch( sleepState )
    {
        case POWER_SLEEP_STATE_ON:
            sleepPacket.type = packetType_sleepON;
            break;

        case POWER_SLEEP_STATE_OFF:
            sleepPacket.type = packetType_sleepOFF;
            break;
    }
    
    txStatus = HostInterface_TxQueueMsgPut( &sleepPacket, false );
    
    if( txStatus != kStatus_OSA_Success )
    {
        error_catch( CATCH_QUEUE );
        return POWER_STATUS_ERROR;
    }
    
    return POWER_STATUS_SUCCESS;
}

// Called before entering sleep mode.
power_manager_error_code_t power_CallBeforeSleep()
{
    currentWakeSrc = POWER_WAKE_SRC_NONE;
    
    // Enable UART edge interrupt circuit.
    UART4_BDHbits.RXEDGIE = 1;
    
    // Post to semaphore to make it available to interrupts.
    OSA_SemaPost( &power_wakeSrcSema );
    
    return kPowerManagerSuccess;
}

// Called after exiting sleep mode.
power_manager_error_code_t power_CallAfterSleep()
{
    // Disable UART edge interrupt circuit.
    UART4_BDHbits.RXEDGIE = 0;
//    UART4_BDH &= 0xBF;
    
    return kPowerManagerSuccess;
}

// Checks for battery status.
bool power_IsBatteryLow()
{
    return isBatteryLow;
}

// Sets battery status as low.
void power_SetBatteryLow()
{
    isBatteryLow = true;
}

// Unsets battery status as low.
void power_UnsetBatteryLow()
{
    isBatteryLow = false;
}