#ifndef NRF24L01_H
#define NRF24L01_H

#include "spi.h"
#include "gpio.h"


#define CMD_R_REGISTER 0x00
#define CMD_W_REGISTER 0x20
#define CMD_R_RX_PAYLOAD 0x61
#define CMD_W_TX_PAYLOAD 0xA0
#define CMD_FLUSH_TX 0xE1
#define CMD_FLUSH_RX 0xE2
#define CMD_REUSE_TX_PL 0xE3
#define CMD_R_RX_PL_WID 0x60
#define CMD_W_ACK_PAYLOAD 0xA8
#define CMD_W_TX_PAYLOAD_NOACK 0xB0
#define CMD_NOP 0xFF
#define REG_MASK 0x1F

#define RF_PWR 0x06

enum class reg_enum : uint8_t {
	REG_CONFIG = 0,
	REG_EN_AA,
	REG_EN_RXADDR,
	REG_SETUP_AW,
	REG_SETUP_RETR,
	REG_RF_CH,
	REG_SETUP,
	REG_STATUS,
	REG_OBSERVE_TX,
	REG_RPD,
	REG_RX_ADDR_P0,
	REG_RX_ADDR_P1,
	REG_RX_ADDR_P2,
	REG_RX_ADDR_P3,
	REG_RX_ADDR_P4,
	REG_RX_ADDR_P5,
	REG_TX_ADDR,
	REG_RX_PW_P0,
	REG_RX_PW_P1,
	REG_RX_PW_P2,
	REG_RX_PW_P3,
	REG_RX_PW_P4,
	REG_RX_PW_P5,
	REG_FIFO_STATUS,
	REG_DYNPD = 0x1C,
	REG_FEATURE = 0x1D
};

enum class rf_pwr_enum : uint8_t {
	RF_PWR_MIN = 0,
	RF_PWR_LOW,
	RF_PWR_HIGH,
	RF_PWR_MAX
};

class nrf24l01 {
public:
	nrf24l01(Spi *s, Gpio *g);
	~nrf24l01();

	void readRXPayload(uint8_t *buf, uint8_t len);
	void writeTXPayload(uint8_t *bytes, uint8_t len);
	void flushTx();
	void flushRx();
	void reuseTxPayload();
	uint8_t readRxPayloadWidth();
	void writeAckPayload(uint8_t pipe, uint8_t *bytes, uint8_t len);
	void writeNoAck(uint8_t *bytes, uint8_t len);
	void nop();

	uint8_t getMaskRxDr();
	uint8_t getMaskTxDs();
	uint8_t getMaskMaxRt();
	uint8_t getEnCrc();
	uint8_t getCrco();
	uint8_t getPwrUp();
	uint8_t getPrimRx();
	uint8_t getEnaaP5();
	uint8_t getEnaaP4();
	uint8_t getEnaaP3();
	uint8_t getEnaaP2();
	uint8_t getEnaaP1();
	uint8_t getEnaaP0();
	uint8_t getErxP5();
	uint8_t getErxP4();
	uint8_t getErxP3();
	uint8_t getErxP2();
	uint8_t getErxP1();
	uint8_t getErxP0();
	uint8_t getAw();
	uint8_t getArd();
	uint8_t getArc();
	uint8_t getRfCh();
	uint8_t getContWave();
	uint8_t getRfDrLow();
	uint8_t getPllLock();
	uint8_t getRfDrHigh();
	inline rf_pwr_enum getRfPwr();
	uint8_t getRxDr();
	uint8_t getTxDs();
	uint8_t getMaxRt();
	uint8_t getRxPNo();
	uint8_t getStatusTxFull();
	uint8_t getPlosCnt();
	uint8_t getArcCnt();
	uint8_t getRpd();
	uint8_t *getRxAddrP0();
	uint8_t *getRxAddrP1();
	uint8_t getRxAddrP2();
	uint8_t getRxAddrP3();
	uint8_t getRxAddrP4();
	uint8_t getRxAddrP5();
	uint8_t *getTxAddr();
	uint8_t getRxPwP0();
	uint8_t getRxPwP1();
	uint8_t getRxPwP2();
	uint8_t getRxPwP3();
	uint8_t getRxPwP4();
	uint8_t getRxPwP5();
	uint8_t getTxReuse();
	uint8_t getTxFull();
	uint8_t getTxEmpty();
	uint8_t getRxFull();
	uint8_t getRxEmpty();
	uint8_t getDplP5();
	uint8_t getDplP4();
	uint8_t getDplP3();
	uint8_t getDplP2();
	uint8_t getDplP1();
	uint8_t getDplP0();
	uint8_t getEnDpl();
	uint8_t getEnAckPay();
	uint8_t getEnDynAck();

