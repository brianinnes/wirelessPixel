/*
 * atMegaGpio.h
 *
 *  Created on: 27 Oct 2016
 *      Author: brian
 */

#ifndef ATMEGAGPIO_H_
#define ATMEGAGPIO_H_

#include "gpio.h"

class atmegaGpio:public Gpio
{
public:
	atmegaGpio();
	~atmegaGpio();
	void setPin(uint8_t p);
	uint8_t setPinState(uint8_t s);

private:
	uint8_t pin;
};

inline atmegaGpio::atmegaGpio() {};
inline atmegaGpio::~atmegaGpio() {};

#endif /* ATTINYGPIO_H_ */
