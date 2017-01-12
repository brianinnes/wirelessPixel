#ifndef RASPBERRYPISPI_H
#define RASPBERRYPISPI_H
#include "spi.h"
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include<string>
#include<stdint.h>



#define MAX_BUFFER 33

class RaspberryPiSpi:public Spi
{
public:;
	RaspberryPiSpi(uint8_t bus, uint8_t device);
	RaspberryPiSpi() : RaspberryPiSpi(0, 0) {}
	~RaspberryPiSpi();
	uint8_t init();
	void close();
	void setCmd(uint8_t cmd);
	void setCmdData(uint8_t *buf, uint8_t len);
	void getCmdData(uint8_t *buf, uint8_t len);
	uint8_t getStatus();
	uint8_t spiTransfer(uint8_t len);


protected:
   uint8_t transfer(uint8_t Len);

private:
   uint8_t buffer[MAX_BUFFER];
   struct spi_ioc_transfer ioc_tfr;

   int spifd;
   SpiMode mode;     //!< The SPI mode as per the SPIMODE enumeration
   uint8_t bitsPerWord;     //!< The number of bits per word
   uint32_t speed;   //!< The speed of transfer in Hz
   uint16_t delay;   //!< The transfer delay in usecs

   std::string filePath;
   int setSpeed(uint32_t speed);
   int setMode(SpiMode mode);
   int setBitsPerWord(uint8_t bits);
};

#endif
