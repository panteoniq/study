################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/raiiandmem/SharedPtr.cpp \
../src/raiiandmem/WeakPtr.cpp 

OBJS += \
./src/raiiandmem/SharedPtr.o \
./src/raiiandmem/WeakPtr.o 

CPP_DEPS += \
./src/raiiandmem/SharedPtr.d \
./src/raiiandmem/WeakPtr.d 


# Each subdirectory must supply rules for building sources it contributes
src/raiiandmem/%.o: ../src/raiiandmem/%.cpp src/raiiandmem/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


