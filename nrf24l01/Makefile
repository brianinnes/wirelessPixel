include ../rules.mk

CXXSRC = nrf24l01.cpp nrf24l01Data.cpp
ATM_OBJS    = $(CXXSRC:%.cpp=atmRelease/%.o)
ATT_OBJS    = $(CXXSRC:%.cpp=attRelease/%.o)
RSP_OBJS    = $(CXXSRC:%.cpp=rspRelease/%.o)
RSP1_OBJS   = $(CXXSRC:%.cpp=rsp1Release/%.o)

all: directories atmRelease/libnrf24l01.a attRelease/libnrf24l01.a rspRelease/libnrf24l01.a rsp1Release/libnrf24l01.a

directories:
	$(MKDIR) atmRelease
	$(MKDIR) attRelease
	$(MKDIR) rspRelease
	$(MKDIR) rsp1Release

atmRelease/libnrf24l01.a: $(ATM_OBJS)
	$(AVR_AR) -rcs $@ $^

attRelease/libnrf24l01.a: $(ATT_OBJS)
		$(AVR_AR) -rcs $@ $^

rspRelease/libnrf24l01.a: $(RSP_OBJS)
		$(ARM_AR) -rcs $@ $^

rsp1Release/libnrf24l01.a: $(RSP1_OBJS)
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
