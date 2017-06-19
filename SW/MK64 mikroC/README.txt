///////////////////////////////////////////////////////////////////////////////

- HEXIWEAR_MK64 is the full featured HEXIWEAR firmware for the MK64 MCU.

///////////////////////////////////////////////////////////////////////////////

- HEXIWEAR_MK64_WiFi_3G contains WiFi and 3G functionalities in addition to the standard HEXIWEAR_MK64 firmware.

///////////////////////////////////////////////////////////////////////////////

Both firmwares require mikroC PRO for ARM v.5.1.0.

In order to successfully compile the examples, you need to enable case sensitivity in MikroC PRO for ARM:
    1) Open the Options window by selecting Tools -> Options.
    2) Open the Output tab on the left, and select Output Settings.
    3) In Compiler options, check Case sensitive.

If you want to use additional interrupts in your project, you shouldn't use NVIC_SetIntPriority
as it is not working correctly in the current mikroC PRO for ARM version.
Instead, you can use HEXIWEAR_SetIntPriority located in HEXIWEAR_driver.h.
It has the exact same parameters and will work as intended.
