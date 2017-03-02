CXXSRC = raspberryPiSpi.cpp raspberryPiGpio.cpp raspberryPiLedControl.cpp raspberryPiPersist.cpp main.cpp
ARM_OBJS    = $(CXXSRC:%.cpp=rspRelease/%.o)
AR6_OBJS    = $(CXXSRC:%.cpp=rsp1Release/%.o)
RSP_TARGET = rspRelease/RpiWirelessPixelReceiver
RSP1_TARGET = rsp1Release/RpiWirelessPixelReceiver

include ../rules.mk
include ../local.mk

RSP_EXTRAINCDIRS = ../nrf24l01 ../bdcstWirelessPixelReceiver
RSP_LDFLAGS += -lbdcstWirelessPixelReceiver -L ../bdcstWirelessPixelReceiver/rspRelease -lnrf24l01 -L../nrf24l01/rspRelease
RSP1_EXTRAINCDIRS = ../nrf24l01 ../bdcstWirelessPixelReceiver
RSP1_LDFLAGS += -lbdcstWirelessPixelReceiver -L ../bdcstWirelessPixelReceiver/rsp1Release -lnrf24l01 -L../nrf24l01/rsp1Release

all: directories $(RSP_TARGET) $(RSP_TARGET).lss $(RSP_TARGET).sym $(RSP1_TARGET) $(RSP1_TARGET).lss $(RSP1_TARGET).sym

directories:
	$(MKDIR) rspRelease
	$(MKDIR) rsp1Release

install:
ifdef RSP_HOST
	- scp $(RSP_TARGET) $(RSP_USER)@$(RSP_HOST):$(RSP_DIRECTORY)/$(notdir $(RSP_TARGET))
endif
ifdef RSP1_HOST
	- scp $(RSP1_TARGET) $(RSP1_USER)@$(RSP1_HOST):$(RSP1_DIRECTORY)/$(notdir $(RSP1_TARGET))
endif

# Target: clean project.
clean:
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) -r rspRelease
	$(REMOVE) -r rsp1Release

.PHONY : directories clean install
