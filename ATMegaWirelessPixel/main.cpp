#include "bdcstWirelessPixelTransmitter.h"
#include "atMegaSpi.h"
#include "atMegaGpio.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

using namespace std;

int main(void)
{
	Gpio *ce = new atMegaGpio();
	ce->setPin(PB1); //d9
	bdcstWPTrans *pixel = new bdcstWPTrans(new ATMegaSpi(), ce);
	pixel->init();

	srand(57);

	while (true) {
		for (int i = 0; i < 10; i++) {
			uint8_t colour = (uint8_t)(rand() % 8);
			pixel->setColour(colour);
			_delay_ms(1000);
		}
		for (int i = 0; i < 10; i++) {
			uint8_t colour = (uint8_t)(rand() % 8);
			pixel->fadeColour(colour, 50);
			_delay_ms(1000);
		}
		pixel->loopSequence(0);
		_delay_ms(5000);
		pixel->loopFadeSequence(0, 50);
		_delay_ms(5000);
		pixel->setColour(0);
		_delay_ms(5000);

		pixel->updateColour(1, 128, 0, 0);
		pixel->updateColour(2, 0, 128, 0);
		pixel->updateColour(3, 0, 0, 128);
		pixel->updateColour(4, 128, 128, 0);
		pixel->updateColour(5, 128, 0, 128);
		pixel->updateColour(6, 0, 128, 128);
		pixel->updateColour(7, 128, 128, 128);

		for (int i = 0; i < 10; i++) {
			uint8_t colour = (uint8_t)(rand() % 8);
			pixel->setColour(colour);
			_delay_ms(1000);
		}
		for (int i = 0; i < 10; i++) {
			uint8_t colour = (uint8_t)(rand() % 8);
			pixel->fadeColour(colour, 50);
			_delay_ms(1000);
		}
		pixel->loopSequence(0);
		_delay_ms(5000);
		pixel->loopFadeSequence(0, 50);
		_delay_ms(5000);
		pixel->setColour(0);
		_delay_ms(5000);

		pixel->updateColour(1, 255, 0, 0);
		pixel->updateColour(2, 0, 255, 0);
		pixel->updateColour(3, 0, 0, 255);
		pixel->updateColour(4, 255, 255, 0);
		pixel->updateColour(5, 255, 0, 255);
		pixel->updateColour(6, 0, 255, 255);
		pixel->updateColour(7, 255, 255, 255);
	}

	delete pixel;
	pixel = NULL;
	delete ce;
	ce = NULL;

	return 0;
}
