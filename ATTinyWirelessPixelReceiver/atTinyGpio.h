/*
 * atTinyGpio.h
 *
 *  Created on: 27 Oct 2016
 *      Author: brian
 */

#ifndef ATTINYGPIO_H_
#define ATTINYGPIO_H_

#include "gpio.h"

class attinyGpio:public Gpio
{
public:
	attinyGpio();
	~attinyGpio();
	void setPin(uint8_t p);
	uint8_t setPinState(uint8_t s);

private:
	uint8_t pin;
};

inline attinyGpio::attinyGpio() {};
inline attinyGpio::~attinyGpio() {};

#endif /* ATTINYGPIO_H_ */
