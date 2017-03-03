#ifndef RPIPERSIST_H_
#define RPIPERSIST_H_

#include "persist.h"
#include <string>

class raspberryPiPersist:public Persist
{
public:
  raspberryPiPersist();
  uint16_t getGID() override;
  void setGID(uint16_t col) override;
  void getStandardColours(uint8_t *buff) override;
  void setStandardColours(uint8_t *buff) override;
//  void getSequences(StdSequence *std, RGBSequence *rgb) override;
//  void setSequences(StdSequence *std, RGBSequence *rgb) override;
  void getSequences(StdSequence *std) override;
  void setSequences(StdSequence *std) override;
private:
  std::string path;
  std::string gIDPath;
  std::string stdColourPath;
  std::string stdSeqPath;
  std::string rgbSeqPath;
};

#endif // RPIPERSIST_H_