	void setMaskRxDr(uint8_t val);
	void setMaskTxDs(uint8_t val);
	void setMaskMaxRt(uint8_t val);
	void setEnCrc(uint8_t val);
	void setCrco(uint8_t val);
	void setPwrUp(uint8_t val);
	void setPrimRx(uint8_t val);
	void setEnaaP5(uint8_t val);
	void setEnaaP4(uint8_t val);
	void setEnaaP3(uint8_t val);
	void setEnaaP2(uint8_t val);
	void setEnaaP1(uint8_t val);
	void setEnaaP0(uint8_t val);
	void setErxP5(uint8_t val);
	void setErxP4(uint8_t val);
	void setErxP3(uint8_t val);
	void setErxP2(uint8_t val);
	void setErxP1(uint8_t val);
	void setErxP0(uint8_t val);
	void setAw(uint8_t val);
	void setArd(uint8_t val);
	void setArc(uint8_t val);
	void setRfCh(uint8_t val);
	void setContWave(uint8_t val);
	void setRfDrLow(uint8_t val);
	void setPllLock(uint8_t val);
	void setRfDrHigh(uint8_t val);
	inline void setRfPwr(rf_pwr_enum val);
	void setRxDr(uint8_t val);
	void setTxDs(uint8_t val);
	void setMaxRt(uint8_t val);
	void setRxPNo(uint8_t val);
	void setStatusTxFull(uint8_t val);
	void setPlosCnt(uint8_t val);
	void setArcCnt(uint8_t val);
	void setRpd(uint8_t val);
	void setRxAddrP0(uint8_t *val);
	void setRxAddrP1(uint8_t *val);
	void setRxAddrP2(uint8_t val);
	void setRxAddrP3(uint8_t val);
	void setRxAddrP4(uint8_t val);
	void setRxAddrP5(uint8_t val);
	void setTxAddr(uint8_t *val);
	void setRxPwP0(uint8_t val);
	void setRxPwP1(uint8_t val);
	void setRxPwP2(uint8_t val);
	void setRxPwP3(uint8_t val);
	void setRxPwP4(uint8_t val);
	void setRxPwP5(uint8_t val);
	void setTxReuse(uint8_t val);
	void setTxFull(uint8_t val);
	void setTxEmpty(uint8_t val);
	void setRxFull(uint8_t val);
	void setRxEmpty(uint8_t val);
	void setDplP5(uint8_t val);
	void setDplP4(uint8_t val);
	void setDplP3(uint8_t val);
	void setDplP2(uint8_t val);
	void setDplP1(uint8_t val);
	void setDplP0(uint8_t val);
	void setEnDpl(uint8_t val);
	void setEnAckPay(uint8_t val);
	void setEnDynAck(uint8_t val);
	int ceWrite(int value);


private:
	int cePin;
	int cePin_fd;
	uint8_t reg_config;
	uint8_t reg_en_aa;
	uint8_t reg_en_rxaddr;
	uint8_t reg_setup_aw;
	uint8_t reg_setup_retr;
	uint8_t reg_rf_ch;
	uint8_t reg_setup;
	uint8_t reg_status;
	uint8_t reg_observe_tx;
	uint8_t reg_rpd;
	uint8_t reg_rx_addr_p0[5];
	uint8_t reg_rx_addr_p1[5];
	uint8_t reg_rx_addr_p2;
	uint8_t reg_rx_addr_p3;
	uint8_t reg_rx_addr_p4;
	uint8_t reg_rx_addr_p5;
	uint8_t reg_tx_addr[5];
	uint8_t reg_rx_pw_p0;
	uint8_t reg_rx_pw_p1;
	uint8_t reg_rx_pw_p2;
	uint8_t reg_rx_pw_p3;
	uint8_t reg_rx_pw_p4;
	uint8_t reg_rx_pw_p5;
	uint8_t reg_fifo_status;
	uint8_t reg_dynpd;
	uint8_t reg_feature;

	Spi *spi;
	Gpio *gpio;

	void readRegs();
	void readReg_config();
	void readReg_en_aa();
	void readReg_en_rxaddr();
	void readReg_setup_aw();
	void readReg_setup_retr();
	void readReg_rf_ch();
	void readReg_setup();
	void readReg_observe_tx();
	void readReg_rpd();
	void readReg_rx_addr_p0();
	void readReg_rx_addr_p1();
	void readReg_rx_addr_p2();
	void readReg_rx_addr_p3();
	void readReg_rx_addr_p4();
	void readReg_rx_addr_p5();
	void readReg_tx_addr();
	void readReg_rx_pw_p0();
	void readReg_rx_pw_p1();
	void readReg_rx_pw_p2();
	void readReg_rx_pw_p3();
	void readReg_rx_pw_p4();
	void readReg_rx_pw_p5();
	void readReg_fifo_status();
	void readReg_dynpd();
	void readReg_feature();
	void writeReg_config();
	void writeReg_en_aa();
	void writeReg_en_rxaddr();
	void writeReg_setup_aw();
	void writeReg_setup_retr();
	void writeReg_rf_ch();
	void writeReg_setup();
	void writeReg_status();
	void writeReg_rx_addr_p0();
	void writeReg_rx_addr_p1();
	void writeReg_rx_addr_p2();
	void writeReg_rx_addr_p3();
	void writeReg_rx_addr_p4();
	void writeReg_rx_addr_p5();
	void writeReg_tx_addr();
	void writeReg_rx_pw_p0();
	void writeReg_rx_pw_p1();
	void writeReg_rx_pw_p2();
	void writeReg_rx_pw_p3();
	void writeReg_rx_pw_p4();
	void writeReg_rx_pw_p5();
	void writeReg_dynpd();
	void writeReg_feature();

