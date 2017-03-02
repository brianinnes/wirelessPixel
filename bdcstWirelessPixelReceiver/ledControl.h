#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <stdlib.h>

class LedControl {
public:
  LedControl(uint8_t numLeds);
  ~LedControl();
  virtual void init();
  virtual void setLed(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
  virtual void delay(uint16_t ms) = 0;
protected:
  uint8_t numLEDs;
  uint8_t *ledBuff;
};

inline LedControl::LedControl(uint8_t numLeds) {
  this->numLEDs = numLeds;
  this->ledBuff = 0;
}

inline LedControl::~LedControl() {
  if (this->ledBuff) {
		free(this->ledBuff);
	}
  this->ledBuff = 0;
}

inline void LedControl::init() {
  if (0 == this->ledBuff) {
    this->ledBuff = (uint8_t*)malloc(this->numLEDs * 3);
  }
}

inline void LedControl::setLed(uint8_t led, uint8_t r, uint8_t g, uint8_t b)
{
  uint16_t index = 3 * led;
  this->ledBuff[index++] = g;
  this->ledBuff[index++] = r;
  this->ledBuff[index] = b;
}

#endif //LEDCONTROL_H
