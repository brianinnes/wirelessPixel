#ifndef BDCSTWPREC_H
#define BDCSTWPREC_H

#include "../nrf24l01/spi.h"
#include "../nrf24l01/gpio.h"
#include "../nrf24l01/nrf24l01Data.h"
#include "persist.h"
#include "ledControl.h"

#define MAXSEQ 8

typedef struct stdSequence {
	uint8_t numItems[MAXSEQ];
	uint8_t *items[MAXSEQ];
} stdSequence;

class bdcstWPRec {
public:
	bdcstWPRec(Spi *sp, Gpio *gp, Persist *st, LedControl *ledControl);
	~bdcstWPRec();
	void init();
	void checkAndProcessMessages();
	void _setLEDColour(uint8_t r, uint8_t g, uint8_t b);
	void _fadeLEDColour(uint8_t r, uint8_t g, uint8_t b, uint8_t time);
	void _playStdSequence(uint8_t s);
	void _fadeStdSequence(uint8_t s, uint8_t time);
protected:
	void setColour(uint8_t *buf);
	void fadeColour(uint8_t *buf, uint8_t len);
	void playSeq(uint8_t *buf);
	void fadeSeq(uint8_t *buf, uint8_t len);
	void loopSeq(uint8_t *buf);
	void loopFadeSeq(uint8_t *buf, uint8_t len);
	void updateColour(uint8_t *buf, uint8_t len);
	void updateSeq(uint8_t *buf, uint8_t len);
	void miscCommand(uint8_t *buf, uint8_t len);
	void playRGBSeq(uint8_t *buf);
	void fadeRGBSeq(uint8_t *buf, uint8_t len);
	void loopRGBSeq(uint8_t *buf);
	void loopFadeRGBSeq(uint8_t *buf, uint8_t len);
	void updateRGBSeq(uint8_t *buf, uint8_t len);
	void updateRGBSeqCont(uint8_t *buf, uint8_t len);
private:
	Spi *sp;
	Gpio *gp;
	nrf24l01 *rf24;
  nrf24l01Data *rf24d;
	Persist *st;
	LedControl *lc;
	uint8_t stdColours[8][3];
	stdSequence stdSequences;
	uint8_t currColours[3] = {0, 0, 0};
	uint16_t gID;
};


#endif //BDCSTWPREC_H
