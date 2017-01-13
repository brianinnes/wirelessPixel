#include "nrf24l01Data.h"
#include "raspberryPiSpi.h"
#include "raspberryPiGpio.h"
#include <iostream>

using namespace std;

int main(void)
{
	cout << "**Wireless Pixel Receiver**" << endl;
	Gpio *g = new RaspberryPiGpio();
	g->setPin(25);
	nrf24l01 *rf24 = new nrf24l01(new RaspberryPiSpi(), g);
	nrf24l01Data *rf24d = new nrf24l01Data(rf24);

	rf24d->initialise();
	cout << "Starting to receive : " << endl;
	rf24d->startReceiving();

	while (true) {
		int len = rf24d->isMessageAvailable();
		if (0 < len) {
			uint8_t buf[len];
			for (int i = 0; i< len; i++) {
				buf[i] = 0x00;
			}
			rf24d->getMessage(buf, len);
			cout << "Message received : ";
			for (int a = 0; a < len; a++) {
				cout << (int)buf[a];
				cout << ", ";
			}
			cout << std::endl;
		}
	}

	return 0;
}
