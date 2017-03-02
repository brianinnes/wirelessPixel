include ../rules.mk

CXXSRC = bdcstWirelessPixelTransmitter.cpp
ATM_OBJS    = $(CXXSRC:%.cpp=atmRelease/%.o)
ATT_OBJS    = $(CXXSRC:%.cpp=attRelease/%.o)
RSP_OBJS    = $(CXXSRC:%.cpp=rspRelease/%.o)
RSP1_OBJS   = $(CXXSRC:%.cpp=rsp1Release/%.o)

all: directories atmRelease/libbdcstWirelessPixelTransmitter.a attRelease/libbdcstWirelessPixelTransmitter.a rspRelease/libbdcstWirelessPixelTransmitter.a rsp1Release/libbdcstWirelessPixelTransmitter.a

directories:
	$(MKDIR) atmRelease
	$(MKDIR) attRelease
	$(MKDIR) rspRelease
	$(MKDIR) rsp1Release

atmRelease/libbdcstWirelessPixelTransmitter.a: $(ATM_OBJS)
	$(AVR_AR) -rcs $@ $^

attRelease/libbdcstWirelessPixelTransmitter.a: $(ATT_OBJS)
		$(AVR_AR) -rcs $@ $^

rspRelease/libbdcstWirelessPixelTransmitter.a: $(RSP_OBJS)
		$(ARM_AR) -rcs $@ $^

rsp1Release/libbdcstWirelessPixelTransmitter.a: $(RSP1_OBJS)
		$(AR6_AR) -rcs $@ $^


# Target: clean project.
clean:
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) -r atmRelease
	$(REMOVE) -r attRelease
	$(REMOVE) -r rspRelease
	$(REMOVE) -r rsp1Release

.PHONY : directories
