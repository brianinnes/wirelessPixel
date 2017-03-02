#ifndef PERSIST_H
#define PERSIST_H

class Persist {
public:
  virtual uint16_t getGID() = 0;
  virtual void setGID(uint16_t col) = 0;
  virtual uint8_t *getStandardColours() = 0;
  virtual void setStandardColours(uint8_t col[]) = 0;
  virtual uint8_t *getStandardSequence(uint8_t s) = 0;
  virtual void setStandardSequence(uint8_t s, uint8_t seq[]) = 0;
  virtual uint8_t *getRGBSequence(uint8_t s) = 0;
  virtual void setRGBSequence(uint8_t s, uint8_t seq[]) = 0;
};

#endif //PERSIST_H
