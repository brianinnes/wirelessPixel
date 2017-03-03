#include <stdint.h>
#include <avr/eeprom.h>
#include "atTinyPersist.h"

uint16_t EEMEM gID = 0;
uint8_t EEMEM stdColours[8][3] = {
  {0, 0, 0},
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255},
  {255, 255, 0},
  {255,0, 255},
  {0, 255, 255},
  {255, 255, 255}};
StdSequence EEMEM stdSequences = {
    {4, 4, 0, 0, 0, 0, 0, 0},
    {(1<<5)+5, (2<<5)+5, (3<<5)+5, (0<<5)+1, (4<<5)+2, (5<<5)+2, (6<<5)+2, (7<<5)+2}};

uint16_t attinyPersist::getGID() {
  return eeprom_read_word(&gID);;
}

void attinyPersist::setGID(uint16_t id) {
  eeprom_update_word(&gID, id);
}

void attinyPersist::getStandardColours(uint8_t *buff) {
  eeprom_read_block((void*)buff, (const void*)stdColours , 24);
}

void attinyPersist::setStandardColours(uint8_t *buff) {
  eeprom_update_block((const void*)buff, (void*)stdColours, 24);
}

void attinyPersist::getSequences(StdSequence *std) {
  eeprom_read_block((void*)std, (const void*)&stdSequences , sizeof(StdSequence));
}

void attinyPersist::setSequences(StdSequence *std) {
  eeprom_update_block((const void*)std, (void*)&stdSequences , sizeof(StdSequence));
}