	uint8_t getShortRegValue(reg_enum r);
	void setShortRegValue(reg_enum r, uint8_t val);
	uint8_t *getLongRegValue(reg_enum r);
	void setLongRegValue(reg_enum r, uint8_t *val);

	uint8_t readShortRegister(reg_enum r);
	void readLongRegister(reg_enum r, uint8_t *buf);
	void writeShortRegister(reg_enum r, uint8_t value);
	void writeLongRegister(reg_enum r, uint8_t *buf);
	uint8_t getBitRegister(reg_enum reg, uint8_t bit, uint8_t lenBits, bool refresh = false);
	void setBitRegister(reg_enum reg, uint8_t bit, uint8_t val, uint8_t lenBits);
};

inline uint8_t nrf24l01::getMaskRxDr(){
	return this->getBitRegister(reg_enum::REG_CONFIG, 6, 0x01);
}


inline uint8_t nrf24l01::getMaskTxDs() {
	return this->getBitRegister(reg_enum::REG_CONFIG, 5, 0x01);
}


inline uint8_t nrf24l01::getMaskMaxRt() {
	return this->getBitRegister(reg_enum::REG_CONFIG, 4, 0x01);
}


inline uint8_t nrf24l01::getEnCrc() {
	return this->getBitRegister(reg_enum::REG_CONFIG, 3, 0x01);
}


inline uint8_t nrf24l01::getCrco() {
	return this->getBitRegister(reg_enum::REG_CONFIG, 2, 0x01);
}


inline uint8_t nrf24l01::getPwrUp() {
	return this->getBitRegister(reg_enum::REG_CONFIG, 1, 0x01);
}


inline uint8_t nrf24l01::getPrimRx() {
	return this->getBitRegister(reg_enum::REG_CONFIG, 0, 0x01);
}


inline uint8_t nrf24l01::getEnaaP5() {
	return this->getBitRegister(reg_enum::REG_EN_AA, 5, 0x01);
}


inline uint8_t nrf24l01::getEnaaP4() {
	return this->getBitRegister(reg_enum::REG_EN_AA, 4, 0x01);
}


inline uint8_t nrf24l01::getEnaaP3() {
	return this->getBitRegister(reg_enum::REG_EN_AA, 3, 0x01);
}


inline uint8_t nrf24l01::getEnaaP2() {
	return this->getBitRegister(reg_enum::REG_EN_AA, 2, 0x01);
}


inline uint8_t nrf24l01::getEnaaP1() {
	return this->getBitRegister(reg_enum::REG_EN_AA, 1, 0x01);
}


inline uint8_t nrf24l01::getEnaaP0() {
	return this->getBitRegister(reg_enum::REG_EN_AA, 0, 0x01);
}


inline uint8_t nrf24l01::getErxP5() {
	return this->getBitRegister(reg_enum::REG_EN_RXADDR, 5, 0x01);
}


inline uint8_t nrf24l01::getErxP4() {
	return this->getBitRegister(reg_enum::REG_EN_RXADDR, 4, 0x01);
}


inline uint8_t nrf24l01::getErxP3() {
	return this->getBitRegister(reg_enum::REG_EN_RXADDR, 3, 0x01);
}


inline uint8_t nrf24l01::getErxP2() {
	return this->getBitRegister(reg_enum::REG_EN_RXADDR, 2, 0x01);
}


inline uint8_t nrf24l01::getErxP1() {
	return this->getBitRegister(reg_enum::REG_EN_RXADDR, 1, 0x01);
}


inline uint8_t nrf24l01::getErxP0() {
	return this->getBitRegister(reg_enum::REG_EN_RXADDR, 0, 0x01);
}


inline uint8_t nrf24l01::getAw() {
	return this->getBitRegister(reg_enum::REG_SETUP_AW, 0, 0x03);
}


inline uint8_t nrf24l01::getArd() {
	return this->getBitRegister(reg_enum::REG_SETUP_RETR, 4, 0x0F);
}


inline uint8_t  nrf24l01::getArc() {
	return this->getBitRegister(reg_enum::REG_SETUP_RETR, 0, 0x0F);
}


