#ifndef BDCSTWPTRANS_H
#define BDCSTWPTRANS_H

#include "../nrf24l01/spi.h"
#include "../nrf24l01/gpio.h"
#include "../nrf24l01/nrf24l01Data.h"


class bdcstWPTrans {
public:
	bdcstWPTrans(Spi *sp, Gpio *gp);
	~bdcstWPTrans();
	void init();
	void setColour(uint8_t col);
	void setColour(uint8_t col, uint16_t id);
	void fadeColour(uint8_t col, uint8_t time);
	void fadeColour(uint8_t col, uint8_t time, uint16_t id);
	void playSequence(uint8_t seq);
	void playSequence(uint8_t seq, uint16_t id);
	void playFadeSequence(uint8_t seq, uint8_t time);
	void playFadeSequence(uint8_t seq, uint8_t time, uint16_t id);
	void loopSequence(uint8_t seq);
	void loopSequence(uint8_t seq, uint16_t id);
	void loopFadeSequence(uint8_t seq, uint8_t time);
	void loopFadeSequence(uint8_t seq, uint8_t time, uint16_t id);
	void updateColour(uint8_t col, uint8_t r, uint8_t g, uint8_t b);
	void updateColour(uint8_t col, uint8_t r, uint8_t g, uint8_t b, uint16_t id);
	void updateSequence(uint8_t seq, uint8_t num, uint8_t steps[]);
	void updateSequence(uint8_t seq, uint8_t num, uint8_t steps[], uint16_t id);

private:
	Spi *sp;
	Gpio *gp;
	nrf24l01 *radio;
	nrf24l01Data *radioD;
};


#endif //BDCSTWPTRANS_H
