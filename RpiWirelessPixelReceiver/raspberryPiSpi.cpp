#include "raspberryPiSpi.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
using namespace std;

#define SPI_PATH "/dev/spidev"

RaspberryPiSpi::RaspberryPiSpi(uint8_t bus, uint8_t device)
{
	stringstream s;
	s << SPI_PATH << to_string(bus) << "." << to_string(device);
	this->filePath = string(s.str());
	this->mode = SpiMode::MODE0;
	this->bitsPerWord = 8;
	this->speed = 16000000;
	this->spifd = -1;
	this->delay = 0;
	this->ioc_tfr.tx_buf = (unsigned long) &this->buffer;
	this->ioc_tfr.rx_buf = (unsigned long) &this->buffer;
	this->ioc_tfr.len = 0;
	this->ioc_tfr.speed_hz = this->speed;
	this->ioc_tfr.bits_per_word = this->bitsPerWord;
	this->ioc_tfr.delay_usecs = this->delay;
	this->ioc_tfr.pad = 0;
}

RaspberryPiSpi::~RaspberryPiSpi()
{
	this->close();
}


uint8_t RaspberryPiSpi::init()
{
	if ((this->spifd = ::open(this->filePath.c_str(), O_RDWR))<0){
			perror("SPI: Can't open device.");
			return -1;
		}
		if (this->setMode(this->mode)==-1) return -1;
		if (this->setSpeed(this->speed)==-1) return -1;
		if (this->setBitsPerWord(this->bitsPerWord)==-1) return -1;
		return 0;
}

void RaspberryPiSpi::close()
{
	::close(this->spifd);
	this->spifd = -1;
}

void RaspberryPiSpi::setCmd(uint8_t cmd)
{
	memset(this->buffer, 0, sizeof this->buffer);
	this->buffer[0] = cmd;
}

void RaspberryPiSpi::setCmdData(uint8_t *buf, uint8_t len)
{
	memcpy(this->buffer+1, buf, len);
}

uint8_t RaspberryPiSpi::getStatus() {
	return this->buffer[0];
}

void RaspberryPiSpi::getCmdData(uint8_t *buf, uint8_t len)
{
	memcpy(buf, this->buffer+1, len);
}

uint8_t RaspberryPiSpi::spiTransfer(uint8_t len)
{
	return this->transfer(len);
}

/**
 *   Set the speed of the SPI bus
 *   @param speed the speed in Hz
 */
int RaspberryPiSpi::setSpeed(uint32_t speed){
	this->speed = speed;
	if (ioctl(this->spifd, SPI_IOC_WR_MAX_SPEED_HZ, &this->speed)==-1){
		perror("SPI: Can't set max speed HZ");
		return -1;
	}
	if (ioctl(this->spifd, SPI_IOC_RD_MAX_SPEED_HZ, &this->speed)==-1){
		perror("SPI: Can't get max speed HZ.");
		return -1;
	}
	return 0;
}

/**
 *   Set the mode of the SPI bus
 *   @param mode the enumerated SPI mode
 */
int RaspberryPiSpi::setMode(SpiMode mode){
   this->mode = mode;
   if (ioctl(this->spifd, SPI_IOC_WR_MODE, &this->mode)==-1){
      perror("SPI: Can't set SPI mode.");
      return -1;
   }
   if (ioctl(this->spifd, SPI_IOC_RD_MODE, &this->mode)==-1){
      perror("SPI: Can't get SPI mode.");
      return -1;
   }
   return 0;
}

/**
 *   Set the number of bits per word of the SPI bus
 *   @param bits the number of bits per word
 */
int RaspberryPiSpi::setBitsPerWord(uint8_t bits){
	this->bitsPerWord = bits;
	this->ioc_tfr.bits_per_word = bits;
	if (ioctl(this->spifd, SPI_IOC_WR_BITS_PER_WORD, &this->bitsPerWord)==-1){
		perror("SPI: Can't set bits per word.");
		return -1;
	}
	if (ioctl(this->spifd, SPI_IOC_RD_BITS_PER_WORD, &this->bitsPerWord)==-1){
		perror("SPI: Can't get bits per word.");
		return -1;
	}
	return 0;
}

uint8_t RaspberryPiSpi::transfer(uint8_t len)
{
		this->ioc_tfr.len = len;
		int status = ioctl(this->spifd, SPI_IOC_MESSAGE(1), &this->ioc_tfr);
		if (status < 0) {
			perror("SPI: SPI_IOC_MESSAGE Failed");
			return -1;
		}
		return status;
}
