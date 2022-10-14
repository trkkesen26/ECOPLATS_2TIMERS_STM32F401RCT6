################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver2/Ethernet/W5200/w5200.c 

OBJS += \
./ioLibrary_Driver2/Ethernet/W5200/w5200.o 

C_DEPS += \
./ioLibrary_Driver2/Ethernet/W5200/w5200.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver2/Ethernet/W5200/%.o ioLibrary_Driver2/Ethernet/W5200/%.su: ../ioLibrary_Driver2/Ethernet/W5200/%.c ioLibrary_Driver2/Ethernet/W5200/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"C:/Users/trkke/OneDrive/Documents/Stm32Codes/2TIMERS_ECOPLAST/ioLibrary_Driver2/Ethernet" -I"C:/Users/trkke/OneDrive/Documents/Stm32Codes/2TIMERS_ECOPLAST/ioLibrary_Driver2" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/trkke/OneDrive/Documents/Stm32Codes/2TIMERS_ECOPLAST/ioLibrary_Driver2/Internet/MQTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ioLibrary_Driver2-2f-Ethernet-2f-W5200

clean-ioLibrary_Driver2-2f-Ethernet-2f-W5200:
	-$(RM) ./ioLibrary_Driver2/Ethernet/W5200/w5200.d ./ioLibrary_Driver2/Ethernet/W5200/w5200.o ./ioLibrary_Driver2/Ethernet/W5200/w5200.su

.PHONY: clean-ioLibrary_Driver2-2f-Ethernet-2f-W5200

