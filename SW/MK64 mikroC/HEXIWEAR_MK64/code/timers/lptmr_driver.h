// File: lptmr_driver.h

// Declarations of main functionalities in the lptmr driver module.

#ifndef _lptmr_driver_h_
#define _lptmr_driver_h_

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Type definitions.                                                          //
////////////////////////////////////////////////////////////////////////////////

// LPTMR pin selection, used in pulse counter mode.
typedef enum _lptmr_pin_select {
    kLptmrPinSelectInput0 = 0x0U, // Pulse counter input 0 is selected.
    kLptmrPinSelectInput1 = 0x1U, // Pulse counter input 1 is selected.
    kLptmrPinSelectInput2 = 0x2U, // Pulse counter input 2 is selected.
    kLptmrPinSelectInput3 = 0x3U  // Pulse counter input 3 is selected.
} lptmr_pin_select_t;

// LPTMR pin polarity, used in pulse counter mode.
typedef enum _lptmr_pin_polarity {
    // Pulse Counter input source is active-high.
    kLptmrPinPolarityActiveHigh = 0x0U,
    // Pulse Counter input source is active-low.
    kLptmrPinPolarityActiveLow  = 0x1U
} lptmr_pin_polarity_t;

// LPTMR timer mode selection.
typedef enum _lptmr_timer_mode {
    kLptmrTimerModeTimeCounter  = 0x0U, // Time Counter mode.
    kLptmrTimerModePulseCounter = 0x1U  // Pulse Counter mode.
} lptmr_timer_mode_t;

// LPTMR prescaler value.
typedef enum _lptmr_prescaler_value {
    // Prescaler divide 2, glitch filter invalid.
    kLptmrPrescalerDivide2                      = 0x0U,
    // Prescaler divide 4, glitch filter 2.
    kLptmrPrescalerDivide4GlitchFilter2         = 0x1U,
    // Prescaler divide 8, glitch filter 4.
    kLptmrPrescalerDivide8GlitchFilter4         = 0x2U,
    // Prescaler divide 16, glitch filter 8.
    kLptmrPrescalerDivide16GlitchFilter8        = 0x3U,
    // Prescaler divide 32, glitch filter 16.
    kLptmrPrescalerDivide32GlitchFilter16       = 0x4U,
    // Prescaler divide 64, glitch filter 32.
    kLptmrPrescalerDivide64GlitchFilter32       = 0x5U,
    // Prescaler divide 128, glitch filter 64.
    kLptmrPrescalerDivide128GlitchFilter64      = 0x6U,
    // Prescaler divide 256, glitch filter 128.
    kLptmrPrescalerDivide256GlitchFilter128     = 0x7U,
    // Prescaler divide 512, glitch filter 256.
    kLptmrPrescalerDivide512GlitchFilter256     = 0x8U,
    // Prescaler divide 1024, glitch filter 512.
    kLptmrPrescalerDivide1024GlitchFilter512    = 0x9U,
    // Prescaler divide 2048 glitch filter 1024.
    kLptmrPrescalerDivide2048GlitchFilter1024   = 0xAU,
    // Prescaler divide 4096, glitch filter 2048.
    kLptmrPrescalerDivide4096GlitchFilter2048   = 0xBU,
    // Prescaler divide 8192, glitch filter 4096.
    kLptmrPrescalerDivide8192GlitchFilter4096   = 0xCU,
    // Prescaler divide 16384, glitch filter 8192.
    kLptmrPrescalerDivide16384GlitchFilter8192  = 0xDU,
    // Prescaler divide 32768, glitch filter 16384.
    kLptmrPrescalerDivide32768GlitchFilter16384 = 0xEU,
    // Prescaler divide 65536, glitch filter 32768.
    kLptmrPrescalerDivide65536GlitchFilter32768 = 0xFU
} lptmr_prescaler_value_t;

// LPTMR prescaler/glitch filter clock select.
typedef enum _lptmr_prescaler_clock_select{
    kLptmrPrescalerClock0 = 0x0U, // Prescaler/glitch filter clock 0 selected.
    kLptmrPrescalerClock1 = 0x1U, // Prescaler/glitch filter clock 1 selected.
    kLptmrPrescalerClock2 = 0x2U, // Prescaler/glitch filter clock 2 selected.
    kLptmrPrescalerClock3 = 0x3U, // Prescaler/glitch filter clock 3 selected.
} lptmr_prescaler_clock_select_t;
 
