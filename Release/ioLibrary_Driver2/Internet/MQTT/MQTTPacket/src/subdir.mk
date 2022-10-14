################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.c \
../ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.c \
../ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.c \
../ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTFormat.c \
../ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTPacket.c \
../ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.c \
../ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.c \
../ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.c \
../ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c \
../ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c 

OBJS += \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.o \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.o \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.o \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTFormat.o \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTPacket.o \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.o \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.o \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.o \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o 

C_DEPS += \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.d \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.d \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.d \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTFormat.d \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTPacket.d \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.d \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.d \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.d \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d \
./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d 


# Each subdirectory must supply rules for building sources it contributes
ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/%.o ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/%.su: ../ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/%.c ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"C:/Users/trkke/OneDrive/Documents/Stm32Codes/2TIMERS_ECOPLAST/ioLibrary_Driver2/Ethernet" -I"C:/Users/trkke/OneDrive/Documents/Stm32Codes/2TIMERS_ECOPLAST/ioLibrary_Driver2" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"C:/Users/trkke/OneDrive/Documents/Stm32Codes/2TIMERS_ECOPLAST/ioLibrary_Driver2/Internet/MQTT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ioLibrary_Driver2-2f-Internet-2f-MQTT-2f-MQTTPacket-2f-src

clean-ioLibrary_Driver2-2f-Internet-2f-MQTT-2f-MQTTPacket-2f-src:
	-$(RM) ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.d ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.o ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.su ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.d ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.o ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.su ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.d ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.o ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.su ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTFormat.d ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTFormat.o ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTFormat.su ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTPacket.d ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTPacket.o ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTPacket.su ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.d ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.o ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.su ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.d ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.o ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.su ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.d ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.o ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.su ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.su ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o ./ioLibrary_Driver2/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.su

.PHONY: clean-ioLibrary_Driver2-2f-Internet-2f-MQTT-2f-MQTTPacket-2f-src

