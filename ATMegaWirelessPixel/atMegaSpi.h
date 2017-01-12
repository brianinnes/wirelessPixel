#ifndef ATMEGASPI_H
#define ATMEGASPI_H
#include "spi.h"
#include "atMegaGpio.h"
#include <stdint.h>


#define MAX_BUFFER 33

class ATMegaSpi:public Spi
{
public:;
	ATMegaSpi();
	~ATMegaSpi();
	uint8_t init();
	void close();
	void setCmd(uint8_t cmd);
	void setCmdData(uint8_t *buf, uint8_t len);
	void getCmdData(uint8_t *buf, uint8_t len);
	uint8_t getStatus();
	uint8_t spiTransfer(uint8_t len);


protected:
	uint8_t transfer(uint8_t data);

private:
   uint8_t buffer[MAX_BUFFER];
	 atmegaGpio *g;
};

#endif
