/*
Example for Fan_2 Click

    Date          : Jul 2017.
    Author        : Djordje Rosic

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v5.1.0

Description :

    Following example will initialize FAN 2 click. It will setup the lookup
    table and basic settings, and drive the fan rotation depending on the
    temperature.

    Additionally, fan can be set to manual contol. Uncomment the Fan_2_Manual()
    and Fan_2_Task(), and fan will switch on and off every few seconds, instead
    of being controlled automatically.

*/

#include "__FAN2_Driver.h"

/*
    Following Look-up table settings will drive the fan slowly if the
    temperature is below 28 degrees Celsius, gradually accelerate when the
    temperature starts rising, and reach maximum rotation at 42 degrees Celsius.
    Table starts at 18 degrees, and each step is 2 degrees (step can be changed
    via register commands).

    0x20 = ~ 12% duty cycle
    0x80 = ~ 50% duty cycle
    0xFF = Full power
 */
uint8_t LUTSettings [48] = { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x50,
                 0x80, 0xA0, 0xD0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

void systemInit()
{
    I2C0_Init_Advanced( 100000, &_GPIO_Module_I2C0_PD8_9 );
}

//sets fan to automatic control (default), and fills the look-up table
void Fan_2_Init()
{
    FAN2_I2CdriverInit( I2C0_Start, 0, 0, I2C0_Write, I2C0_Read);
    FAN2_sendCommand(_FAN2_CONTROL_REGISTER_1, _FAN2_CMD1_DEFAULT);
    FAN2_sendCommand(_FAN2_CONTROL_REGISTER_2, _FAN2_CMD2_DEFAULT);
    FAN2_sendCommand(_FAN2_CONTROL_REGISTER_3, _FAN2_CMD3_DEFAULT | _FAN2_CMD3_INSTANT_RAMP);
    FAN2_setupLUT(LUTSettings);
}

//sets fan to manual control
void Fan_2_Manual()
{
    FAN2_sendCommand(_FAN2_CONTROL_REGISTER_1, _FAN2_CMD1_DEFAULT);
    FAN2_sendCommand(_FAN2_CONTROL_REGISTER_2, _FAN2_CMD2_DEFAULT | _FAN2_CMD2_DIRECT_CONTROL);
    FAN2_sendCommand(_FAN2_CONTROL_REGISTER_3, _FAN2_CMD3_DEFAULT | _FAN2_CMD3_INSTANT_RAMP);
}

//turns fan on and off
void Fan_2_Task()
{
    FAN2_sendCommand(_FAN2_DIRECT_CONTROL_REGISTER, _FAN2_DUTYCYCLE_100);
    delay_ms (5000);
    FAN2_sendCommand(_FAN2_DIRECT_CONTROL_REGISTER, _FAN2_DUTYCYCLE_0);
    delay_ms (5000);
}

void main()
{

    systemInit();
    Fan_2_Init();

    //Fan_2_Manual();

    while( 1 )
    {
    //    Fan_2_Task();
    }
}