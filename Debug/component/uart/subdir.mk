################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/fsl_adapter_lpuart.c 

OBJS += \
./component/uart/fsl_adapter_lpuart.o 

C_DEPS += \
./component/uart/fsl_adapter_lpuart.d 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c component/uart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MIMXRT1021DAG5A -DCPU_MIMXRT1021DAG5A_cm7 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/samia/ws_imx/INO_Arduino/board" -I"/home/samia/ws_imx/INO_Arduino/source" -I"/home/samia/ws_imx/INO_Arduino/drivers" -I"/home/samia/ws_imx/INO_Arduino/xip" -I"/home/samia/ws_imx/INO_Arduino/component/serial_manager" -I"/home/samia/ws_imx/INO_Arduino/component/uart" -I"/home/samia/ws_imx/INO_Arduino/utilities" -I"/home/samia/ws_imx/INO_Arduino/component/lists" -I"/home/samia/ws_imx/INO_Arduino/CMSIS" -I"/home/samia/ws_imx/INO_Arduino/device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


