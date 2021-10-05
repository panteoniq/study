################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Twosum/Twosum.cpp 

OBJS += \
./src/Twosum/Twosum.o 

CPP_DEPS += \
./src/Twosum/Twosum.d 


# Each subdirectory must supply rules for building sources it contributes
src/Twosum/%.o: ../src/Twosum/%.cpp src/Twosum/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


