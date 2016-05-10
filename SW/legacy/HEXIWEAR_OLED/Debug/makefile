################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include menu/src/subdir.mk
-include exceptions/src/subdir.mk
-include drivers/power/src/subdir.mk
-include drivers/SPI/src/subdir.mk
-include drivers/OLED/src/subdir.mk
-include drivers/FLASH/src/subdir.mk
-include Static_Code/System/subdir.mk
-include Sources/subdir.mk
-include SDK/platform/system/src/power/subdir.mk
-include SDK/platform/system/src/interrupt/subdir.mk
-include SDK/platform/system/src/clock/MK64F12/subdir.mk
-include SDK/platform/system/src/clock/subdir.mk
-include SDK/platform/osa/src/subdir.mk
-include SDK/platform/hal/src/smc/subdir.mk
-include SDK/platform/hal/src/sim/MK64F12/subdir.mk
-include SDK/platform/hal/src/rtc/subdir.mk
-include SDK/platform/hal/src/rcm/subdir.mk
-include SDK/platform/hal/src/port/subdir.mk
-include SDK/platform/hal/src/osc/subdir.mk
-include SDK/platform/hal/src/mcg/subdir.mk
-include SDK/platform/hal/src/llwu/subdir.mk
-include SDK/platform/hal/src/gpio/subdir.mk
-include SDK/platform/hal/src/edma/subdir.mk
-include SDK/platform/hal/src/dspi/subdir.mk
-include SDK/platform/hal/src/dmamux/subdir.mk
-include SDK/platform/drivers/src/rtc/subdir.mk
-include SDK/platform/drivers/src/gpio/subdir.mk
-include SDK/platform/drivers/src/edma/subdir.mk
-include SDK/platform/drivers/src/dspi/subdir.mk
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
SECONDARY_SIZE += \
OLED_bm.siz \


# All Target
all: OLED_bm.elf secondary-outputs

# Tool invocations
OLED_bm.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -T "D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/Project_Settings/Linker_Files/ProcessorExpert.ld" -Xlinker --gc-sections -L"D:/Marko/tasks/freescale/projects/HEXIWEAR_OLED/Project_Settings/Linker_Files" -Wl,-Map,"OLED_bm.map" -specs=nosys.specs -specs=nano.specs -o "OLED_bm.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

OLED_bm.siz: OLED_bm.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "OLED_bm.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) OLED_bm.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
