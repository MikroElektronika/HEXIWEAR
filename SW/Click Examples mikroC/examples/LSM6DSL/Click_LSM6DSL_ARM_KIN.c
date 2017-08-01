/*
        Example for LSM6DSL click

        Date          : Jun 2017
        Author        : Djordje Rosic

        Test configuration KINETIS :
        
                 MCU           :        MK64
                Dev. Board    :        HEXIWEAR
                 SW            :        mikroC PRO for ARM v5.1.0

    Description :

    This examples shows the use of LSM6DSL click library functions. It will
    initialize the sensor, and periodically read acceleration and rotation data.
*/

sbit LSM6DSL_CS_PIN at PTC_PDOR.B4;
#include "__LSM6DSL_Driver.h"

void systemInit()
{
    GPIO_Digital_Output(&PTC_PDOR, _GPIO_PINMASK_4);
    SPI0_Init_Advanced( 5000000, _SPI_CFG_MASTER | _SPI_CFG_SELECT_CTAR0 |
                         _SPI_CFG_FRAME_SIZE_8BITS | _SPI_CFG_CLK_IDLE_HIGH |
                         _SPI_CFG_CLK_PHASE_CHG_LEADING | _SPI_CFG_MSB_FIRST,
                         &_GPIO_Module_SPI0_PC5_7_6);



    UART0_Init(9600);
    Delay_ms( 100 );
}

void main()
{
    char txt [100];
    float x,y,z;
  
    systemInit();
    LSM6DSL_initDriver(Spi0_Write, Spi0_Read);
    UART0_Write_Text ("\r\nInitialized");
    Delay_ms( 100 );
    /*
     * Starts measurements for acceleration and rotation at specified
     * rate (104 HZ) and selected full-scale (+-2G, +-245DPS).
     */
    LSM6DSL_configureRead (CONFIG_ACCELERATION, ODR_104_HZ | FULLSCALE_A_2);
    LSM6DSL_configureRead (CONFIG_ROTATION, ODR_104_HZ | FULLSCALE_R_245);
    Delay_ms( 100 );
    while( 1 )
    {

         UART0_Write_Text ("\r\n\r\nAcceleration values in mili-Gs:");
         LSM6DSL_readAccelerationXYZ (&x, &y, &z, FULLSCALE_A_2);
         sprintf (txt, "\r\nX: %.2f, \t Y:%.2f, \t Z: %.2f", x,y,z);
         Uart0_Write_Text (txt);

         UART0_Write_Text ("\r\nRotation values in degrees per second:");
         LSM6DSL_readRotationXYZ (&x, &y, &z, FULLSCALE_R_245);
         //Values are read in mili-degrees per second, so they need to be divided by 1000
         sprintf (txt,
          "\r\nPitch: %.2f, \t Roll:%.2f, \t Yaw: %.2f", x/1000,y/1000,z/1000);
         Uart0_Write_Text (txt);
         
         delay_ms (2000);
    }
}