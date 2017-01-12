/*
 * gpio.h
 *
 *  Created on: 26 Oct 2016
 *      Author: brian
 */

#ifndef NRF_GPIO_H_
#define NRF_GPIO_H_

#include<stdint.h>


class Gpio
{
public:
	virtual ~Gpio() {};
	virtual void setPin(uint8_t p) = 0;
	virtual uint8_t setPinState(uint8_t s) = 0;
};

#endif /* NRF_GPIO_H_ */
