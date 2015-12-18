################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/rtos/FreeRTOS/src/croutine.c \
../SDK/rtos/FreeRTOS/src/event_groups.c \
../SDK/rtos/FreeRTOS/src/heap_1.c \
../SDK/rtos/FreeRTOS/src/heap_2.c \
../SDK/rtos/FreeRTOS/src/heap_3.c \
../SDK/rtos/FreeRTOS/src/heap_4.c \
../SDK/rtos/FreeRTOS/src/list.c \
../SDK/rtos/FreeRTOS/src/queue.c \
../SDK/rtos/FreeRTOS/src/tasks.c \
../SDK/rtos/FreeRTOS/src/timers.c 

OBJS += \
./SDK/rtos/FreeRTOS/src/croutine.o \
./SDK/rtos/FreeRTOS/src/event_groups.o \
./SDK/rtos/FreeRTOS/src/heap_1.o \
./SDK/rtos/FreeRTOS/src/heap_2.o \
./SDK/rtos/FreeRTOS/src/heap_3.o \
./SDK/rtos/FreeRTOS/src/heap_4.o \
./SDK/rtos/FreeRTOS/src/list.o \
./SDK/rtos/FreeRTOS/src/queue.o \
./SDK/rtos/FreeRTOS/src/tasks.o \
./SDK/rtos/FreeRTOS/src/timers.o 

C_DEPS += \
./SDK/rtos/FreeRTOS/src/croutine.d \
./SDK/rtos/FreeRTOS/src/event_groups.d \
./SDK/rtos/FreeRTOS/src/heap_1.d \
./SDK/rtos/FreeRTOS/src/heap_2.d \
./SDK/rtos/FreeRTOS/src/heap_3.d \
./SDK/rtos/FreeRTOS/src/heap_4.d \
./SDK/rtos/FreeRTOS/src/list.d \
./SDK/rtos/FreeRTOS/src/queue.d \
./SDK/rtos/FreeRTOS/src/tasks.d \
./SDK/rtos/FreeRTOS/src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/rtos/FreeRTOS/src/%.o: ../SDK/rtos/FreeRTOS/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"FSL_RTOS_FREE_RTOS" -D"CPU_MK64FN1M0VDC12" -DARM_MATH_CM4 -D__FPU_PRESENT -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/hal/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/hal/src/sim/MK64F12" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/system/src/clock/MK64F12" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/system/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/osa/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/CMSIS/Include" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/devices" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/devices/MK64F12/include" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/devices/MK64F12/startup" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Generated_Code/SDK/platform/devices/MK64F12/startup" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/apps/common/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/apps/watch/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/FLASH/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/FXAS/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/FXOS/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/HTU/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/MPL/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/TSL/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/MAXIM/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/OLED/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/power/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/I2C/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/drivers/SPI/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Generated_Code" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/intf/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/menu/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/exceptions/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/sensors/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Sources/HEXIWEAR/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/rtos/FreeRTOS/include" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/rtos/FreeRTOS/port/gcc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/Generated_Code/SDK/rtos/FreeRTOS/config" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/drivers/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/utilities/inc" -I"D:/Marko/tasks/freescale/work/HEXIWEAR_OLED_sensors_RTOS/SDK/platform/system/src/power" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


