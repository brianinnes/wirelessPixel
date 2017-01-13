#include "nrf24l01Data.h"
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
	nrf24l01 *rf24 = new nrf24l01(new ATMegaSpi(), ce);
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
	delete ce;
	ce = NULL;

	return 0;
}
