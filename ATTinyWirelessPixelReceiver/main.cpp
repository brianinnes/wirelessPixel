#include "bdcstWirelessPixelReceiver.h"
#include "nullGpio.h"
#include "atTinySpi.h"
#include "atTinyPersist.h"
#include "attinyLedControl.h"
#include <avr/io.h>

#define NUM_WS2812 1


int main(void)
{
  DDRB = (1<<DDB4);
  PORTB |= (1<<PORTB4);

  Spi *s = new ATTinySpi();
	Gpio *g = new nullGpio();
  bdcstWPRec *pixels = new bdcstWPRec(s, g, new attinyPersist(), new attinyLedControl(NUM_WS2812));
  pixels->init();
  pixels->_playStdSequence(0);

	while (true) {
		pixels->checkAndProcessMessages();
	}

	return 0;
}
