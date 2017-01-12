#include <string.h>
#include <stdlib.h>
#include <avr/io.h>

#include "atTinySpi.h"
//using namespace std;
#define SPI_MODE 0

ATTinySpi::ATTinySpi()
{
	this->g = new attinyGpio();
	this->g->setPin(PORTB3);
}

ATTinySpi::~ATTinySpi()
{
		delete this->g;
}


uint8_t ATTinySpi::init()
{
	this->g->setPinState(1);
	DDRB |= (1<<DDB2)|(1<<DDB1);
	USICR = (1<<USIWM0) | (1<<USICS1) | (SPI_MODE<<USICS0) | (1<<USICLK);
	return 0;
}

void ATTinySpi::close()
{
}

void ATTinySpi::setCmd(uint8_t cmd)
{
	this->g->setPinState(0);
	memset(this->buffer, 0, sizeof this->buffer);
	this->buffer[0] = cmd;
}

void ATTinySpi::setCmdData(uint8_t *buf, uint8_t len)
{
	memcpy(this->buffer+1, buf, len);
}

uint8_t ATTinySpi::getStatus() {
	return this->buffer[0];
}

void ATTinySpi::getCmdData(uint8_t *buf, uint8_t len)
{
	memcpy(buf, &this->buffer[1], len);
}

uint8_t ATTinySpi::spiTransfer(uint8_t len)
{
	for (int i = 0; i < len; i++) {
		this->buffer[i] = this->transfer(this->buffer[i]);
	}
	this->g->setPinState(1);
	return buffer[0];
}

uint8_t ATTinySpi::transfer(uint8_t data)
{
	  USIDR = data;
	  USISR = _BV(USIOIF);
	  do
	    USICR |= _BV(USITC);
	  while ((USISR & _BV(USIOIF)) == 0);
	  return USIDR;
}
