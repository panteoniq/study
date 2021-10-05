################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/auto/AutoTest.cpp 

OBJS += \
./src/auto/AutoTest.o 

CPP_DEPS += \
./src/auto/AutoTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/auto/%.o: ../src/auto/%.cpp src/auto/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


