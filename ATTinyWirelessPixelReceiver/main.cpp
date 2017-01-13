#include "nrf24l01Data.h"
#include "nullGpio.h"
#include "atTinySpi.h"
#include <avr/io.h>
#include <util/delay.h>


typedef uint8_t   u8;
typedef uint16_t  u16;

#define NUM_WS2812    1
#define NUM_LEDS      (NUM_WS2812*3)

#define setRGB(l, r, g, b, delay) set_color(bufLED, l, r, g, b); \
output_grb(bufLED, sizeof(bufLED)); \
_delay_ms(delay);

// declaration of our ASM function
extern "C" {
void output_grb(u8 * ptr, u16 count);
}

u8 bufLED[NUM_LEDS];

void set_color(u8 *p_buf, u8 led, u8 r, u8 g, u8 b)
{
  u16 index = 3*led;
  p_buf[index++] = g;
  p_buf[index++] = r;
  p_buf[index] = b;
}

//void setRGB(uint8_t r, uint8_t g, uint8_t b, const int delay) {
//  set_color(bufLED, 0, r, g, b);
//  output_grb(bufLED, sizeof(bufLED));
//  _delay_ms(delay);
//}

int main(void)
{
	DDRB = (1<<DDB4);
	PORTB |= (1<<PORTB4);

  setRGB(0, 0x00, 0x00, 0x00, 10);
  setRGB(0, 0xFF, 0x00, 0x00, 500);
  setRGB(0, 0x00, 0xFF, 0x00, 500);
  setRGB(0, 0x00, 0x00, 0xFF, 500);
  setRGB(0, 0xFF, 0xFF, 0xFF, 500);
  setRGB(0, 0x00, 0x00, 0x00, 10);

	Gpio *g = new nullGpio();
	nrf24l01 *rf24 = new nrf24l01(new ATTinySpi(), g);
	nrf24l01Data *rf24d = new nrf24l01Data(rf24);
	rf24d->initialise();
	rf24d->startReceiving();

	while (true) {

		int len = rf24d->isMessageAvailable();
		if (0 < len) {

			uint8_t buf[len];
			for (int i = 0; i< len; i++) {
				buf[i] = 0x00;
			}
			rf24d->getMessage(buf, len);

			if ((len >=4) && (0 == buf[0])) {
        set_color(bufLED, 0, buf[1], buf[2], buf[3]); \
        output_grb(bufLED, sizeof(bufLED));
			}
		}
	}

	return 0;
}
