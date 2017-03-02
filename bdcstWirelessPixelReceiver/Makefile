include ../rules.mk

CXXSRC = bdcstWirelessPixelReceiver.cpp
ATM_OBJS    = $(CXXSRC:%.cpp=atmRelease/%.o)
ATT_OBJS    = $(CXXSRC:%.cpp=attRelease/%.o)
RSP_OBJS    = $(CXXSRC:%.cpp=rspRelease/%.o)
RSP1_OBJS   = $(CXXSRC:%.cpp=rsp1Release/%.o)

all: directories atmRelease/libbdcstWirelessPixelReceiver.a attRelease/libbdcstWirelessPixelReceiver.a rspRelease/libbdcstWirelessPixelReceiver.a rsp1Release/libbdcstWirelessPixelReceiver.a

directories:
	$(MKDIR) atmRelease
	$(MKDIR) attRelease
	$(MKDIR) rspRelease
	$(MKDIR) rsp1Release

atmRelease/libbdcstWirelessPixelReceiver.a: $(ATM_OBJS)
	$(AVR_AR) -rcs $@ $^

attRelease/libbdcstWirelessPixelReceiver.a: $(ATT_OBJS)
		$(AVR_AR) -rcs $@ $^

rspRelease/libbdcstWirelessPixelReceiver.a: $(RSP_OBJS)
		$(ARM_AR) -rcs $@ $^

rsp1Release/libbdcstWirelessPixelReceiver.a: $(RSP1_OBJS)
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
