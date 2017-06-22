/*
 * Example for DC Motor 5 click
 *
 * Date         Apr 2017
 * Author       Djordje Rosic
 *
 * Test configuration KINETIS :
 *  MCU           :        MK64
 *  Dev. Board    :        HEXIWEAR
 *  SW            :        mikroC PRO for ARM v5.0.0
 *
 * Description :
 *
 * This example demonstrates the use of DC Motor click 5. It will cycle through
 * all 4 possible states.
 *
 ******************************************************************************/


sbit IN1_PIN at PTA_PDOR.B10;
sbit IN2_PIN at PTB_PDOR.B13;


/*
 * System Initialization
 */
void systemInit()
{
    GPIO_Digital_Output(&PTA_PDOR, _GPIO_PINMASK_10);
    GPIO_Digital_Output(&PTB_PDOR, _GPIO_PINMASK_13);
}

void main()
{
    systemInit();

    while (1)
    {
    // Coast

        IN1_PIN = 0;
        IN2_PIN = 0;
        Delay_ms (5000);

    // Reverse

        IN1_PIN = 0;
        IN2_PIN = 1;
        Delay_ms (5000);
    // Brake

        IN1_PIN = 1;
        IN2_PIN = 1;
        Delay_ms (5000);

    // Forward

        IN1_PIN = 1;
        IN2_PIN = 0;
        Delay_ms (5000);

    }
}
/************************************************************ END OF FILE *****/