// LPTMR status return codes.
typedef enum _lptmr_status {
    // Success.
    kStatus_LPTMR_Success                       = 0x0U,
    // LPTMR is not initialised yet.
    kStatus_LPTMR_NotInitlialized               = 0x1U,
    // Argument is NULL.
    kStatus_LPTMR_NullArgument                  = 0x2U,
    // Value 0 is not valid in pulse counter mode.
    kStatus_LPTMR_InvalidPrescalerValue         = 0x3U,
    // Function cannot be called in time counter mode.
    kStatus_LPTMR_InvalidInTimeCounterMode      = 0x4U,
    // Function cannot be called in pulse counter mode.
    kStatus_LPTMR_InvalidInPulseCounterMode     = 0x5U,
    // If LPTMR is enabled, compare register can only altered when TCF is set.
    kStatus_LPTMR_TcfNotSet                     = 0x6U,
    // Timer period time is too small for current clock source.
    kStatus_LPTMR_TimerPeriodUsTooSmall         = 0x7U,
    // Timer period time is too large for current clock source.
    kStatus_LPTMR_TimerPeriodUsTooLarge         = 0x8U
 } lptmr_status_t;
 
// LPTMR prescaler user configuration.
typedef struct LptmrPrescalerUserConfig {
    // Set this value will by pass the Prescaler or glitch filter.
    bool prescalerBypass;
    // Selects the clock to be used by the LPTMR prescaler/glitch filter.
    lptmr_prescaler_clock_select_t prescalerClockSelect;
    // Configures the size of the Prescaler in Time Counter mode
    // or width of the glitch filter in Pulse Counter mode.
    lptmr_prescaler_value_t prescalerValue;
} lptmr_prescaler_user_config_t;

// Define LPTMR working mode user configure.
typedef struct LptmrWorkingModeUserConfig {
    // Selects the LPTMR working mode: Timer or Pulse Counter.
    lptmr_timer_mode_t timerModeSelect;
    // Enables or disables the LPTMR free running.
    bool freeRunningEnable;
    // Specifies LPTMR pulse input pin polarity.
    lptmr_pin_polarity_t pinPolarity;
    // Specifies LPTMR pulse input pin select.
    lptmr_pin_select_t pinSelect;
} lptmr_working_mode_user_config_t;

// LPTMR clock source select
typedef enum _clock_lptmr_src_t
{
    kClockLptmrSrcMcgIrClk,        // MCGIRCLK
    kClockLptmrSrcLpoClk,          // LPO clock
    kClockLptmrSrcEr32kClk,        // ERCLK32K clock
    kClockLptmrSrcOsc0erClk,       // OSCERCLK clock
} clock_lptmr_src_t;

// Data structure to initialise the LPTMR.
typedef struct LptmrUserConfig {
    lptmr_timer_mode_t timerMode; // timer counter mode or pulse counter mode
    lptmr_pin_select_t pinSelect; // LPTMR pulse input pin select
    lptmr_pin_polarity_t pinPolarity; // LPTMR pulse input pin polarity
    bool freeRunningEnable; // enable free running
    bool  prescalerEnable; // means enable prescaler
    clock_lptmr_src_t prescalerClockSource; // LPTMR clock source
    lptmr_prescaler_value_t prescalerValue; // prescaler value
    bool isInterruptEnabled;  // timer interrupt 0-disable/1-enable
} lptmr_user_config_t;

// Defines a type of the user-defined callback function.
typedef void ( *lptmr_callback_t )();

// Internal driver state information.
typedef struct LptmrState {
    // Callback function that is executed in ISR.
    lptmr_callback_t userCallbackFunc;
    uint32_t prescalerClockHz;
} lptmr_state_t;

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// EXTAL0 clock
extern uint32_t g_xtal0ClkFreq;
// EXTAL RTC clock
extern uint32_t g_xtalRtcClkFreq;

////////////////////////////////////////////////////////////////////////////////
// Global function declarations.                                              //
////////////////////////////////////////////////////////////////////////////////

// Initialises the LPTMR driver.
lptmr_status_t LPTMR_DRV_Init( 
                               lptmr_state_t *userStatePtr,
                               const lptmr_user_config_t* userConfigPtr
                             );

// De-initialises the LPTMR driver.
lptmr_status_t LPTMR_DRV_Deinit();

// Starts the LPTMR counter.
lptmr_status_t LPTMR_DRV_Start();

// Stops the LPTMR counter.
lptmr_status_t LPTMR_DRV_Stop();

// Configures the LPTMR timer period in microseconds.
lptmr_status_t LPTMR_DRV_SetTimerPeriodUs( uint32_t us );

// Gets the current LPTMR time in microseconds.
uint32_t LPTMR_DRV_GetCurrentTimeUs();

// Sets the pulse period value.
lptmr_status_t LPTMR_DRV_SetPulsePeriodCount( uint32_t pulsePeriodCount );

// Gets the current pulse count.
uint32_t LPTMR_DRV_GetCurrentPulseCount();

// Installs the user-defined callback in the LPTMR module.
lptmr_status_t LPTMR_DRV_InstallCallback( lptmr_callback_t userCallback );

#endif