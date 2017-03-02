#ifndef ATTINYPERSIST_H_
#define ATTINYPERSIST_H_

#include "persist.h"

class attinyPersist:public Persist
{
  uint16_t getGID() override;
  void setGID(uint16_t col) override;
  uint8_t *getStandardColours() override;
  void setStandardColours(uint8_t col[]) override;
  uint8_t *getStandardSequence(uint8_t s) override;
  void setStandardSequence(uint8_t s, uint8_t seq[]) override;
  uint8_t *getRGBSequence(uint8_t s) override;
  void setRGBSequence(uint8_t s, uint8_t seq[]) override;
};

#endif // ATTINYPERSIST_H_
