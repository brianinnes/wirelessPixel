#ifndef ATTINYSPI_H
#define ATTINYSPI_H
#include "spi.h"
#include "atTinyGpio.h"
#include <stdint.h>



#define MAX_BUFFER 33

class ATTinySpi:public Spi
{
public:;
	ATTinySpi();
	~ATTinySpi();
	uint8_t init() override;
	void close() override;
	void setCmd(uint8_t cmd) override;
	void setCmdData(uint8_t *buf, uint8_t len) override;
	void getCmdData(uint8_t *buf, uint8_t len) override;
	uint8_t getStatus() override;
	uint8_t spiTransfer(uint8_t len) override;


protected:
	uint8_t transfer(uint8_t data);

private:
   uint8_t buffer[MAX_BUFFER];
	 attinyGpio *g;
};

#endif
