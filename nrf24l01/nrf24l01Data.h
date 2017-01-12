#ifndef NRF24L01DATA_H
    #define NRF24L01DATA_H

#include "nrf24l01.h"

#define BROADCAST_ADDR 0x01,0x00,0x00,0x00,0x01

class nrf24l01Data {
public:
	nrf24l01Data(nrf24l01 *radio);
	~nrf24l01Data();

	uint8_t broadcastAddr[5];

	void initialise();
	void broadcast(uint8_t *bytes, uint8_t len);
	void startReceiving();
	void stopReceiving();
	uint8_t isMessageAvailable();
	void getMessage(uint8_t *buf, uint8_t len);

private:
	nrf24l01 *radio;
};

#endif
