################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_prog.c \
../DIO_program.c \
../GIE_program.c \
../SCH_program.c \
../SPI_prog.c \
../TMR0_program.c \
../TMR1_program.c \
../USART_program.c \
../main.c 

OBJS += \
./ADC_prog.o \
./DIO_program.o \
./GIE_program.o \
./SCH_program.o \
./SPI_prog.o \
./TMR0_program.o \
./TMR1_program.o \
./USART_program.o \
./main.o 

C_DEPS += \
./ADC_prog.d \
./DIO_program.d \
./GIE_program.d \
./SCH_program.d \
./SPI_prog.d \
./TMR0_program.d \
./TMR1_program.d \
./USART_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


