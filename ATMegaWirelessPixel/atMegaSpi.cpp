#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>

#include "atMegaSpi.h"
//using namespace std;
#define DDR_SPI     DDRB
#define DD_MISO     DDB4
#define DD_MOSI     DDB3
#define DD_SS       DDB2
#define DD_SCK      DDB5

ATMegaSpi::ATMegaSpi()
{
	this->csn = new atMegaGpio();
	this->csn->setPin(PORTB2);
}

ATMegaSpi::~ATMegaSpi()
{
		delete this->csn;
}


uint8_t ATMegaSpi::init()
{
	this->csn->setPinState(1);
	DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK);
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
	return 0;
}

void ATMegaSpi::close()
{
}

void ATMegaSpi::setCmd(uint8_t cmd)
{
	this->csn->setPinState(0);
	memset(this->buffer, 0, sizeof this->buffer);
	this->buffer[0] = cmd;
}

void ATMegaSpi::setCmdData(uint8_t *buf, uint8_t len)
{
	memcpy(this->buffer+1, buf, len);
}

uint8_t ATMegaSpi::getStatus() {
	return this->buffer[0];
}

void ATMegaSpi::getCmdData(uint8_t *buf, uint8_t len)
{
	memcpy(buf, &this->buffer[1], len);
}

uint8_t ATMegaSpi::spiTransfer(uint8_t len)
{
	for (int i = 0; i < len; i++) {
		this->buffer[i] = this->transfer(this->buffer[i]);
	}
	this->csn->setPinState(1);
	return buffer[0];
}

uint8_t ATMegaSpi::transfer(uint8_t data)
{
	  SPDR = data;
	  while(!(SPSR & (1<<SPIF)))
			;
	  return SPDR;
}
