################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Static_Code/System/subdir.mk
-include Sources/sensors/src/subdir.mk
-include Sources/menu/src/subdir.mk
-include Sources/intf/src/subdir.mk
-include Sources/exceptions/src/subdir.mk
-include Sources/drivers/power/src/subdir.mk
-include Sources/drivers/TSL/src/subdir.mk
-include Sources/drivers/SPI/src/subdir.mk
-include Sources/drivers/OLED/src/subdir.mk
-include Sources/drivers/MPL/src/subdir.mk
-include Sources/drivers/MAXIM/src/subdir.mk
-include Sources/drivers/I2C/src/subdir.mk
-include Sources/drivers/HTU/src/subdir.mk
-include Sources/drivers/FXOS/src/subdir.mk
-include Sources/drivers/FXAS/src/subdir.mk
-include Sources/drivers/FLASH/src/subdir.mk
-include Sources/cmsis_dsp/src/TransformFunctions/subdir.mk
-include Sources/cmsis_dsp/src/SupportFunctions/subdir.mk
-include Sources/cmsis_dsp/src/StatisticsFunctions/subdir.mk
-include Sources/cmsis_dsp/src/MatrixFunctions/subdir.mk
-include Sources/cmsis_dsp/src/FilteringFunctions/subdir.mk
-include Sources/cmsis_dsp/src/FastMathFunctions/subdir.mk
-include Sources/cmsis_dsp/src/ControllerFunctions/subdir.mk
-include Sources/cmsis_dsp/src/ComplexMathFunctions/subdir.mk
-include Sources/cmsis_dsp/src/CommonTables/subdir.mk
-include Sources/cmsis_dsp/src/BasicMathFunctions/subdir.mk
-include Sources/apps/watch/src/subdir.mk
-include Sources/apps/sensorTag/src/subdir.mk
-include Sources/HEXIWEAR/src/subdir.mk
-include Sources/subdir.mk
-include SDK/rtos/FreeRTOS/src/subdir.mk
-include SDK/rtos/FreeRTOS/port/gcc/subdir.mk
-include SDK/platform/utilities/src/subdir.mk
-include SDK/platform/system/src/power/subdir.mk
-include SDK/platform/system/src/interrupt/subdir.mk
-include SDK/platform/system/src/clock/MK64F12/subdir.mk
-include SDK/platform/system/src/clock/subdir.mk
-include SDK/platform/osa/src/subdir.mk
-include SDK/platform/hal/src/uart/subdir.mk
-include SDK/platform/hal/src/smc/subdir.mk
-include SDK/platform/hal/src/sim/MK64F12/subdir.mk
-include SDK/platform/hal/src/rtc/subdir.mk
-include SDK/platform/hal/src/rcm/subdir.mk
-include SDK/platform/hal/src/port/subdir.mk
-include SDK/platform/hal/src/osc/subdir.mk
-include SDK/platform/hal/src/mcg/subdir.mk
-include SDK/platform/hal/src/llwu/subdir.mk
-include SDK/platform/hal/src/i2c/subdir.mk
-include SDK/platform/hal/src/gpio/subdir.mk
-include SDK/platform/hal/src/edma/subdir.mk
-include SDK/platform/hal/src/dspi/subdir.mk
-include SDK/platform/hal/src/dmamux/subdir.mk
-include SDK/platform/hal/src/adc16/subdir.mk
-include SDK/platform/drivers/src/uart/subdir.mk
-include SDK/platform/drivers/src/rtc/subdir.mk
-include SDK/platform/drivers/src/i2c/subdir.mk
-include SDK/platform/drivers/src/gpio/subdir.mk
-include SDK/platform/drivers/src/edma/subdir.mk
-include SDK/platform/drivers/src/dspi/subdir.mk
-include SDK/platform/drivers/src/adc16/subdir.mk
-include SDK/platform/devices/MK64F12/startup/gcc/subdir.mk
-include SDK/platform/devices/MK64F12/startup/subdir.mk
-include SDK/platform/devices/subdir.mk
-include Generated_Code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
HEXIWEAR_OLED_sensors_RTOS.bin \

SECONDARY_SIZE += \
HEXIWEAR_OLED_sensors_RTOS.siz \


# All Target
all: HEXIWEAR_OLED_sensors_RTOS.elf secondary-outputs

# Tool invocations
HEXIWEAR_OLED_sensors_RTOS.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -T "D:/temp/20151217/HEXIWEAR_OLED_sensors_RTOS/Project_Settings/Linker_Files/ProcessorExpert.ld" -Xlinker --gc-sections -L"D:/temp/20151217/HEXIWEAR_OLED_sensors_RTOS/Project_Settings/Linker_Files" -Wl,-Map,"HEXIWEAR_OLED_sensors_RTOS.map" -specs=nosys.specs -specs=nano.specs -o "HEXIWEAR_OLED_sensors_RTOS.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

HEXIWEAR_OLED_sensors_RTOS.bin: HEXIWEAR_OLED_sensors_RTOS.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "HEXIWEAR_OLED_sensors_RTOS.elf"  "HEXIWEAR_OLED_sensors_RTOS.bin"
	@echo 'Finished building: $@'
	@echo ' '

HEXIWEAR_OLED_sensors_RTOS.siz: HEXIWEAR_OLED_sensors_RTOS.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "HEXIWEAR_OLED_sensors_RTOS.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(SECONDARY_FLASH)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) HEXIWEAR_OLED_sensors_RTOS.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
