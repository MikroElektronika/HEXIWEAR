# Docking Station firmware update

## MAINTENANCE mode

- HEXIWEAR_DockingStation_MAINTENANCE_FW.bin is file containing firmware for MAINTENANCE mode for Docking Station K20 MCU
- This file needs to be programmed onto K20 by using external programmer connected to the connector CN6 on the back side of the Docking Station (take a look at Hexiwear_Docking_Station_OpenSDA_circuitry.png).
- Then, MAINTENANCE mass storage drive should appear and you can continue with uploading _HEXIWEAR_DockingStation_DAPLINK_FW.bin_

## DAPLINK mode

- HEXIWEAR_DockingStation_DAPLINK_FW.bin is file containing firmware for docking station K20 MCU, that can be loaded using bootloader from Docking Station's MAINTENANCE mode that you can enter by holding RESET button while plugging in USB cable. 
- After that mass storage device with the name MAINTENANCE should appear. 
- Then you drag-n-drop one of the aforementioned files and it should load the firmware onto the K20 chip.
- After successful loading MSD should appear again but this time with the name DAPLINK.

