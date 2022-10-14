################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver2/Ethernet/W5100S/w5100s.c 

OBJS += \
./ioLibrary_Driver2/Ethernet/W5100S/w5100s.o 

C_DEPS += \
./ioLibrary_Driver2/Ethernet/W5100S/w5100s.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver2/Ethernet/W5100S/%.o ioLibrary_Driver2/Ethernet/W5100S/%.su: ../ioLibrary_Driver2/Ethernet/W5100S/%.c ioLibrary_Driver2/Ethernet/W5100S/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"C:/Users/trkke/OneDrive/Documents/Stm32Codes/2TIMERS_ECOPLAST/ioLibrary_Driver2/Ethernet" -I"C:/Users/trkke/OneDrive/Documents/Stm32Codes/2TIMERS_ECOPLAST/ioLibrary_Driver2" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/trkke/OneDrive/Documents/Stm32Codes/2TIMERS_ECOPLAST/ioLibrary_Driver2/Internet/MQTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ioLibrary_Driver2-2f-Ethernet-2f-W5100S

clean-ioLibrary_Driver2-2f-Ethernet-2f-W5100S:
	-$(RM) ./ioLibrary_Driver2/Ethernet/W5100S/w5100s.d ./ioLibrary_Driver2/Ethernet/W5100S/w5100s.o ./ioLibrary_Driver2/Ethernet/W5100S/w5100s.su

.PHONY: clean-ioLibrary_Driver2-2f-Ethernet-2f-W5100S