inline uint8_t nrf24l01::getRfCh() {
	return this->getBitRegister(reg_enum::REG_RF_CH, 0, 0x7F);
}


inline uint8_t nrf24l01::getContWave() {
	return this->getBitRegister(reg_enum::REG_SETUP, 7, 0x01);
}


inline uint8_t nrf24l01::getRfDrLow() {
	return this->getBitRegister(reg_enum::REG_SETUP, 5, 0x01);
}


inline uint8_t nrf24l01::getPllLock() {
	return this->getBitRegister(reg_enum::REG_SETUP, 4, 0x01);
}


inline uint8_t nrf24l01::getRfDrHigh() {
	return this->getBitRegister(reg_enum::REG_SETUP, 3, 0x01);
}


inline rf_pwr_enum nrf24l01::getRfPwr() {
	return (rf_pwr_enum)this->getBitRegister(reg_enum::REG_SETUP, 1, 0x03);
}

inline uint8_t nrf24l01::getRxDr() {
	return this->getBitRegister(reg_enum::REG_STATUS, 6, 0x01);
}


inline uint8_t nrf24l01::getTxDs() {
	return this->getBitRegister(reg_enum::REG_STATUS, 5, 0x01);
}


inline uint8_t nrf24l01::getMaxRt() {
	return this->getBitRegister(reg_enum::REG_STATUS, 4, 0x01);
}


inline uint8_t nrf24l01::getRxPNo() {
	return this->getBitRegister(reg_enum::REG_STATUS, 1, 0x07);
}


inline uint8_t nrf24l01::getStatusTxFull() {
	return this->getBitRegister(reg_enum::REG_STATUS, 0, 0x01, true);
}


inline uint8_t nrf24l01::getPlosCnt() {
	return this->getBitRegister(reg_enum::REG_OBSERVE_TX, 4, 0x0F);
}


inline uint8_t nrf24l01::getArcCnt() {
	return this->getBitRegister(reg_enum::REG_OBSERVE_TX, 0, 0x0F);
}


inline uint8_t nrf24l01::getRpd() {
	return this->getBitRegister(reg_enum::REG_RPD, 0, 0x01);
}


inline uint8_t *nrf24l01::getRxAddrP0() {
	return this->reg_rx_addr_p0;
}


inline uint8_t *nrf24l01::getRxAddrP1() {
	return this->reg_rx_addr_p1;
}


inline uint8_t nrf24l01::getRxAddrP2() {
	return this->reg_rx_addr_p2;
}


inline uint8_t nrf24l01::getRxAddrP3() {
	return this->reg_rx_addr_p3;
}


inline uint8_t nrf24l01::getRxAddrP4() {
	return this->reg_rx_addr_p4;
}


inline uint8_t nrf24l01::getRxAddrP5() {
	return this->reg_rx_addr_p5;
}


inline uint8_t *nrf24l01::getTxAddr() {
	return this->reg_tx_addr;
}


inline uint8_t nrf24l01::getRxPwP0() {
	return this->getBitRegister(reg_enum::REG_RX_PW_P0, 0, 0x3F);
}


inline uint8_t nrf24l01::getRxPwP1() {
	return this->getBitRegister(reg_enum::REG_RX_PW_P1, 0, 0x3F);
}


inline uint8_t nrf24l01::getRxPwP2() {
	return this->getBitRegister(reg_enum::REG_RX_PW_P2, 0, 0x3F);
}


inline uint8_t nrf24l01::getRxPwP3() {
	return this->getBitRegister(reg_enum::REG_RX_PW_P3, 0, 0x3F);
}


inline uint8_t nrf24l01::getRxPwP4() {
	return this->getBitRegister(reg_enum::REG_RX_PW_P4, 0, 0x3F);
}


inline uint8_t nrf24l01::getRxPwP5() {
	return this->getBitRegister(reg_enum::REG_RX_PW_P5, 0, 0x3F);
}


inline uint8_t nrf24l01::getTxReuse() {
	return this->getBitRegister(reg_enum::REG_FIFO_STATUS, 6, 0x01);
}


inline uint8_t nrf24l01::getTxFull() {
	return this->getBitRegister(reg_enum::REG_FIFO_STATUS, 5, 0x01, true);
}


inline uint8_t nrf24l01::getTxEmpty() {
	return this->getBitRegister(reg_enum::REG_FIFO_STATUS, 4, 0x01, true);
}


inline uint8_t nrf24l01::getRxFull() {
	return this->getBitRegister(reg_enum::REG_FIFO_STATUS, 1, 0x01);
}


inline uint8_t nrf24l01::getRxEmpty() {
	return this->getBitRegister(reg_enum::REG_FIFO_STATUS, 0, 0x01);
}


inline uint8_t nrf24l01::getDplP5() {
	return this->getBitRegister(reg_enum::REG_DYNPD, 5, 0x01);
}


inline uint8_t nrf24l01::getDplP4() {
	return this->getBitRegister(reg_enum::REG_DYNPD, 4, 0x01);
}


