#include "bdcstWirelessPixelTransmitter.h"

#define BDCAST (uint8_t)0x00
#define GROUP (uint8_t)0x80
#define C_SETCOLOUR (uint8_t)0x00
#define C_FADECOLOUT (uint8_t)0x08
#define C_PSEQ (uint8_t)0x10
#define C_PFSEQ (uint8_t)0x18
#define C_LSEQ (uint8_t)0x20
#define C_LFSEQ (uint8_t)0x28
#define C_UCOLOUR (uint8_t)0x30
#define C_USEQ (uint8_t)0x38
#define C_MISCCOMMAND (uint8_t)0x40
#define C_PLAYRGBSEQ (uint8_t)0x50
#define C_FADERGBSEQ (uint8_t)0x58
#define C_LOOPRGBSEQ (uint8_t)0x60
#define C_LOOPFADERGBSEQ (uint8_t)0x68
#define C_UPDATERGBSEQ (uint8_t)0x70
#define C_UPDATERGBSEQCONT (uint8_t)0x71


bdcstWPTrans::bdcstWPTrans(Spi *sp, Gpio *gp) {
  this->sp = sp;
  this->gp = gp;
}

bdcstWPTrans::~bdcstWPTrans() {

}

void bdcstWPTrans::init() {
  this->radio = new nrf24l01(this->sp, this->gp);
	this->radioD = new nrf24l01Data(this->radio);
	this->radioD->initialise();
}

void bdcstWPTrans::setColour(uint8_t col) {
  uint8_t msg = BDCAST | C_SETCOLOUR | (col & 0x07);
  this->radioD->broadcast(&msg, 1);
}

void bdcstWPTrans::setColour(uint8_t col, uint16_t id) {
  uint8_t cmd = GROUP | C_SETCOLOUR | (col & 0x07);
  uint8_t msg[] = { cmd, (uint8_t)(id >> 8), (uint8_t)id };
  this->radioD->broadcast(msg, 3);
}

void bdcstWPTrans::fadeColour(uint8_t col, uint8_t time) {
  uint8_t cmd = BDCAST | C_FADECOLOUT | (col & 0x07);
  uint8_t msg[] = { cmd, time};
  this->radioD->broadcast(msg, 2);
}

void bdcstWPTrans::fadeColour(uint8_t col, uint8_t time, uint16_t id) {
  uint8_t cmd = GROUP | C_FADECOLOUT | (col & 0x07);
  uint8_t msg[] = { cmd, (uint8_t)(id >> 8), (uint8_t)id, time };
  this->radioD->broadcast(msg, 4);
}

void bdcstWPTrans::playSequence(uint8_t seq) {
  uint8_t msg = BDCAST | C_PSEQ | (seq & 0x07);
  this->radioD->broadcast(&msg, 1);
}

void bdcstWPTrans::playSequence(uint8_t seq, uint16_t id) {
  uint8_t cmd = GROUP | C_PSEQ | (seq & 0x07);
  uint8_t msg[] = { cmd, (uint8_t)(id >> 8), (uint8_t)id };
  this->radioD->broadcast(msg, 3);
}

void bdcstWPTrans::playFadeSequence(uint8_t seq, uint8_t time) {
  uint8_t cmd = BDCAST | C_PFSEQ | (seq & 0x07);
  uint8_t msg[] = { cmd, time};
  this->radioD->broadcast(msg, 2);
}

void bdcstWPTrans::playFadeSequence(uint8_t seq, uint8_t time, uint16_t id) {
  uint8_t cmd = GROUP | C_PFSEQ | (seq & 0x07);
  uint8_t msg[] = { cmd, (uint8_t)(id >> 8), (uint8_t)id, time };
  this->radioD->broadcast(msg, 4);
}

void bdcstWPTrans::loopSequence(uint8_t seq) {
  uint8_t msg = BDCAST | C_LSEQ | (seq & 0x07);
  this->radioD->broadcast(&msg, 1);
}

void bdcstWPTrans::loopSequence(uint8_t seq, uint16_t id) {
  uint8_t cmd = GROUP | C_LSEQ | (seq & 0x07);
  uint8_t msg[] = { cmd, (uint8_t)(id >> 8), (uint8_t)id };
  this->radioD->broadcast(msg, 3);
}

void bdcstWPTrans::loopFadeSequence(uint8_t seq, uint8_t time) {
  uint8_t cmd = BDCAST | C_LFSEQ | (seq & 0x07);
  uint8_t msg[] = { cmd, time};
  this->radioD->broadcast(msg, 2);
}

void bdcstWPTrans::loopFadeSequence(uint8_t seq, uint8_t time, uint16_t id) {
  uint8_t cmd = GROUP | C_LFSEQ | (seq & 0x07);
  uint8_t msg[] = { cmd, (uint8_t)(id >> 8), (uint8_t)id, time };
  this->radioD->broadcast(msg, 4);
}

void bdcstWPTrans::updateColour(uint8_t col, uint8_t r, uint8_t g, uint8_t b) {
  uint8_t cmd = BDCAST | C_UCOLOUR | (col & 0x07);
  uint8_t msg[] = { cmd, r, g, b };
  this->radioD->broadcast(msg, 4);
}

void bdcstWPTrans::updateColour(uint8_t col, uint8_t r, uint8_t g, uint8_t b, uint16_t id) {
  uint8_t cmd = GROUP | C_UCOLOUR | (col & 0x07);
  uint8_t msg[] = { cmd, (uint8_t)(id >> 8), (uint8_t)id, r, g, b };
  this->radioD->broadcast(msg, 6);
}

void bdcstWPTrans::updateSequence(uint8_t seq, uint8_t num, uint8_t steps[]) {
  uint8_t msg[2+num];
  msg[0] = BDCAST | C_USEQ | (seq & 0x07);
  msg[1] = num;
  for (uint8_t i = 0; i< num; i++) {
    msg[2+i] = steps[i];
  }
  this->radioD->broadcast(msg, 2+num);
}

void bdcstWPTrans::updateSequence(uint8_t seq, uint8_t num, uint8_t steps[], uint16_t id) {
  uint8_t msg[4+num];
  msg[0] = GROUP | C_USEQ | (seq & 0x07);
  msg[1] = (uint8_t)(id >> 8);
  msg[2] = (uint8_t)id;
  msg[3] = num;
  for (uint8_t i = 0; i< num; i++) {
    msg[4+i] = steps[i];
  }

  this->radioD->broadcast(msg, 4+num);}
