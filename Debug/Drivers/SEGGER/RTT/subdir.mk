################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/SEGGER/RTT/SEGGER_RTT.c \
../Drivers/SEGGER/RTT/SEGGER_RTT_printf.c 

S_UPPER_SRCS += \
../Drivers/SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./Drivers/SEGGER/RTT/SEGGER_RTT.o \
./Drivers/SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.o \
./Drivers/SEGGER/RTT/SEGGER_RTT_printf.o 

S_UPPER_DEPS += \
./Drivers/SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./Drivers/SEGGER/RTT/SEGGER_RTT.d \
./Drivers/SEGGER/RTT/SEGGER_RTT_printf.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/SEGGER/RTT/%.o Drivers/SEGGER/RTT/%.su Drivers/SEGGER/RTT/%.cyclo: ../Drivers/SEGGER/RTT/%.c Drivers/SEGGER/RTT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../Drivers/SEGGER/Config -I../Drivers/SEGGER/RTT -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Drivers/SEGGER/RTT/%.o: ../Drivers/SEGGER/RTT/%.S Drivers/SEGGER/RTT/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Drivers-2f-SEGGER-2f-RTT

clean-Drivers-2f-SEGGER-2f-RTT:
	-$(RM) ./Drivers/SEGGER/RTT/SEGGER_RTT.cyclo ./Drivers/SEGGER/RTT/SEGGER_RTT.d ./Drivers/SEGGER/RTT/SEGGER_RTT.o ./Drivers/SEGGER/RTT/SEGGER_RTT.su ./Drivers/SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.d ./Drivers/SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.o ./Drivers/SEGGER/RTT/SEGGER_RTT_printf.cyclo ./Drivers/SEGGER/RTT/SEGGER_RTT_printf.d ./Drivers/SEGGER/RTT/SEGGER_RTT_printf.o ./Drivers/SEGGER/RTT/SEGGER_RTT_printf.su

.PHONY: clean-Drivers-2f-SEGGER-2f-RTT

