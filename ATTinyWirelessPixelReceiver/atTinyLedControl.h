#ifndef ATTINYLEDCONT_H_
#define ATTINYLEDCONT_H_

#include "ledControl.h"
#include <util/delay.h>

class attinyLedControl:public LedControl
{
public:
  attinyLedControl(uint8_t numLeds);
  void setLed(uint8_t led, uint8_t r, uint8_t g, uint8_t b) override;
  void delay(uint16_t ms) override;
};

inline attinyLedControl::attinyLedControl(uint8_t numLeds) : LedControl(numLeds) {}

inline void attinyLedControl::delay(uint16_t ms) { while (ms--) {_delay_ms(1);}}

#endif // ATTINYLEDCONT_H_
