################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../saitek.c \
../socket_fg.c \
../stkmanager.c 

O_SRCS += \
../saitek.o \
../socket_fg.o \
../stkmanager.o 

OBJS += \
./saitek.o \
./socket_fg.o \
./stkmanager.o 

C_DEPS += \
./saitek.d \
./socket_fg.d \
./stkmanager.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


