/**
 * @file 6LoWPAN_C_click.c
 * @brief 6LoWPAN C click ARM example
 *
 ******************************************************************************/

/*******************************************************************************
********************************************************************************
* Includes
********************************************************************************
*******************************************************************************/

#include <stdint.h>
#include "__C6LP_Driver.h"

/*******************************************************************************
********************************************************************************
* Preprocessor Constants
********************************************************************************
*******************************************************************************/

// Application mode: 1 - receiver; 0 - transmitter
// Change this value to switch between receiver and transmitter modes
// of the application.
#define RECEIVER 1

// Application parameters
#define RF_CHANNEL                25      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                0x2017
#define SWITCH_ADDR           0x1234
#define LIGHT_ADDR            0x5678
#define APP_PAYLOAD_LENGTH        1
#define LIGHT_TOGGLE_CMD          0

// Application states
#define IDLE                      0
#define SEND_CMD                  1

// Application role
#define NONE                      0
#define SWITCH                    1
#define LIGHT                     2
#define APP_MODES                 2

/*******************************************************************************
********************************************************************************
* Memory Declarations
********************************************************************************
*******************************************************************************/

// LEDs
sbit LED0 at PTA_PDOR.B12;
sbit LED1 at PTA_PDOR.B13;

// 6LoWPAN click pins
sbit C6LP_RESET at PTB_PDOR.B11;
sbit C6LP_VREG_EN at PTA_PDOR.B10;

sbit C6LP_SPI_CS at PTC_PDOR.B4;
sbit C6LP_SPI_MISO at PTC_PDIR.B7;

sbit C6LP_GPIO0 at  PTB_PDIR.B2;

#if (!RECEIVER)
static uint8_t flag;
#endif

static uint8_t pTxData[APP_PAYLOAD_LENGTH];
static uint8_t pRxData[APP_PAYLOAD_LENGTH];
static T_C6LP_cfg config;

/*******************************************************************************
********************************************************************************
* Public Functions
********************************************************************************
*******************************************************************************/

#if (!RECEIVER)
// Interrupt routine for the "send package" button.
void portAInterruptHandler() iv IVT_INT_PORTA ics ICS_AUTO
{
    if (PORTA_ISFR.B14)
    {
        PORTA_ISFR.B14 = 1;

        flag = 1;
    }
}
#endif

// Interrupt routine for receiving data.
void portBInterruptHandler() iv IVT_INT_PORTB ics ICS_AUTO
{
    if (PORTB_ISFR.B13)
    {
        PORTB_ISFR.B13 = 1;

        C6LP_rxFrmDoneIsr();
    }
}

void C6LP_userDisableRxInterrupt()
{
    // Clear the IRQ
    NVIC_IntDisable(IVT_INT_PORTB);
    PORTB_ISFR.B13 = 1;
}

void C6LP_userEnableRxInterrupt()
{
    GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_13);
    IRQC0_PORTB_PCR13_bit = 1;     // Rising Edge will trigger interrupt
    IRQC1_PORTB_PCR13_bit = 0;
    IRQC2_PORTB_PCR13_bit = 0;
    IRQC3_PORTB_PCR13_bit = 1;
    NVIC_IntEnable(IVT_INT_PORTB);
}

uint8_t C6LP_spiRxTx(uint8_t x)
{
    return SPI0_Read(x);
}

void main()
{
    // Config basicRF
    config.panId = PAN_ID;
    config.channel = RF_CHANNEL;
    config.ackRequest = TRUE;

    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_6);
    SPI0_Init_Advanced(4000000, _SPI_CFG_FRAME_SIZE_8BITS | _SPI_CFG_MASTER |
        _SPI_CFG_CLK_IDLE_LOW | _SPI_CFG_CLK_PHASE_CAPT_LEADING |
        _SPI_CFG_MSB_FIRST, &_GPIO_Module_SPI0_PC5_7_6);

    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_11); // RF_RESET
    GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_10); // RF_VREG_EN
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4); // RF_SPI_CS

    GPIO_Digital_Input(&PTB_PDIR, _GPIO_PINMASK_2); // RF_GPIO0
    
    // LEDs
    GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_12 | _GPIO_PINMASK_13);
    
    EnableInterrupts(); // Enable interrupts

#if (!RECEIVER)
    // button
    GPIO_Digital_Input(&PTA_PDIR, _GPIO_PINMASK_14);
    
    // Enable button interrupt
    IRQC0_PORTA_PCR14_bit = 1;     // Rising Edge will trigger interrupt
    IRQC1_PORTA_PCR14_bit = 0;
    IRQC2_PORTA_PCR14_bit = 0;
    IRQC3_PORTA_PCR14_bit = 1;
    PE_PORTA_PCR14_bit = 1;        // Enable pullup/pulldown
    NVIC_IntEnable(IVT_INT_PORTA); // Enable PORTA interrupt
#endif

    // Enable rx interrupt
    C6LP_userEnableRxInterrupt();

    // LEDs to 0
    LED0 = 0;
    LED1 = 0;
    
    Delay_ms(100);

#if RECEIVER
    // Receiver code

    // Initialize BasicRF
    config.myAddr = LIGHT_ADDR;
    if (C6LP_init(&config) == FAILED)
        LED1 = 1;
    
    // Data reception on.
    C6LP_receiveOn();
    EnableInterrupts();
    
    // Wait for a package from the transmitter.
    while (1)
    {
        while (!C6LP_isPacketReady());

        if (C6LP_receive(pRxData, APP_PAYLOAD_LENGTH, 0) > 0)
        {
            // Handle the received package.
            if (pRxData[0] == LIGHT_TOGGLE_CMD)
            {
                LED0 = !LED0;
            }
        }
    }
#else
    // Transmitter code

    pTxData[0] = LIGHT_TOGGLE_CMD;

    // Initialize BasicRF
    config.myAddr = SWITCH_ADDR;
    if (C6LP_init(&config) == FAILED)
        LED1 = 1;
    
    // Keep Receiver off when not needed to save power.
    C6LP_receiveOff();

    flag = 0;
    EnableInterrupts();
    
    // Wait for the interrupt routine to indicate that a button is pressed.
    while (1)
    {
        if (flag)
        {
            flag = 0;
            LED0 = !LED0;

            // Send the package to the receiver.
            C6LP_sendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH);
            EnableInterrupts();
        }
    }
#endif
}