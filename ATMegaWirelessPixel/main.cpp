/***********************************************************************
 * mcp3008SpiTest.cpp. Sample program that tests the mcp3008Spi class.
 * an mcp3008Spi class object (a2d) is created. the a2d object is instantiated
 * using the overloaded constructor. which opens the spidev0.0 device with
 * SPI_MODE_0 (MODE 0) (defined in linux/spi/spidev.h), speed = 1MHz &
 * bitsPerWord=8.
 *
 * call the spiWriteRead function on the a2d object 20 times. Each time make sure
 * that conversion is configured for single ended conversion on CH0
 * i.e. transmit ->  byte1 = 0b00000001 (start bit)
 *                   byte2 = 0b1000000  (SGL/DIF = 1, D2=D1=D0=0)
 *                   byte3 = 0b00000000  (Don't care)
 *      receive  ->  byte1 = junk
 *                   byte2 = junk + b8 + b9
 *                   byte3 = b7 - b0
 *
 * after conversion must merge data[1] and data[2] to get final result
 *
 *  http://www.hertaville.com/interfacing-an-spi-adc-mcp3008-chip-to-the-raspberry-pi-using-c.html
 *
 * *********************************************************************/

#include "nrf24l01Data.h"
#include "atMegaSpi.h"
#include "atMegaGpio.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

using namespace std;

int main(void)
{
	Gpio *g = new atmegaGpio();
	g->setPin(PB1); //d9
	nrf24l01 *rf24 = new nrf24l01(new ATMegaSpi(), g);
	nrf24l01Data *rf24d = new nrf24l01Data(rf24);

	rf24d->initialise();

	srand(57);

	char msg[] = "AAA";

	char i = 0;
	char j = 0;
	while (true) {
		i ++;
		j++;
		if (i > 5) {
			i = 0;
		}
		if (j > 2) {
			j = 0;
		}

		msg[0] = rand() % 200 + 50;
		msg[1] = rand() % 200 + 50;
		msg[2] = rand() % 200 + 50;

		rf24d->broadcast((uint8_t *)msg, 3);
		_delay_ms(1000);
	}
	
	delete rf24;
	rf24 = NULL;
	delete g;
	g = NULL;

	return 0;
}
