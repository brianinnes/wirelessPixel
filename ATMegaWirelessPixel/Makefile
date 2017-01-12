CXXSRC = atMegaSpi.cpp atMegaGpio.cpp fixup.cpp main.cpp
ASRC =
AVR_OBJS    = $(CXXSRC:%.cpp=atmRelease/%.o) $(ASRC:%.S=attRelease/%.o)
EXTRAINCDIRS = ../nrf24l01

include ../rules.mk
include ../local.mk

TARGET = atmRelease/ATmWirelessPixel

ATM_EXTRAINCDIRS = ../nrf24l01
ATM_LDFLAGS += -lnrf24l01 -L../nrf24l01/atmRelease

all: directories $(TARGET).elf $(TARGET).lss $(TARGET).sym \
	$(TARGET).hex $(TARGET).eep

directories:
	$(MKDIR) atmRelease

install:
ifdef ATM_AVRDUDE_PORT
	- $(AVRDUDE) -c$(ATM_AVRDUDE_PROGRAMMER) -P$(ATM_AVRDUDE_PORT) $(ATM_EXTRA_FLAGS) $(ATM_AVRDUDE_WRITE_FLASH)
endif

# Target: clean project.
clean:
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) -r atmRelease

.PHONY : directories clean install
