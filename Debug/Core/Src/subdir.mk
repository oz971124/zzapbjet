################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/buzzer.c \
../Core/Src/fnd4dight.c \
../Core/Src/i2c_lcd.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/washer.c \
../Core/Src/washer_button.c \
../Core/Src/washer_dcmotor.c \
../Core/Src/washer_led.c \
../Core/Src/washer_time.c \
../Core/Src/washer_uart.c \
../Core/Src/washer_ultrasonic.c 

OBJS += \
./Core/Src/buzzer.o \
./Core/Src/fnd4dight.o \
./Core/Src/i2c_lcd.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/washer.o \
./Core/Src/washer_button.o \
./Core/Src/washer_dcmotor.o \
./Core/Src/washer_led.o \
./Core/Src/washer_time.o \
./Core/Src/washer_uart.o \
./Core/Src/washer_ultrasonic.o 

C_DEPS += \
./Core/Src/buzzer.d \
./Core/Src/fnd4dight.d \
./Core/Src/i2c_lcd.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/washer.d \
./Core/Src/washer_button.d \
./Core/Src/washer_dcmotor.d \
./Core/Src/washer_led.d \
./Core/Src/washer_time.d \
./Core/Src/washer_uart.d \
./Core/Src/washer_ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/buzzer.cyclo ./Core/Src/buzzer.d ./Core/Src/buzzer.o ./Core/Src/buzzer.su ./Core/Src/fnd4dight.cyclo ./Core/Src/fnd4dight.d ./Core/Src/fnd4dight.o ./Core/Src/fnd4dight.su ./Core/Src/i2c_lcd.cyclo ./Core/Src/i2c_lcd.d ./Core/Src/i2c_lcd.o ./Core/Src/i2c_lcd.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/washer.cyclo ./Core/Src/washer.d ./Core/Src/washer.o ./Core/Src/washer.su ./Core/Src/washer_button.cyclo ./Core/Src/washer_button.d ./Core/Src/washer_button.o ./Core/Src/washer_button.su ./Core/Src/washer_dcmotor.cyclo ./Core/Src/washer_dcmotor.d ./Core/Src/washer_dcmotor.o ./Core/Src/washer_dcmotor.su ./Core/Src/washer_led.cyclo ./Core/Src/washer_led.d ./Core/Src/washer_led.o ./Core/Src/washer_led.su ./Core/Src/washer_time.cyclo ./Core/Src/washer_time.d ./Core/Src/washer_time.o ./Core/Src/washer_time.su ./Core/Src/washer_uart.cyclo ./Core/Src/washer_uart.d ./Core/Src/washer_uart.o ./Core/Src/washer_uart.su ./Core/Src/washer_ultrasonic.cyclo ./Core/Src/washer_ultrasonic.d ./Core/Src/washer_ultrasonic.o ./Core/Src/washer_ultrasonic.su

.PHONY: clean-Core-2f-Src

