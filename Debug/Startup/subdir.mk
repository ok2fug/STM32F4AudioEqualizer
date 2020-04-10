################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f429zitx.s 

OBJS += \
./Startup/startup_stm32f429zitx.o 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 '-D__DSP_PRESENT=1' '-D__FPU_PRESENT=1' -c -I"C:/Users/Fede/STM32Cube/Repository/STM32Cube_FW_F4_V1.24.1/Drivers/CMSIS/DSP/Include" -I"C:/Users/Fede/STM32Cube/Repository/STM32Cube_FW_F4_V1.24.1/Drivers/CMSIS/DSP/Examples/ARM/arm_fir_example" -x assembler-with-cpp --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

