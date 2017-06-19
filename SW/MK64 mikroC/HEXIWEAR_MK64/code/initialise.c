// File: initialise.c

// Definitions of functionalities for system initialisation.

////////////////////////////////////////////////////////////////////////////////
// Header file inclusions.                                                    //
////////////////////////////////////////////////////////////////////////////////

#include "initialise.h"

#include "lptmr_driver.h"
#include "timer_driver.h"
#include "DMA_Controller.h"
#include "OLED_SPI.h"

////////////////////////////////////////////////////////////////////////////////
// Global variable definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Start of the dynamic memory heap.
const unsigned long HEAP_START = 0x20000000;
// Size of the dynamic memory heap.
const unsigned long HEAP_SIZE  = 0x00028000;

////////////////////////////////////////////////////////////////////////////////
// Static function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

/* void ADC0_IRQHandler() iv IVT_INT_ADC0 ics ICS_AUTO
{

} */

// Initailises hardware.
static void hardware_init()
{
    // Enable clock for PORTs.
    PORTA_bit = 1;
    PORTB_bit = 1;
    PORTC_bit = 1;
    PORTD_bit = 1;
    PORTE_bit = 1;
  
    // Setup board clock source.
    // Value of the external crystal or oscillator clock frequency
    // of the system oscillator (OSC) in Hz.
    g_xtal0ClkFreq = 12000000U;
    // Value of the external 32k crystal or oscillator clock frequency
    // of the RTC in Hz.
    g_xtalRtcClkFreq = 32768U;

    GPIO_Digital_Output( &PTB_PDOR, _GPIO_PINMASK_12 ); // PWR_SENSORS_NF
    PTB_PDOR.B12 = 0;

    GPIO_Digital_Output( &PTA_PDOR, _GPIO_PINMASK_29 ); // PWR_HR
    PTA_PDOR.B29 = 1;
    
    GPIO_Digital_Output( &PTD_PDOR, _GPIO_PINMASK_11 ); // Accel_RST

    GPIO_Digital_Output( &PTD_PDOR, _GPIO_PINMASK_14 ); // KW40_WU
    
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_8 ); // RED_LED
    GPIO_Digital_Output( &PTD_PDOR, _GPIO_PINMASK_0 ); // GREEN_LED
    GPIO_Digital_Output( &PTC_PDOR, _GPIO_PINMASK_9 ); // BLUE_LED
    PTC_PDOR.B8 = 1;
    PTD_PDOR.B0 = 1;
    PTC_PDOR.B9 = 1;

    PORTB_PCR21bits.MUX = 2; // SPI2_SCK
    PORTB_PCR22bits.MUX = 2; // SPI2_MOSI
    
    PORTA_PCR14 |= 0x00000002; // LED3 pulldown
}

// Initialises ADC for battery.
static void BAT_ADC_init()
{
    // enable ADC0 clock
    ADC0_bit = 1;
    
    // initialise ADC0 module
    ADC0_CFG1 = 0;
    ADC0_CFG2 = 0;
    ADC0_CV1 = 0;
    ADC0_CV2 = 0;
    ADC0_SC2 = 0;
    ADC0_SC3 = 0;
    
    // configure ADC0 module
    MODE0_bit = 1;
    MODE1_bit = 1;

    ADHSC_bit = 1;
    ADLSTS0_bit = 1;
    ADLSTS1_bit = 1;
    
    // enable ADC0 interrupt
    NVIC_IntEnable( IVT_INT_ADC0 );
    
    // configure ADC0 channel
    ADC0_SC1A = 0x10;
}

// Initialises components.
static void components_init()
{
    // DMA_controller initialization
    EDMA_DRV_Init( &DMA_controller_State, &DMA_controller_InitConfig0 );

    // OLED_SPI initialization
    DSPI_DRV_EdmaMasterInit( FSL_OLED_SPI, &OLED_SPI_MasterState,
        &OLED_SPI_MasterConfig, &OLED_SPI_dmaTcd );
    DSPI_DRV_EdmaMasterConfigureBus(
        FSL_OLED_SPI, &OLED_SPI_BusConfig, &OLED_SPI_calculatedBaudRate );

    // PWR_Manager initialization
    NVIC_IntEnable( IVT_INT_LLW );

    // BATTERY_ADC initialization
    BAT_ADC_init();

    // sensor_timer Auto initialization start
    LPTMR_DRV_Init( &sensor_timer_State,&sensor_timer_cfg );
}

////////////////////////////////////////////////////////////////////////////////
// Global function definitions.                                               //
////////////////////////////////////////////////////////////////////////////////

// Sets clocks, configures pins and initialises RTOS and hardware components.
void system_init()
{
    // Global routing function and crystal values initialisation.
    hardware_init();

    // Components initialisation.
    components_init();
}