inline uint8_t nrf24l01::getDplP3() {
	return this->getBitRegister(reg_enum::REG_DYNPD, 3, 0x01);
}


inline uint8_t nrf24l01::getDplP2() {
	return this->getBitRegister(reg_enum::REG_DYNPD, 2, 0x01);
}


inline uint8_t nrf24l01::getDplP1() {
	return this->getBitRegister(reg_enum::REG_DYNPD, 1, 0x01);
}


inline uint8_t nrf24l01::getDplP0() {
	return this->getBitRegister(reg_enum::REG_DYNPD, 0, 0x01);
}


inline uint8_t nrf24l01::getEnDpl() {
	return this->getBitRegister(reg_enum::REG_FEATURE, 2, 0x01);
}


inline uint8_t nrf24l01::getEnAckPay() {
	return this->getBitRegister(reg_enum::REG_FEATURE, 1, 0x01);
}


inline uint8_t nrf24l01::getEnDynAck() {
	return this->getBitRegister(reg_enum::REG_FEATURE, 0, 0x01);
}



inline void nrf24l01::setMaskRxDr(uint8_t val) {
	this->setBitRegister(reg_enum::REG_CONFIG, 6, val, 0x01);
}


inline void nrf24l01::setMaskTxDs(uint8_t val) {
	this->setBitRegister(reg_enum::REG_CONFIG, 5, val, 0x01);
}


inline void nrf24l01::setMaskMaxRt(uint8_t val) {
	this->setBitRegister(reg_enum::REG_CONFIG, 4, val, 0x01);
}


inline void nrf24l01::setEnCrc(uint8_t val) {
	this->setBitRegister(reg_enum::REG_CONFIG, 3, val, 0x01);
}


inline void nrf24l01::setCrco(uint8_t val) {
	this->setBitRegister(reg_enum::REG_CONFIG, 2, val, 0x01);
}


inline void nrf24l01::setPwrUp(uint8_t val) {
	this->setBitRegister(reg_enum::REG_CONFIG, 1, val, 0x01);
}


inline void nrf24l01::setPrimRx(uint8_t val) {
	this->setBitRegister(reg_enum::REG_CONFIG, 0, val, 0x01);
}


inline void nrf24l01::setEnaaP5(uint8_t val) {
	this->setBitRegister(reg_enum::REG_EN_AA, 5, val, 0x01);
}


inline void nrf24l01::setEnaaP4(uint8_t val) {
	this->setBitRegister(reg_enum::REG_EN_AA, 4, val, 0x01);
}


inline void nrf24l01::setEnaaP3(uint8_t val) {
	this->setBitRegister(reg_enum::REG_EN_AA, 3, val, 0x01);
}


inline void nrf24l01::setEnaaP2(uint8_t val) {
	this->setBitRegister(reg_enum::REG_EN_AA, 2, val, 0x01);
}


inline void nrf24l01::setEnaaP1(uint8_t val) {
	this->setBitRegister(reg_enum::REG_EN_AA, 1, val, 0x01);
}


inline void nrf24l01::setEnaaP0(uint8_t val) {
	this->setBitRegister(reg_enum::REG_EN_AA, 0, val, 0x01);
}


inline void nrf24l01::setErxP5(uint8_t val) {
	this->setBitRegister(reg_enum::REG_EN_RXADDR, 5, val, 0x01);
}


inline void nrf24l01::setErxP4(uint8_t val) {
	this->setBitRegister(reg_enum::REG_EN_RXADDR, 4, val, 0x01);
}


inline void nrf24l01::setErxP3(uint8_t val) {
	this->setBitRegister(reg_enum::REG_EN_RXADDR, 3, val, 0x01);
}


inline void nrf24l01::setErxP2(uint8_t val) {
	this->setBitRegister(reg_enum::REG_EN_RXADDR, 2, val, 0x01);
}


inline void nrf24l01::setErxP1(uint8_t val) {
	this->setBitRegister(reg_enum::REG_EN_RXADDR, 1, val, 0x01);
}


inline void nrf24l01::setErxP0(uint8_t val) {
	this->setBitRegister(reg_enum::REG_EN_RXADDR, 0, val, 0x01);
}


inline void nrf24l01::setAw(uint8_t val) {
	this->setBitRegister(reg_enum::REG_SETUP_AW, 0, val, 0x03);
}


inline void nrf24l01::setArd(uint8_t val) {
	this->setBitRegister(reg_enum::REG_SETUP_RETR, 4, val, 0x0F);
}


inline void nrf24l01::setArc(uint8_t val) {
	this->setBitRegister(reg_enum::REG_SETUP_RETR, 0, val, 0x0F);
}


inline void nrf24l01::setRfCh(uint8_t val) {
	this->setBitRegister(reg_enum::REG_RF_CH, 0, val, 0x7F);
}


