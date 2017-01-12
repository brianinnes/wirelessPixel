/*
 * nullGpio.h
 *
 *  Created on: 27 Oct 2016
 *      Author: brian
 */

#ifndef NULLGPIO_H_
#define NULLGPIO_H_

#include "gpio.h"

class nullGpio:public Gpio
{
public:
	nullGpio();
	~nullGpio();
	void setPin(uint8_t p);
	uint8_t setPinState(uint8_t s);

private:
	uint8_t pin;
};

inline nullGpio::nullGpio() {};
inline nullGpio::~nullGpio() {};
inline void nullGpio::setPin(uint8_t p) {};
inline uint8_t nullGpio::setPinState(uint8_t s) {return 0; };

#endif /* NULLGPIO_H_ */
