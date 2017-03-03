#ifndef PERSIST_H
#define PERSIST_H

#define MAXSEQ 8
#define STDITEMS 6
//#define RGBITEMS 3


typedef struct StdSequence {
	uint8_t numItems[MAXSEQ];
	uint8_t items[MAXSEQ*STDITEMS];
} StdSequence;

//typedef struct RGBSequence {
//	uint8_t numItems[MAXSEQ];
//	uint8_t items[MAXSEQ*RGBITEMS*5];
//} RGBSequence;

class Persist {
public:
  virtual uint16_t getGID() = 0;
  virtual void setGID(uint16_t col) = 0;
  virtual void getStandardColours(uint8_t *buff) = 0;
  virtual void setStandardColours(uint8_t *buff) = 0;
	//virtual void getSequences(StdSequence *std, RGBSequence *rgb) = 0;
  //virtual void setSequences(StdSequence *std, RGBSequence *rgb) = 0;
  virtual void getSequences(StdSequence *std) = 0;
  virtual void setSequences(StdSequence *std) = 0;
};

#endif //PERSIST_H
