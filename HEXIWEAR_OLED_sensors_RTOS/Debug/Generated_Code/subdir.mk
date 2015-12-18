################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/BATTERY_ADC.c \
../Generated_Code/CLK_manager.c \
../Generated_Code/CLOCK.c \
../Generated_Code/Cpu.c \
../Generated_Code/DEBUG_UART.c \
../Generated_Code/DMA_controller.c \
../Generated_Code/FLASH_SPI.c \
../Generated_Code/FS_I2C.c \
../Generated_Code/GPIO.c \
../Generated_Code/HEXI_OS.c \
../Generated_Code/KW40_UART.c \
../Generated_Code/NFS_I2C.c \
../Generated_Code/OLED_SPI.c \
../Generated_Code/PWR_Manager.c \
../Generated_Code/free_rtos.c \
../Generated_Code/hardware_init.c \
../Generated_Code/pin_mux.c 

OBJS += \
./Generated_Code/BATTERY_ADC.o \
./Generated_Code/CLK_manager.o \
./Generated_Code/CLOCK.o \
./Generated_Code/Cpu.o \
./Generated_Code/DEBUG_UART.o \
./Generated_Code/DMA_controller.o \
./Generated_Code/FLASH_SPI.o \
./Generated_Code/FS_I2C.o \
./Generated_Code/GPIO.o \
./Generated_Code/HEXI_OS.o \
./Generated_Code/KW40_UART.o \
./Generated_Code/NFS_I2C.o \
./Generated_Code/OLED_SPI.o \
./Generated_Code/PWR_Manager.o \
./Generated_Code/free_rtos.o \
./Generated_Code/hardware_init.o \
./Generated_Code/pin_mux.o 

C_DEPS += \
./Generated_Code/BATTERY_ADC.d \
./Generated_Code/CLK_manager.d \
./Generated_Code/CLOCK.d \
./Generated_Code/Cpu.d \
./Generated_Code/DEBUG_UART.d \
./Generated_Code/DMA_controller.d \
./Generated_Code/FLASH_SPI.d \
./Generated_Code/FS_I2C.d \
./Generated_Code/GPIO.d \
./Generated_Code/HEXI_OS.d \
./Generated_Code/KW40_UART.d \
./Generated_Code/NFS_I2C.d \
./Generated_Code/OLED_SPI.d \
./Generated_Code/PWR_Manager.d \
./Generated_Code/free_rtos.d \
./Generated_Code/hardware_init.d \
./Generated_Code/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"FSL_RTOS_FREE_RTOS" -D"CPU_MK64FN1M0VDC12" -DARM_MATH_CM4 -D__FPU_PRESENT -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/hal/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/hal/src/sim/MK64F12" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/system/src/clock/MK64F12" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/system/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/osa/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/CMSIS/Include" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/devices" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/devices/MK64F12/include" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/devices/MK64F12/startup" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Generated_Code/SDK/platform/devices/MK64F12/startup" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/apps/common/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/apps/watch/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/FLASH/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/FXAS/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/FXOS/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/HTU/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/MPL/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/TSL/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/MAXIM/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/OLED/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/power/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/I2C/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/SPI/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Generated_Code" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/intf/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/menu/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/exceptions/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/sensors/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/HEXIWEAR/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/rtos/FreeRTOS/include" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/rtos/FreeRTOS/port/gcc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Generated_Code/SDK/rtos/FreeRTOS/config" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/drivers/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/utilities/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/system/src/power" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


