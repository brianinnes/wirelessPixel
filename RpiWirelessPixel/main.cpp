#include "nrf24l01Data.h"
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
	nrf24l01 *rf24 = new nrf24l01(new RaspberryPiSpi(), g);
	nrf24l01Data *rf24d = new nrf24l01Data(rf24);

	rf24d->initialise();

	srand(time(NULL));

	char msg[] = "AAA";

	char i = 0;
	char j = 0;
	while (true) {
		//for (char i = 0; i < 20; i++) {
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

		cout << "Message sent : ";
		for (int a = 0; a < 3; a++) {
			cout << (int)msg[a];
			cout << ", ";
		}
		cout << std::endl;

		rf24d->broadcast((uint8_t *)msg, 3);
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
	delete rf24;
	rf24 = NULL;
	delete g;
	g = NULL;

	return 0;
}
