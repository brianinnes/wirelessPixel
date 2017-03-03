#ifndef ATTINYPERSIST_H_
#define ATTINYPERSIST_H_

#include "persist.h"

class attinyPersist:public Persist
{
  uint16_t getGID() override;
  void setGID(uint16_t col) override;
  void getStandardColours(uint8_t *buff) override;
  void setStandardColours(uint8_t *buff) override;
//  void getSequences(StdSequence *std, RGBSequence *rgb) override;
//  void setSequences(StdSequence *std, RGBSequence *rgb) override;
  void getSequences(StdSequence *std) override;
  void setSequences(StdSequence *std) override;
};

#endif // ATTINYPERSIST_H_
