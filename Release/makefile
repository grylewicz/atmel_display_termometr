################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
atmel_display_termometr.lss \

FLASH_IMAGE += \
atmel_display_termometr.hex \

EEPROM_IMAGE += \
atmel_display_termometr.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: atmel_display_termometr.elf secondary-outputs

# Tool invocations
atmel_display_termometr.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,atmel_display_termometr.map -mmcu=attiny2313 -o "atmel_display_termometr.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

atmel_display_termometr.lss: atmel_display_termometr.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S atmel_display_termometr.elf  >"atmel_display_termometr.lss"
	@echo 'Finished building: $@'
	@echo ' '

atmel_display_termometr.hex: atmel_display_termometr.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex atmel_display_termometr.elf  "atmel_display_termometr.hex"
	@echo 'Finished building: $@'
	@echo ' '

atmel_display_termometr.eep: atmel_display_termometr.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex atmel_display_termometr.elf  "atmel_display_termometr.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: atmel_display_termometr.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny2313 atmel_display_termometr.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) atmel_display_termometr.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
