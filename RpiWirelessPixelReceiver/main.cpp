#include "bdcstWirelessPixelReceiver.h"
#include "raspberryPiSpi.h"
#include "raspberryPiGpio.h"
#include "raspberryPiPersist.h"
#include "raspberryPiLedControl.h"
#include <iostream>

using namespace std;

int main(void)
{
	cout << "**Wireless Pixel Receiver**" << endl;
	Gpio *g = new RaspberryPiGpio();
	g->setPin(25);

	bdcstWPRec *pixels = new bdcstWPRec(new RaspberryPiSpi(), g, new raspberryPiPersist(), new RaspberryPiLedControl(1));
	pixels->init();

	pixels->_playStdSequence(0);

	cout << "Starting to receive : " << endl;

	while (true) {
		pixels->checkAndProcessMessages();
	}

	return 0;
}
