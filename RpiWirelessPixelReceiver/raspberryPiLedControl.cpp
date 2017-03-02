#include <stdint.h>
#include <iostream>
#include "raspberryPiLedControl.h"

using namespace std;

void RaspberryPiLedControl::setLed(uint8_t led, uint8_t r, uint8_t g, uint8_t b) {
  LedControl::setLed(led, r, g, b);
  // Data stored in ledBuff grb to enable easy transmission to RGB LED chain
  cout << "Setting LEDs to : ";
  cout <<(int)this->ledBuff[1] << ", ";
  cout <<(int)this->ledBuff[0] << ", ";
  cout <<(int)this->ledBuff[2] << std::endl;
}
