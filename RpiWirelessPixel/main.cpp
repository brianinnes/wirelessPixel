#include "bdcstWirelessPixelTransmitter.h"
#include "raspberryPiSpi.h"
#include "raspberryPiGpio.h"
//#include <unistd.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <time.h>

using namespace std;

int main(void)
{
	Gpio *g = new RaspberryPiGpio();
	g->setPin(25);
	bdcstWPTrans *pixel = new bdcstWPTrans(new RaspberryPiSpi(), g);

	pixel->init();

	srand(time(NULL));

	while (true) {
		for (int i = 0; i < 10; i++) {
			uint8_t colour = (uint8_t)(rand() % 8);
			cout << "Message sent : ";
			cout << "Set Colour = ";
			cout << (int)colour;
			cout << std::endl;
			pixel->setColour(colour);
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
		for (int i = 0; i < 10; i++) {
			uint8_t colour = (uint8_t)(rand() % 8);
			cout << "Message sent : ";
			cout << "Fade Colour to = ";
			cout << (int)colour;
			cout << std::endl;
			pixel->fadeColour(colour, 50);
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
		cout << "Loop Sequence" << std::endl;
		pixel->loopSequence(0);
		this_thread::sleep_for(chrono::milliseconds(5000));
		cout << "Loop Fading Sequence" << std::endl;
		pixel->loopFadeSequence(0, 50);
		this_thread::sleep_for(chrono::milliseconds(5000));
		pixel->setColour(0);
		this_thread::sleep_for(chrono::milliseconds(5000));

		cout << "Half brightness colours" << std::endl;
		pixel->updateColour(1, 128, 0, 0);
		pixel->updateColour(2, 0, 128, 0);
		pixel->updateColour(3, 0, 0, 128);
		pixel->updateColour(4, 128, 128, 0);
		pixel->updateColour(5, 128, 0, 128);
		pixel->updateColour(6, 0, 128, 128);
		pixel->updateColour(7, 128, 128, 128);

		for (int i = 0; i < 10; i++) {
			uint8_t colour = (uint8_t)(rand() % 8);
			cout << "Message sent : ";
			cout << "Set Colour = ";
			cout << (int)colour;
			cout << std::endl;
			pixel->setColour(colour);
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
		for (int i = 0; i < 10; i++) {
			uint8_t colour = (uint8_t)(rand() % 8);
			cout << "Message sent : ";
			cout << "Fade Colour to = ";
			cout << (int)colour;
			cout << std::endl;
			pixel->fadeColour(colour, 50);
			this_thread::sleep_for(chrono::milliseconds(1000));
		}
		cout << "Loop Sequence" << std::endl;
		pixel->loopSequence(0);
		this_thread::sleep_for(chrono::milliseconds(5000));
		cout << "Loop Fading Sequence" << std::endl;
		pixel->loopFadeSequence(0, 50);
		this_thread::sleep_for(chrono::milliseconds(5000));
		pixel->setColour(0);
		this_thread::sleep_for(chrono::milliseconds(5000));

		cout << "Full brightness colours" << std::endl;
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
	delete g;
	g = NULL;

	return 0;
}