inline void nrf24l01::setContWave(uint8_t val) {
	this->setBitRegister(reg_enum::REG_SETUP, 7, val, 0x01);
}


inline void nrf24l01::setRfDrLow(uint8_t val) {
	this->setBitRegister(reg_enum::REG_SETUP, 5, val, 0x01);
}


inline void nrf24l01::setPllLock(uint8_t val) {
	this->setBitRegister(reg_enum::REG_SETUP, 4, val, 0x01);
}


inline void nrf24l01::setRfDrHigh(uint8_t val) {
	this->setBitRegister(reg_enum::REG_SETUP, 3, val, 0x01);
}


inline void nrf24l01::setRfPwr(rf_pwr_enum val) {
	this->setBitRegister(reg_enum::REG_SETUP, 1, (uint8_t)val, 0x03);
}


inline void nrf24l01::setRxDr(uint8_t val) {
	this->setBitRegister(reg_enum::REG_STATUS, 6, val, 0x01);
}


inline void nrf24l01::setTxDs(uint8_t val) {
	this->setBitRegister(reg_enum::REG_STATUS, 5, val, 0x01);
}


inline void nrf24l01::setMaxRt(uint8_t val) {
	this->setBitRegister(reg_enum::REG_STATUS, 4, val, 0x01);
}


inline void nrf24l01::setRxPNo(uint8_t val) {
	this->setBitRegister(reg_enum::REG_STATUS, 1, val, 0x07);
}


inline void nrf24l01::setStatusTxFull(uint8_t val) {
	this->setBitRegister(reg_enum::REG_STATUS, 0, val, 0x01);
}


inline void nrf24l01::setPlosCnt(uint8_t val) {
	this->setBitRegister(reg_enum::REG_OBSERVE_TX, 4, val, 0x0F);
}


inline void nrf24l01::setArcCnt(uint8_t val) {
	this->setBitRegister(reg_enum::REG_OBSERVE_TX, 0, val, 0x0F);
}


inline void nrf24l01::setRpd(uint8_t val) {
	this->setBitRegister(reg_enum::REG_RPD, 0, val, 0x01);
}


inline void nrf24l01::setRxAddrP0(uint8_t *val) {
	this->setLongRegValue(reg_enum::REG_RX_ADDR_P0, val);
}


inline void nrf24l01::setRxAddrP1(uint8_t *val) {
	this->setLongRegValue(reg_enum::REG_RX_ADDR_P1, val);
}


inline void nrf24l01::setRxAddrP2(uint8_t val) {
	this->setShortRegValue(reg_enum::REG_RX_ADDR_P2, val);
}


inline void nrf24l01::setRxAddrP3(uint8_t val) {
	this->setShortRegValue(reg_enum::REG_RX_ADDR_P3, val);
}


inline void nrf24l01::setRxAddrP4(uint8_t val) {
	this->setShortRegValue(reg_enum::REG_RX_ADDR_P4, val);
}


inline void nrf24l01::setRxAddrP5(uint8_t val) {
	this->setShortRegValue(reg_enum::REG_RX_ADDR_P5, val);
}


inline void nrf24l01::setTxAddr(uint8_t *val) {
	this->setLongRegValue(reg_enum::REG_TX_ADDR, val);
}


inline void nrf24l01::setRxPwP0(uint8_t val) {
	this->setBitRegister(reg_enum::REG_RX_PW_P0, 0, val, 0x3F);
}


inline void nrf24l01::setRxPwP1(uint8_t val) {
	this->setBitRegister(reg_enum::REG_RX_PW_P1, 0, val, 0x3F);
}


inline void nrf24l01::setRxPwP2(uint8_t val) {
	this->setBitRegister(reg_enum::REG_RX_PW_P2, 0, val, 0x3F);
}


inline void nrf24l01::setRxPwP3(uint8_t val) {
	this->setBitRegister(reg_enum::REG_RX_PW_P3, 0, val, 0x3F);
}


inline void nrf24l01::setRxPwP4(uint8_t val) {
	this->setBitRegister(reg_enum::REG_RX_PW_P4, 0, val, 0x3F);
}


inline void nrf24l01::setRxPwP5(uint8_t val) {
	this->setBitRegister(reg_enum::REG_RX_PW_P5, 0, val, 0x3F);
}


inline void nrf24l01::setTxReuse(uint8_t val) {
	this->setBitRegister(reg_enum::REG_FIFO_STATUS, 6, val, 0x01);
}


inline void nrf24l01::setTxFull(uint8_t val) {
	this->setBitRegister(reg_enum::REG_FIFO_STATUS, 5, val, 0x01);
}


inline void nrf24l01::setTxEmpty(uint8_t val) {
	this->setBitRegister(reg_enum::REG_FIFO_STATUS, 4, val, 0x01);
}


inline void nrf24l01::setRxFull(uint8_t val) {
	this->setBitRegister(reg_enum::REG_FIFO_STATUS, 1, val, 0x01);
}


