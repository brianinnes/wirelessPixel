#include <avr/io.h>

#include "atTinyGpio.h"

void attinyGpio::setPin(uint8_t P) {
  this->pin = P;
  DDRB |= (1<<P);
};

uint8_t attinyGpio::setPinState(uint8_t s) {
  if (0 == s) {
    PORTB &= (~(1<<this->pin));
  } else {
    PORTB |= (1<<this->pin);
  }
  return 0;
}
