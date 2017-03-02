/*
 * atMegaGpio.h
 *
 *  Created on: 27 Oct 2016
 *      Author: brian
 */

#ifndef ATMEGAGPIO_H_
#define ATMEGAGPIO_H_

#include "gpio.h"

class atMegaGpio:public Gpio
{
public:
	atMegaGpio();
	~atMegaGpio();
	void setPin(uint8_t p) override;
	uint8_t setPinState(uint8_t s) override;

private:
	uint8_t pin;
};

inline atMegaGpio::atMegaGpio() {};
inline atMegaGpio::~atMegaGpio() {};

#endif /* ATTINYGPIO_H_ */