inline void nrf24l01::setRxEmpty(uint8_t val) {
	this->setBitRegister(reg_enum::REG_FIFO_STATUS, 0, val, 0x01);
}


inline void nrf24l01::setDplP5(uint8_t val) {
	this->setBitRegister(reg_enum::REG_DYNPD, 5, val, 0x01);
}


inline void nrf24l01::setDplP4(uint8_t val) {
	this->setBitRegister(reg_enum::REG_DYNPD, 4, val, 0x01);
}


inline void nrf24l01::setDplP3(uint8_t val) {
	this->setBitRegister(reg_enum::REG_DYNPD, 3, val, 0x01);
}


inline void nrf24l01::setDplP2(uint8_t val) {
	this->setBitRegister(reg_enum::REG_DYNPD, 2, val, 0x01);
}


inline void nrf24l01::setDplP1(uint8_t val) {
	this->setBitRegister(reg_enum::REG_DYNPD, 1, val, 0x01);
}


inline void nrf24l01::setDplP0(uint8_t val) {
	this->setBitRegister(reg_enum::REG_DYNPD, 0, val, 0x01);
}


inline void nrf24l01::setEnDpl(uint8_t val) {
	this->setBitRegister(reg_enum::REG_FEATURE, 2, val, 0x01);
}


inline void nrf24l01::setEnAckPay(uint8_t val) {
	this->setBitRegister(reg_enum::REG_FEATURE, 1, val, 0x01);
}


inline void nrf24l01::setEnDynAck(uint8_t val) {
	this->setBitRegister(reg_enum::REG_FEATURE, 0, val, 0x01);
}



void inline nrf24l01::readReg_config() {
	this->reg_config = this->readShortRegister(reg_enum::REG_CONFIG);
}

void inline nrf24l01::readReg_en_aa() {
	this->reg_en_aa = this->readShortRegister(reg_enum::REG_EN_AA);

}

void inline nrf24l01::readReg_en_rxaddr() {
	this->reg_en_rxaddr = this->readShortRegister(reg_enum::REG_EN_RXADDR);
}

void inline nrf24l01::readReg_setup_aw() {
	this->reg_setup_aw = this->readShortRegister(reg_enum::REG_SETUP_AW);
}

void inline nrf24l01::readReg_setup_retr() {
	this->reg_setup_retr = this->readShortRegister(reg_enum::REG_SETUP_RETR);
}

void inline nrf24l01::readReg_rf_ch() {
	this->reg_rf_ch = this->readShortRegister(reg_enum::REG_RF_CH);
}

void inline nrf24l01::readReg_setup() {
	this->reg_setup = this->readShortRegister(reg_enum::REG_SETUP);
}

void inline nrf24l01::readReg_observe_tx() {
	this->reg_observe_tx = this->readShortRegister(reg_enum::REG_OBSERVE_TX);
}

void inline nrf24l01::readReg_rpd() {
	this->reg_rpd = this->readShortRegister(reg_enum::REG_RPD);
}

void inline nrf24l01::readReg_rx_addr_p0() {
	this->readLongRegister(reg_enum::REG_RX_ADDR_P0, this->reg_rx_addr_p0);
}

void inline nrf24l01::readReg_rx_addr_p1() {
	this->readLongRegister(reg_enum::REG_RX_ADDR_P1, this->reg_rx_addr_p1);
}

void inline nrf24l01::readReg_rx_addr_p2() {
	this->reg_rx_addr_p2 = this->readShortRegister(reg_enum::REG_RX_ADDR_P2);
}

void inline nrf24l01::readReg_rx_addr_p3() {
	this->reg_rx_addr_p3 = this->readShortRegister(reg_enum::REG_RX_ADDR_P3);
}

void inline nrf24l01::readReg_rx_addr_p4() {
	this->reg_rx_addr_p4 = this->readShortRegister(reg_enum::REG_RX_ADDR_P4);
}

void inline nrf24l01::readReg_rx_addr_p5() {
	this->reg_rx_addr_p5= this->readShortRegister(reg_enum::REG_RX_ADDR_P5);
}

void inline nrf24l01::readReg_tx_addr() {
	this->readLongRegister(reg_enum::REG_TX_ADDR, this->reg_tx_addr);
}

void inline nrf24l01::readReg_rx_pw_p0() {
	this->reg_rx_pw_p0 = this->readShortRegister(reg_enum::REG_RX_PW_P0);
}

void inline nrf24l01::readReg_rx_pw_p1() {
	this->reg_rx_pw_p1 = this->readShortRegister(reg_enum::REG_RX_PW_P1);
}

void inline nrf24l01::readReg_rx_pw_p2() {
	this->reg_rx_pw_p2 = this->readShortRegister(reg_enum::REG_RX_PW_P2);
}

