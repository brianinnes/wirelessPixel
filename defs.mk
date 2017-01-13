export MAKEFLAGS += --no-builtin-rules

export REMOVE = rm -f
export COPY = cp
export SHELL = sh
export MKDIR = mkdir -p

#AVR Tools
export AVR_CC = avr-gcc
export AVR_CXX = avr-g++
export AVR_AR = avr-ar
export AVR_OBJCOPY = avr-objcopy
export AVR_OBJDUMP = avr-objdump
export AVR_SIZE = avr-size
export AVR_STRIP = avr-strip
export ARV_NM = avr-nm
# Programming support using avrdude.
export AVRDUDE = avrdude


#ARM6 Tools
export AR6_CC = /opt/arm-bcm2708hardfp-linux-gnueabi/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
export AR6_CXX = /opt/arm-bcm2708hardfp-linux-gnueabi/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
export AR6_AR = /opt/arm-bcm2708hardfp-linux-gnueabi/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-ar
export AR6_OBJCOPY = /opt/arm-bcm2708hardfp-linux-gnueabi/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-objcopy
export AR6_OBJDUMP = /opt/arm-bcm2708hardfp-linux-gnueabi/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-objdump
export AR6_SIZE = /opt/arm-bcm2708hardfp-linux-gnueabi/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-size
export AR6_STRIP = /opt/arm-bcm2708hardfp-linux-gnueabi/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-strip
export AR6_NM = /opt/arm-bcm2708hardfp-linux-gnueabi/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-nm

#ARM7 Tools
export ARM_CC = arm-linux-gnueabihf-gcc
export ARM_CXX = arm-linux-gnueabihf-g++
export ARM_AR = arm-linux-gnueabihf-ar
export ARM_OBJCOPY = arm-linux-gnueabihf-objcopy
export ARM_OBJDUMP = arm-linux-gnueabihf-objdump
export ARM_SIZE = arm-linux-gnueabihf-size
export ARM_STRIP = arm-linux-gnueabihf-strip
export ARM_NM = arm-linux-gnueabihf-nm

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
# EXTRAINCDIRS = $(CURDIR) $(CURDIR)/nrf24l01 /usr/lib/avr/include

#AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep

#export AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)

#HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
#ELFSIZE = $(SIZE) -AC --mcu=$(MCU) $(TARGET).elf

# Define Messages
# English
export MSG_ERRORS_NONE = Errors- none
export MSG_BEGIN = -------- begin --------
export MSG_END = --------  end  --------
export MSG_SIZE_BEFORE = Size before-
export MSG_SIZE_AFTER = Size after-
export MSG_COFF = Converting to AVR COFF-
export MSG_EXTENDED_COFF = Converting to AVR Extended COFF-
export MSG_FLASH = Creating load file for Flash-
export MSG_EEPROM = Creating load file for EEPROM-
export MSG_EXTENDED_LISTING = Creating Extended Listing-
export MSG_SYMBOL_TABLE = Creating Symbol Table-
export MSG_LINKING = Linking-
export MSG_COMPILING = Compiling-
export MSG_ASSEMBLING = Assembling-
export MSG_CLEANING = Cleaning project-
export MSG_INSTALLING = Installing binaries
