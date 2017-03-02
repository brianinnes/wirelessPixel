#include <stdint.h>
#include "atTinyLedControl.h"

extern "C" {
void output_grb(uint8_t * ptr, uint16_t count);
}

void attinyLedControl::setLed(uint8_t led, uint8_t r, uint8_t g, uint8_t b) {
  LedControl::setLed(led, r, g, b);
  output_grb(this->ledBuff, this->numLEDs * 3);
}
