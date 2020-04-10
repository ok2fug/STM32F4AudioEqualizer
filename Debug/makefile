################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include FilteringFunctions/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
dac-test.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
dac-test.list \

OBJCOPY_BIN += \
dac-test.bin \


# All Target
all: dac-test.elf secondary-outputs

# Tool invocations
dac-test.elf: $(OBJS) $(USER_OBJS) C:\Users\Fede\STM32CubeIDE\workspace_1.0.0\dac-test\STM32F429ZITX_FLASH.ld
	arm-none-eabi-gcc -o "dac-test.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Fede\STM32CubeIDE\workspace_1.0.0\dac-test\STM32F429ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="dac-test.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

dac-test.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "dac-test.list"
	@echo 'Finished building: $@'
	@echo ' '

dac-test.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "dac-test.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
