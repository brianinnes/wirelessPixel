#ifndef SPI_H
#define SPI_H

#include<stdint.h>


class Spi
{
	public:
	enum SpiMode {
		MODE0 = 0,   //!< Low at idle, capture on rising clock edge
		MODE1 = 1,   //!< Low at idle, capture on falling clock edge
		MODE2 = 2,   //!< High at idle, capture on falling clock edge
		MODE3 = 3    //!< High at idle, capture on rising clock edge
	};
	virtual ~Spi() {};
	virtual uint8_t init() = 0;
	virtual void close() = 0;
	virtual void setCmd(uint8_t cmd) = 0;
	virtual void setCmdData(uint8_t *buf, uint8_t len) = 0;
	virtual void getCmdData(uint8_t *buf, uint8_t len) = 0;
	virtual uint8_t getStatus() = 0;
	virtual uint8_t spiTransfer(uint8_t len) = 0;
};

#endif