void inline nrf24l01::readReg_rx_pw_p3() {
	this->reg_rx_pw_p3 = this->readShortRegister(reg_enum::REG_RX_PW_P3);
}

void inline nrf24l01::readReg_rx_pw_p4() {
	this->reg_rx_pw_p4 = this->readShortRegister(reg_enum::REG_RX_PW_P4);
}

void inline nrf24l01::readReg_rx_pw_p5() {
	this->reg_rx_pw_p5 = this->readShortRegister(reg_enum::REG_RX_PW_P5);
}

void inline nrf24l01::readReg_fifo_status() {
	this->reg_fifo_status = this->readShortRegister(reg_enum::REG_FIFO_STATUS);
}

void inline nrf24l01::readReg_dynpd() {
	this->reg_dynpd = this->readShortRegister(reg_enum::REG_DYNPD);
}

void inline nrf24l01::readReg_feature() {
	this->reg_feature = this->readShortRegister(reg_enum::REG_FEATURE);
}

void inline nrf24l01::writeReg_config() {
	this->writeShortRegister(reg_enum::REG_CONFIG, this->reg_config);
}

void inline nrf24l01::writeReg_en_aa() {
	this->writeShortRegister(reg_enum::REG_EN_AA, this->reg_en_aa);
}

void inline nrf24l01::nrf24l01::writeReg_en_rxaddr() {
	this->writeShortRegister(reg_enum::REG_EN_RXADDR, this->reg_en_rxaddr);
}

void inline nrf24l01::writeReg_setup_aw() {
	this->writeShortRegister(reg_enum::REG_SETUP_AW, this->reg_setup_aw);
}

void inline nrf24l01::writeReg_setup_retr() {
	this->writeShortRegister(reg_enum::REG_SETUP_RETR, this->reg_setup_retr);
}

void inline nrf24l01::writeReg_rf_ch() {
	this->writeShortRegister(reg_enum::REG_RF_CH, this->reg_rf_ch);
}

void inline nrf24l01::writeReg_setup() {
	this->writeShortRegister(reg_enum::REG_SETUP, this->reg_setup);
}

void inline nrf24l01::writeReg_status() {
	this->writeShortRegister(reg_enum::REG_STATUS, this->reg_status);
}

void inline nrf24l01::writeReg_rx_addr_p0() {
	this->writeLongRegister(reg_enum::REG_RX_ADDR_P0, this->reg_rx_addr_p0);
}

void inline nrf24l01::writeReg_rx_addr_p1() {
	this->writeLongRegister(reg_enum::REG_RX_ADDR_P1, this->reg_rx_addr_p1);
}

void inline nrf24l01::writeReg_rx_addr_p2() {
	this->writeShortRegister(reg_enum::REG_RX_ADDR_P2, this->reg_rx_addr_p2);
}

void inline nrf24l01::writeReg_rx_addr_p3() {
	this->writeShortRegister(reg_enum::REG_RX_ADDR_P3, this->reg_rx_addr_p3);
}

void inline nrf24l01::writeReg_rx_addr_p4() {
	this->writeShortRegister(reg_enum::REG_RX_ADDR_P4, this->reg_rx_addr_p4);
}

void inline nrf24l01::writeReg_rx_addr_p5() {
	this->writeShortRegister(reg_enum::REG_RX_ADDR_P5, this->reg_rx_addr_p5);
}

void inline nrf24l01::writeReg_tx_addr() {
	this->writeLongRegister(reg_enum::REG_TX_ADDR, this->reg_tx_addr);
}

void inline nrf24l01::writeReg_rx_pw_p0() {
	this->writeShortRegister(reg_enum::REG_RX_PW_P0, this->reg_rx_pw_p0);
}

void inline nrf24l01::writeReg_rx_pw_p1() {
	this->writeShortRegister(reg_enum::REG_RX_PW_P1, this->reg_rx_pw_p1);
}

void inline nrf24l01::writeReg_rx_pw_p2() {
	this->writeShortRegister(reg_enum::REG_RX_PW_P2, this->reg_rx_pw_p2);
}

void inline nrf24l01::writeReg_rx_pw_p3() {
	this->writeShortRegister(reg_enum::REG_RX_PW_P3, this->reg_rx_pw_p3);
}

void inline nrf24l01::writeReg_rx_pw_p4() {
	this->writeShortRegister(reg_enum::REG_RX_PW_P4, this->reg_rx_pw_p4);
}

void inline nrf24l01::writeReg_rx_pw_p5() {
	this->writeShortRegister(reg_enum::REG_RX_PW_P5, this->reg_rx_pw_p5);
}

void inline nrf24l01::writeReg_dynpd() {
	this->writeShortRegister(reg_enum::REG_DYNPD, this->reg_dynpd);
}

void inline nrf24l01::writeReg_feature() {
	this->writeShortRegister(reg_enum::REG_FEATURE, this->reg_feature);
}

#endif
