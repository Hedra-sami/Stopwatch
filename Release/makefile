################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/WDT/subdir.mk
-include MCAL/TIMER1/subdir.mk
-include MCAL/TIMER0/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EXTINT0/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/SSD/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/Keypad/subdir.mk
-include HAL/DCM/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
MY_DRIVERS.lss \

FLASH_IMAGE += \
MY_DRIVERS.hex \

EEPROM_IMAGE += \
MY_DRIVERS.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: MY_DRIVERS.elf secondary-outputs

# Tool invocations
MY_DRIVERS.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,MY_DRIVERS.map -mmcu=atmega32 -o "MY_DRIVERS.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

MY_DRIVERS.lss: MY_DRIVERS.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S MY_DRIVERS.elf  >"MY_DRIVERS.lss"
	@echo 'Finished building: $@'
	@echo ' '

MY_DRIVERS.hex: MY_DRIVERS.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex MY_DRIVERS.elf  "MY_DRIVERS.hex"
	@echo 'Finished building: $@'
	@echo ' '

MY_DRIVERS.eep: MY_DRIVERS.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex MY_DRIVERS.elf  "MY_DRIVERS.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: MY_DRIVERS.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 MY_DRIVERS.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) MY_DRIVERS.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
