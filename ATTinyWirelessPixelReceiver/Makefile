CXXSRC = atTinySpi.cpp atTinyGpio.cpp atTinyPersist.cpp atTinyLedControl.cpp fixup.cpp main.cpp
ASRC = RGBWriteOut.S
AVR_OBJS    = $(CXXSRC:%.cpp=attRelease/%.o) $(ASRC:%.S=attRelease/%.o)
ATT_EXTRAINCDIRS = ../nrf24l01 ../bdcstWirelessPixelReceiver

include ../rules.mk
include ../local.mk

TARGET = attRelease/ATTinyWirelessPixelReceiver

ATT_LDFLAGS += -lbdcstWirelessPixelReceiver -lnrf24l01 -L../nrf24l01/attRelease -L../bdcstWirelessPixelReceiver/attRelease


all: directories $(TARGET).elf $(TARGET).lss $(TARGET).sym \
	$(TARGET).hex $(TARGET).eep

directories:
	$(MKDIR) attRelease

install:
ifdef ATT_AVRDUDE_PORT
	- $(AVRDUDE) -c$(ATT_AVRDUDE_PROGRAMMER) -P$(ATT_AVRDUDE_PORT) $(ATT_EXTRA_FLAGS) $(ATT_AVRDUDE_WRITE_FLASH)
	- $(AVRDUDE) -c$(ATT_AVRDUDE_PROGRAMMER) -P$(ATT_AVRDUDE_PORT) $(ATT_EXTRA_FLAGS) $(ATT_AVRDUDE_FUSES)
endif

# Target: clean project.
clean:
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) -r attRelease

.PHONY : directories clean install
