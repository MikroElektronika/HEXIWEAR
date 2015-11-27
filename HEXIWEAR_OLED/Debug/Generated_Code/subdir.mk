################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/Cpu.c \
../Generated_Code/FLASH_SPI.c \
../Generated_Code/GPIO.c \
../Generated_Code/OLED_SPI.c \
../Generated_Code/PWR_Manager.c \
../Generated_Code/clkManager.c \
../Generated_Code/dmaController1.c \
../Generated_Code/hardware_init.c \
../Generated_Code/osa1.c \
../Generated_Code/pin_mux.c 

OBJS += \
./Generated_Code/Cpu.o \
./Generated_Code/FLASH_SPI.o \
./Generated_Code/GPIO.o \
./Generated_Code/OLED_SPI.o \
./Generated_Code/PWR_Manager.o \
./Generated_Code/clkManager.o \
./Generated_Code/dmaController1.o \
./Generated_Code/hardware_init.o \
./Generated_Code/osa1.o \
./Generated_Code/pin_mux.o 

C_DEPS += \
./Generated_Code/Cpu.d \
./Generated_Code/FLASH_SPI.d \
./Generated_Code/GPIO.d \
./Generated_Code/OLED_SPI.d \
./Generated_Code/PWR_Manager.d \
./Generated_Code/clkManager.d \
./Generated_Code/dmaController1.d \
./Generated_Code/hardware_init.d \
./Generated_Code/osa1.d \
./Generated_Code/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"FSL_OSA_BM_TIMER_CONFIG=2" -D"CPU_MK64FN1M0VDC12" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/SDK/platform/hal/inc" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/SDK/platform/hal/src/sim/MK64F12" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/SDK/platform/system/src/clock/MK64F12" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/SDK/platform/drivers/inc" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/menu/inc" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/drivers/FLASH/inc" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/drivers/OLED/inc" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/drivers/power/inc" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/drivers/SPI/inc" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/exceptions/inc/" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/SDK/platform/system/inc" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/SDK/platform/osa/inc" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/SDK/platform/CMSIS/Include" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/SDK/platform/devices" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/SDK/platform/devices/MK64F12/include" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/SDK/platform/devices/MK64F12/startup" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/Generated_Code/SDK/platform/devices/MK64F12/startup" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/Sources" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/Generated_Code" -I"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/SDK/platform/system/src/power" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


