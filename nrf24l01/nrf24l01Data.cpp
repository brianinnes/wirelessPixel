/*
 * nrf24l01Data.cpp
 *
 *  Created on: 23 Oct 2016
 *      Author: brian
 */
#include "nrf24l01Data.h"
#include <string.h>

nrf24l01Data::nrf24l01Data(nrf24l01 *radio) : broadcastAddr{BROADCAST_ADDR} {
	this->radio = radio;
}

nrf24l01Data::~nrf24l01Data() {
	radio->ceWrite(0x00);
	radio->setPwrUp(0x00);
}

void nrf24l01Data::initialise() {
	radio->setRfCh(0x62);
	radio->setRxAddrP0(this->broadcastAddr);
	radio->setRfPwr(rf_pwr_enum::RF_PWR_MIN);
	radio->setArd(0x02);
	radio->setEnDpl(0x01);
	radio->setDplP0(0x01);
	radio->setEnAckPay(0x01);
	radio->setEnDynAck(0x01);
	radio->ceWrite(0x00);
	radio->setPwrUp(0x01);
	radio->flushRx();
	radio->flushTx();
}

void nrf24l01Data::broadcast(uint8_t *bytes, uint8_t len) {
	uint8_t buf[len+1];
	buf[0] = 0x00;
	memcpy(buf+1, bytes, len);
	radio->setRxAddrP0(this->broadcastAddr);
	radio->setTxAddr(this->broadcastAddr);
	radio->writeNoAck(buf, len+1);
	radio->setPrimRx(0x00);
	radio->ceWrite(0x01);
	radio->nop();
	radio->ceWrite(0x00);
}

void nrf24l01Data::startReceiving() {
	radio->setRxAddrP0(this->broadcastAddr);
	radio->setPrimRx(0x01);
	radio->ceWrite(0x01);
}

void nrf24l01Data::stopReceiving() {
	radio->ceWrite(0x00);
}

uint8_t nrf24l01Data::isMessageAvailable() {
	uint8_t ret = 0;
	radio->nop();
	if (radio->getRxPNo() < 0x07) {
		ret = radio->readRxPayloadWidth();
	}
	return ret;
}

void nrf24l01Data::getMessage(uint8_t *buf, uint8_t len) {
	radio->readRXPayload(buf, len);
}

