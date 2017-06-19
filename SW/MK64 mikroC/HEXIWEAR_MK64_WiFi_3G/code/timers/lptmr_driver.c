// File: lptmr_driver.c

// Definitions of main functionalities in the lptmr driver module.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <string.h>
#include "lptmr_driver.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definitions.                                                         //
////////////////////////////////////////////////////////////////////////////////

#define LPTMR_INSTANCE_COUNT (1U) // Number of instances of the LPTMR module.

#define CPU_LPO_CLK_HZ 1000U // Frequency of LPO.

////////////////////////////////////////////////////////////////////////////////
// Static variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

static lptmr_state_t *volatile lptmr_state_ptrs[LPTMR_INSTANCE_COUNT];

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// EXTAL0 clock
uint32_t g_xtal0ClkFreq;
// EXTAL RTC clock
uint32_t g_xtalRtcClkFreq;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Enables the LPTMR module operation.
static inline void LPTMR_HAL_Enable()
{
//    LPTMR0_CSR |= 0x01;
    TEN_LPTMR0_CSR_bit = 1;
}

// Disables the LPTMR module operation.
static inline void LPTMR_HAL_Disable()
{
    TEN_LPTMR0_CSR_bit = 0;
}

// Clears the LPTMR interrupt flag if set.
static inline void LPTMR_HAL_ClearIntFlag()
{
    TCF_LPTMR0_CSR_bit = 1;
}

// Returns the current LPTMR interrupt flag.
static inline bool LPTMR_HAL_IsIntPending()
{
    return (bool)TCF_LPTMR0_CSR_bit;
}

// Enables or disables the LPTMR interrupt.
static inline void LPTMR_HAL_SetIntCmd( bool enable )
{
    TIE_LPTMR0_CSR_bit = enable;
}

// Configures the LPTMR working mode.
void LPTMR_HAL_SetTimerWorkingMode( lptmr_working_mode_user_config_t timerMode )
{
    LPTMR0_CSR &= ~( 0x80 | 0x2 | 0x4 | 0x8 | 0x30 );
    
    TMS_bit = timerMode.timerModeSelect;
    TFC_bit = timerMode.freeRunningEnable;
    TPP_bit = timerMode.pinPolarity;
    TPS0_bit = timerMode.pinSelect & 0x01;
    TPS1_bit = ( timerMode.pinSelect & 0x02 ) >> 1;
}

// Sets the LPTMR prescaler mode.
void LPTMR_HAL_SetPrescalerMode(
    lptmr_prescaler_user_config_t prescaler_config )
{
    LPTMR0_PSR = ( ( prescaler_config.prescalerValue << 3 )
                 | ( prescaler_config.prescalerBypass << 2 )
                 | ( prescaler_config.prescalerClockSelect ) );
}

// Sets the LPTMR compare value.
static inline void LPTMR_HAL_SetCompareValue( uint32_t compareValue )
{
    LPTMR0_CMR = compareValue & 0xffff;
}

// Gets the LPTMR compare value.
static inline uint32_t LPTMR_HAL_GetCompareValue()
{
    return LPTMR0_CMR;
}

// Gets the LPTMR counter value.
uint32_t LPTMR_HAL_GetCounterValue()
{
    LPTMR0_CNR = 0x0000; // Must first write to the CNR with any value.
    return LPTMR0_CNR;
}

// Restores the LPTMR module to reset state.
void LPTMR_HAL_Init()
{
    lptmr_working_mode_user_config_t working_mode_config;
    lptmr_prescaler_user_config_t prescaler_config;

    LPTMR_HAL_Disable();
    LPTMR_HAL_ClearIntFlag();

    working_mode_config.timerModeSelect = kLptmrTimerModeTimeCounter;
    working_mode_config.freeRunningEnable = false;
    working_mode_config.pinPolarity = kLptmrPinPolarityActiveHigh;
    working_mode_config.pinSelect = kLptmrPinSelectInput0;
    LPTMR_HAL_SetTimerWorkingMode( working_mode_config );

    prescaler_config.prescalerValue = kLptmrPrescalerDivide2;
    prescaler_config.prescalerBypass = true;
    prescaler_config.prescalerClockSelect = kLptmrPrescalerClock0;
    LPTMR_HAL_SetPrescalerMode( prescaler_config );

    LPTMR_HAL_SetCompareValue( 0 );
    LPTMR_HAL_SetIntCmd( false );
}

