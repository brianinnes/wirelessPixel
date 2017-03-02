#ifndef RPILEDCONT_H_
#define RPILEDCONT_H_

#include <chrono>
#include <thread>
#include "ledControl.h"

class RaspberryPiLedControl:public LedControl
{
public:
  RaspberryPiLedControl(uint8_t numLeds);
  void setLed(uint8_t led, uint8_t r, uint8_t g, uint8_t b) override ;
  void delay(uint16_t ms) override;
};

using namespace std;

inline RaspberryPiLedControl::RaspberryPiLedControl(uint8_t numLeds) : LedControl(numLeds) {}

inline void RaspberryPiLedControl::delay(uint16_t ms) {this_thread::sleep_for(chrono::milliseconds(ms));}

#endif // RPILEDCONT_H_
