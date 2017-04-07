# Docking Station firmware update

## MAINTENANCE mode

- HEXIWEAR_DockingStation_MAINTENANCE_FW.bin is file containing firmware for MAINTENANCE mode for Docking Station K20 MCU
- This file needs to be programmed onto K20 by using external programmer connected to the connector CN6 on the back side of the Docking Station (take a look at Hexiwear_Docking_Station_OpenSDA_circuitry.png).
- If, for example J-Link programmer is used, the K20 MCU can be programmed either using J-Flash GUI (which is easier way), or using J-Link.exe command line tool with following instructions:
    -JLINK>device MK20DX128xxx5
    -(S)WD
    -(4000)KHz
    -JLINK>r
    -JLINK>h
    -JLINK>loadbin HEXIWEAR_DockingStation_MAINTENANCE_FW.bin 0
    -JLINK>r
    -JLINK>exit
- Then, MAINTENANCE mass storage drive should appear and you can continue with uploading HEXIWEAR_DockingStation_DAPLINK_FW.bin

## DAPLINK mode

- HEXIWEAR_DockingStation_DAPLINK_FW.bin is file containing firmware for docking station K20 MCU, that can be loaded using bootloader from Docking Station's MAINTENANCE mode that you can enter by holding RESET button while plugging in USB cable. 
- After that mass storage device with the name MAINTENANCE should appear. 
- Then you drag-n-drop one of the aforementioned files and it should load the firmware onto the K20 chip.
- After successful loading MSD should appear again but this time with the name DAPLINK.
