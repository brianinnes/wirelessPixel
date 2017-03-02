include defs.mk

# Default target: make program!
all: begin gccversion nrf24l01 bdcstWirelessPixelReceiver \
	bdcstWirelessPixelTransmitter ATTinyWirelessPixelReceiver \
	ATMegaWirelessPixel RpiWirelessPixel RpiWirelessPixelReceiver end

begin:
	@echo
	@echo $(MSG_BEGIN)

finished:
	@echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_END)
	@echo

nrf24l01:
	$(MAKE) -w -C nrf24l01 all

bdcstWirelessPixelReceiver:
	$(MAKE) -w -C bdcstWirelessPixelReceiver all

bdcstWirelessPixelTransmitter:
		$(MAKE) -w -C bdcstWirelessPixelTransmitter all

ATTinyWirelessPixelReceiver:
	$(MAKE) -w -C ATTinyWirelessPixelReceiver all

ATMegaWirelessPixel:
	$(MAKE) -w -C ATMegaWirelessPixel all

RpiWirelessPixel:
	$(MAKE) -w -C RpiWirelessPixel all

RpiWirelessPixelReceiver:
	$(MAKE) -w -C RpiWirelessPixelReceiver all

# Display compiler version information.
gccversion :
	@$(CC) --version
	@$(CXX) --version

install: nrf24l01 bdcstWirelessPixelReceiver bdcstWirelessPixelTransmitter ATTinyWirelessPixelReceiver ATMegaWirelessPixel RpiWirelessPixel RpiWirelessPixelReceiver
	@echo $(MSG_INSTALLING)
	$(MAKE) -w -C ATTinyWirelessPixelReceiver install
	$(MAKE) -w -C ATMegaWirelessPixel install
	$(MAKE) -w -C RpiWirelessPixel install
	$(MAKE) -w -C RpiWirelessPixelReceiver install

# Target: clean project.
clean: begin clean_list finished end

clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).eep
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).cof
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).a90
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lnk
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(OBJ)
	$(REMOVE) $(LST)
	$(REMOVE) $(SRC:.c=.s)
	$(REMOVE) $(SRC:.c=.d)
	$(REMOVE) *~
	$(MAKE) -w -C nrf24l01 clean
	$(MAKE) -w -C bdcstWirelessPixelReceiver clean
	$(MAKE) -w -C bdcstWirelessPixelTransmitter clean
	$(MAKE) -w -C ATTinyWirelessPixelReceiver clean
	$(MAKE) -w -C ATMegaWirelessPixel clean
	$(MAKE) -w -C RpiWirelessPixel clean
	$(MAKE) -w -C RpiWirelessPixelReceiver clean

# Listing of phony targets.
.PHONY : all gccversion clean clean_list nrf24l01 bdcstWirelessPixelReceiver \
		bdcstWirelessPixelTransmitter ATTinyWirelessPixelReceiver \
		ATMegaWirelessPixel RpiWirelessPixel RpiWirelessPixelReceiver \
		install begin finished end