// Returns clock frequency of lptmr.
uint32_t CLOCK_SYS_GetLptmrFreq( clock_lptmr_src_t lptmrSrc )
{
    uint32_t freq;
    uint8_t src;

    switch( lptmrSrc )
    {
        case kClockLptmrSrcMcgIrClk: // MCG out clock
            if( IRCLKEN_bit == 0 )
                freq = 0;
            else if ( IRCS_bit == 0 )
                freq = 32768;
            else
                freq = 4000000 >> ( ( MCG_SC >> 1 ) & 0x03 );
                
            break;
            
        case kClockLptmrSrcLpoClk: // LPO clock
            freq = CPU_LPO_CLK_HZ;
            break;
            
        case kClockLptmrSrcEr32kClk: // ERCLK32K clock
            src = SIM_SOPT1 >> 18;
            switch( src )
            {
                case 0: // OSC 32k clock
                    freq = ( 32768U == g_xtal0ClkFreq ) ? 32768U : 0U;
                    break;
                    
                case 2: // RTC 32k clock
                    freq = g_xtalRtcClkFreq;
                    break;
                    
                case 3: // LPO clock
                    freq = CPU_LPO_CLK_HZ;
                    break;
                    
                default:
                    freq = 0;
                    break;
            }
            break;
            
        case kClockLptmrSrcOsc0erClk: // OSCERCLK clock
            if( ERCLKEN_bit == 1 )
                freq = g_xtal0ClkFreq;
            else
                freq = 0;
            break;
            
        default:
            freq = 0;
            break;
    }

    return freq;
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Initialises the LPTMR driver.
lptmr_status_t LPTMR_DRV_Init(
                               lptmr_state_t *userStatePtr,
                               const lptmr_user_config_t* userConfigPtr
                             )
{
    lptmr_prescaler_user_config_t prescalerUserConfig;
    lptmr_working_mode_user_config_t workingModeUserConfig;
    
    if ((!userConfigPtr) || (!userStatePtr))
    {
        return kStatus_LPTMR_NullArgument;
    }
    
    // prescaler value 0 is invalid while working as pulse counter
    if ( ( userConfigPtr->timerMode == kLptmrTimerModePulseCounter ) &&
         ( userConfigPtr->prescalerEnable == true ) &&
         ( userConfigPtr->prescalerValue == kLptmrPrescalerDivide2) )
    {
        return kStatus_LPTMR_InvalidPrescalerValue;
    }
    
    // Enable clock for lptmr.
    LPTMR_bit = 1;
    
    // Disable lptmr and reset its logic.
    LPTMR_HAL_Disable();
    
    // LPTMR prescaler configure
    prescalerUserConfig.prescalerClockSelect =
        ( lptmr_prescaler_clock_select_t )userConfigPtr->prescalerClockSource;
    prescalerUserConfig.prescalerBypass =
        ( uint8_t )( userConfigPtr->prescalerEnable == false );
    prescalerUserConfig.prescalerValue = userConfigPtr->prescalerValue;
    LPTMR_HAL_SetPrescalerMode( prescalerUserConfig );

    // Working Mode configure
    workingModeUserConfig.timerModeSelect = userConfigPtr->timerMode;
    workingModeUserConfig.freeRunningEnable = userConfigPtr->freeRunningEnable;
    workingModeUserConfig.pinPolarity = userConfigPtr->pinPolarity;
    workingModeUserConfig.pinSelect = userConfigPtr->pinSelect;
    LPTMR_HAL_SetTimerWorkingMode( workingModeUserConfig );
    
    // Internal context
    lptmr_state_ptrs[0] = userStatePtr;

    userStatePtr->userCallbackFunc = 0;
    
    // LPTMR interrupt
    if( userConfigPtr->isInterruptEnabled )
    {
        LPTMR_HAL_SetIntCmd( true );
        NVIC_IntEnable( IVT_INT_LPTimer );
    }
    else
    {
        LPTMR_HAL_SetIntCmd( false );
        NVIC_IntDisable( IVT_INT_LPTimer );
    }
    
    // Caculate prescaler clock frequency.
    if( userConfigPtr->timerMode == kLptmrTimerModeTimeCounter )
    {
        userStatePtr->prescalerClockHz =
            CLOCK_SYS_GetLptmrFreq( userConfigPtr->prescalerClockSource );

        if( userConfigPtr->prescalerEnable )
        {
            userStatePtr->prescalerClockHz = ( userStatePtr->prescalerClockHz
                >> ( ( uint32_t )( userConfigPtr->prescalerValue + 1 ) ) );
        }
    }
}

// De-initialises the LPTMR driver.
lptmr_status_t LPTMR_DRV_Deinit()
{
    //Turn off lptmr hal.
    LPTMR_HAL_Disable();

    // Reset all register to reset value.
    LPTMR_HAL_Init();

    // Disable the interrupt.
    NVIC_IntDisable( IVT_INT_LPTimer );

    // Disable clock for lptmr.
    LPTMR_bit = 0;

    // Cleared state pointer.
    lptmr_state_ptrs[0] = 0;

    return kStatus_LPTMR_Success;
}

// Starts the LPTMR counter.
lptmr_status_t LPTMR_DRV_Start()
{
    LPTMR_HAL_Enable();

    return kStatus_LPTMR_Success;
}

// Stops the LPTMR counter.
lptmr_status_t LPTMR_DRV_Stop()
{
    LPTMR_HAL_Disable();

    return kStatus_LPTMR_Success;
}

// Configures the LPTMR timer period in microseconds.
lptmr_status_t LPTMR_DRV_SetTimerPeriodUs( uint32_t us )
{
    uint32_t tick_count;

    assert( us > 0 );
    
    if( lptmr_state_ptrs[0]->prescalerClockHz < 1000000U )
    {
        if( us < ( 1000000U / lptmr_state_ptrs[0]->prescalerClockHz ) )
        {
            return kStatus_LPTMR_TimerPeriodUsTooSmall;
        }
        else
        {
            tick_count =
                ( us / ( 1000000U / lptmr_state_ptrs[0]->prescalerClockHz ) );

            // CMR register is 16 bits.
            if( tick_count > 0xFFFFU )
            {
                return kStatus_LPTMR_TimerPeriodUsTooLarge;
            }
            else
            {
                LPTMR_HAL_SetCompareValue( tick_count );
            }
        }
    }
    else
    {
        tick_count =
            ( us * ( lptmr_state_ptrs[0]->prescalerClockHz / 1000000U ) );
            
        // CMR register is 16 bits.
        if( tick_count > 0xFFFFU )
        {
            return kStatus_LPTMR_TimerPeriodUsTooLarge;
        }
        else
        {
            LPTMR_HAL_SetCompareValue( tick_count );
        }
    }

    return kStatus_LPTMR_Success;
}

// Gets the current LPTMR time in microseconds.
uint32_t LPTMR_DRV_GetCurrentTimeUs()
{
    uint32_t us;

    if( lptmr_state_ptrs[0]->prescalerClockHz < 1000000U )
    {
        us = LPTMR_HAL_GetCounterValue() * 
            ( 1000000U / lptmr_state_ptrs[0]->prescalerClockHz );
    }
    else
    {
        us = LPTMR_HAL_GetCounterValue() /
            ( lptmr_state_ptrs[0]->prescalerClockHz / 1000000U );
    }

    return us;
}

// Sets the pulse period value.
lptmr_status_t LPTMR_DRV_SetPulsePeriodCount( uint32_t pulsePeriodCount )
{
    assert( pulsePeriodCount > 0 );
    
    LPTMR_HAL_SetCompareValue( pulsePeriodCount );

    return kStatus_LPTMR_Success;
}

// Gets the current pulse count.
uint32_t LPTMR_DRV_GetCurrentPulseCount()
{
    uint32_t count;

    count = LPTMR_HAL_GetCounterValue();

    return count;
}

// Installs the user-defined callback in the LPTMR module.
lptmr_status_t LPTMR_DRV_InstallCallback( lptmr_callback_t userCallback )
{
    if( !lptmr_state_ptrs[0] )
    {
        return kStatus_LPTMR_NotInitlialized;
    }
    // Fill callback function into state structure.
    lptmr_state_ptrs[0]->userCallbackFunc = userCallback;

    return kStatus_LPTMR_Success;
}

// Driver-defined ISR in the LPTMR module.
void LPTMR_DRV_IRQHandler() iv IVT_INT_LPTimer ics ICS_AUTO
{
    // Clear interrupt flag.
    LPTMR_HAL_ClearIntFlag();

    if( lptmr_state_ptrs[0] )
    {
        if( lptmr_state_ptrs[0]->userCallbackFunc )
        {
            // Execute user-defined callback function.
            ( *( lptmr_state_ptrs[0]->userCallbackFunc ) )();
        }
    }
}