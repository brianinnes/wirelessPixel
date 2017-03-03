/*
 * raspberryPiGpio.h
 *
 *  Created on: 27 Oct 2016
 *      Author: brian
 */

#ifndef RASPBERRYPIGPIO_H_
#define RASPBERRYPIGPIO_H_

#include "gpio.h"

class RaspberryPiGpio:public Gpio
{
public:
	RaspberryPiGpio();
	~RaspberryPiGpio();
	void setPin(uint8_t p) override;
	uint8_t setPinState(uint8_t s) override;

private:
	int pin;
	int pin_fd;
};


#endif /* RASPBERRYPIGPIO_H_ */
