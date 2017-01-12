#include "nrf24l01.h"
// #include <unistd.h>
#include <string.h>

nrf24l01::nrf24l01(Spi *s, Gpio *g) {

	this->spi = s;
	this->gpio = g;
	this->spi->init();
	this->readRegs();
}

nrf24l01::~nrf24l01() {
	delete this->spi;
	this->spi = NULL;
}

void nrf24l01::readRXPayload(uint8_t *buf, uint8_t len) {
	spi->setCmd(CMD_R_RX_PAYLOAD);
	spi->spiTransfer(len + 1);
	spi->getCmdData(buf, len);
	this->reg_status = spi->getStatus();
}

void nrf24l01::writeTXPayload(uint8_t *buf, uint8_t len) {
	spi->setCmd(CMD_W_TX_PAYLOAD);
	spi->setCmdData(buf, len);
	spi->spiTransfer(len+1);
	this->reg_status = spi->getStatus();
}

void nrf24l01::flushTx() {
	spi->setCmd(CMD_FLUSH_TX);
	spi->spiTransfer(1);
	this->reg_status = spi->getStatus();
}

void nrf24l01::flushRx() {
	spi->setCmd(CMD_FLUSH_RX);
	spi->spiTransfer(1);
	this->reg_status = spi->getStatus();
}

void nrf24l01::reuseTxPayload() {
	spi->setCmd(CMD_REUSE_TX_PL);
	spi->spiTransfer(1);
	this->reg_status = spi->getStatus();
}

uint8_t nrf24l01::readRxPayloadWidth() {
	uint8_t ret;
	spi->setCmd(CMD_R_RX_PL_WID);
	spi->spiTransfer(2);
	spi->getCmdData(&ret, 1);
	this->reg_status = spi->getStatus();;
	return ret;
}

void nrf24l01::writeAckPayload(uint8_t pipe, uint8_t *buf, uint8_t len) {
	spi->setCmd(CMD_W_ACK_PAYLOAD | (pipe & 0x07));
	spi->setCmdData(buf, len);
	spi->spiTransfer(len+1);
	this->reg_status = buf[0];
}
void nrf24l01::writeNoAck(uint8_t *buf, uint8_t len) {
	spi->setCmd(CMD_W_TX_PAYLOAD_NOACK);
	spi->setCmdData(buf, len);
	spi->spiTransfer(len+1);
	this->reg_status = buf[0];
}

void nrf24l01::nop() {
	spi->setCmd(CMD_NOP);
	spi->spiTransfer(1);
	this->reg_status = spi->getStatus();
}


//////////////////////////////////////////////////////////////////////////////
///
/// Private members
///
//////////////////////////////////////////////////////////////////////////////


void nrf24l01::readRegs() {
	this->readReg_config();
	this->readReg_en_aa();
	this->readReg_en_rxaddr();
	this->readReg_setup_aw();
	this->readReg_setup_retr();
	this->readReg_rf_ch();
	this->readReg_setup();
	this->readReg_observe_tx();
	this->readReg_rpd();
	this->readReg_rx_addr_p0();
	this->readReg_rx_addr_p1();
	this->readReg_rx_addr_p2();
	this->readReg_rx_addr_p3();
	this->readReg_rx_addr_p4();
	this->readReg_rx_addr_p5();
	this->readReg_tx_addr();
	this->readReg_rx_pw_p0();
	this->readReg_rx_pw_p1();
	this->readReg_rx_pw_p2();
	this->readReg_rx_pw_p3();
	this->readReg_rx_pw_p4();
	this->readReg_rx_pw_p5();
	this->readReg_fifo_status();
	this->readReg_dynpd();
	this->readReg_feature();
}


uint8_t nrf24l01::getShortRegValue(reg_enum r) {
	switch (r) {
	case reg_enum::REG_CONFIG :
		return this->reg_config;
		break;
	case reg_enum::REG_EN_AA :
		return this->reg_en_aa;
		break;
	case reg_enum::REG_EN_RXADDR :
		return this->reg_en_rxaddr;
		break;
	case reg_enum::REG_SETUP_AW :
		return this->reg_setup_aw;
		break;
	case reg_enum::REG_SETUP_RETR :
		return this->reg_setup_retr;
		break;
	case reg_enum::REG_RF_CH :
		return this->reg_rf_ch;
		break;
	case reg_enum::REG_SETUP :
		return this->reg_setup;
		break;
	case reg_enum::REG_STATUS :
		return this->reg_status;
		break;
	case reg_enum::REG_OBSERVE_TX :
		return this->reg_observe_tx;
		break;
	case reg_enum::REG_RPD :
		return this->reg_rpd;
		break;
	case reg_enum::REG_RX_ADDR_P2 :
		return this->reg_rx_addr_p2;
		break;
	case reg_enum::REG_RX_ADDR_P3 :
		return this->reg_rx_addr_p3;
		break;
	case reg_enum::REG_RX_ADDR_P4 :
		return this->reg_rx_addr_p4;
		break;
	case reg_enum::REG_RX_ADDR_P5 :
		return this->reg_rx_addr_p5;
		break;
	case reg_enum::REG_RX_PW_P0 :
		return this->reg_rx_pw_p1;
		break;
	case reg_enum::REG_RX_PW_P1 :
		return this->reg_rx_pw_p2;
		break;
	case reg_enum::REG_RX_PW_P2 :
		return this->reg_rx_pw_p3;
		break;
	case reg_enum::REG_RX_PW_P3 :
		return this->reg_rx_pw_p3;
		break;
	case reg_enum::REG_RX_PW_P4 :
		return this->reg_rx_pw_p4;
		break;
	case reg_enum::REG_RX_PW_P5 :
		return this->reg_rx_pw_p5;
		break;
	case reg_enum::REG_FIFO_STATUS :
		return this->reg_fifo_status;
		break;
	case reg_enum::REG_DYNPD :
		return this->reg_dynpd;
		break;
	case reg_enum::REG_FEATURE :
		return this->reg_feature;
		break;
	default :
		return 0;
	}
}

void nrf24l01::setShortRegValue(reg_enum r, uint8_t val) {
	switch (r) {
	case reg_enum::REG_CONFIG :
		this->reg_config = val;
		break;
	case reg_enum::REG_EN_AA :
		this->reg_en_aa = val;
		break;
	case reg_enum::REG_EN_RXADDR :
		this->reg_en_rxaddr = val;
		break;
	case reg_enum::REG_SETUP_AW :
		this->reg_setup_aw = val;
		break;
	case reg_enum::REG_SETUP_RETR :
		this->reg_setup_retr = val;
		break;
	case reg_enum::REG_RF_CH :
		this->reg_rf_ch = val;
		break;
	case reg_enum::REG_SETUP :
		this->reg_setup = val;
		break;
	case reg_enum::REG_STATUS :
		this->reg_status = val;
		break;
	case reg_enum::REG_OBSERVE_TX :
		this->reg_observe_tx = val;
		break;
	case reg_enum::REG_RPD :
		this->reg_rpd = val;
		break;
	case reg_enum::REG_RX_ADDR_P2 :
		this->reg_rx_addr_p2 = val;
		break;
	case reg_enum::REG_RX_ADDR_P3 :
		this->reg_rx_addr_p3 = val;
		break;
	case reg_enum::REG_RX_ADDR_P4 :
		this->reg_rx_addr_p4 = val;
		break;
	case reg_enum::REG_RX_ADDR_P5 :
		this->reg_rx_addr_p5 = val;
		break;
	case reg_enum::REG_RX_PW_P0 :
		this->reg_rx_pw_p1 = val;
		break;
	case reg_enum::REG_RX_PW_P1 :
		this->reg_rx_pw_p2 = val;
		break;
	case reg_enum::REG_RX_PW_P2 :
		this->reg_rx_pw_p3 = val;
		break;
	case reg_enum::REG_RX_PW_P3 :
		this->reg_rx_pw_p3 = val;
		break;
	case reg_enum::REG_RX_PW_P4 :
		this->reg_rx_pw_p4 = val;
		break;
	case reg_enum::REG_RX_PW_P5 :
		this->reg_rx_pw_p5 = val;
		break;
	case reg_enum::REG_FIFO_STATUS :
		this->reg_fifo_status = val;
		break;
	case reg_enum::REG_DYNPD :
		this->reg_dynpd = val;
		break;
	case reg_enum::REG_FEATURE :
		this->reg_feature = val;
		break;
	default :
		break;
	}
}

uint8_t *nrf24l01::getLongRegValue(reg_enum r) {
	switch (r) {
		case reg_enum::REG_RX_ADDR_P0 :
			return this->reg_rx_addr_p0;
			break;
		case reg_enum::REG_RX_ADDR_P1 :
			return this->reg_rx_addr_p1;
			break;
		case reg_enum::REG_TX_ADDR :
			return this->reg_tx_addr;
			break;
		default :
			return NULL;
	}
}

void nrf24l01::setLongRegValue(reg_enum r, uint8_t *val) {
	switch (r) {
		case reg_enum::REG_RX_ADDR_P0 :
			memcpy(this->reg_rx_addr_p0, val, 5);
			break;
		case reg_enum::REG_RX_ADDR_P1 :
			memcpy(this->reg_rx_addr_p1, val, 5);
			break;
		case reg_enum::REG_TX_ADDR :
			memcpy(this->reg_tx_addr, val, 5);
			break;
		default:
			break;
	}
	this->writeLongRegister(r, val);
}


uint8_t nrf24l01::readShortRegister(reg_enum r)
{
	uint8_t ret;
	spi->setCmd((uint8_t)r);
	spi->spiTransfer(2);
	spi->getCmdData(&ret, 1);
	this->reg_status = spi->getStatus();
	return ret;
}

void nrf24l01::readLongRegister(reg_enum r, uint8_t *buf)
{
	spi->setCmd((uint8_t)r);
	spi->spiTransfer(6);
	spi->getCmdData(buf, 5);
	this->reg_status = spi->getStatus();
}

void nrf24l01::writeShortRegister(reg_enum r, uint8_t value)
{
	spi->setCmd(CMD_W_REGISTER | (uint8_t)r);
	spi->setCmdData(&value, 1);
	spi->spiTransfer(2);
	this->reg_status = spi->getStatus();
}

void nrf24l01::writeLongRegister(reg_enum r, uint8_t *value)
{
	spi->setCmd(CMD_W_REGISTER | (uint8_t)r);
	spi->setCmdData(value, 5);
	spi->spiTransfer(6);
	this->reg_status = spi->getStatus();
}

uint8_t nrf24l01::getBitRegister(reg_enum reg, uint8_t bit, uint8_t lenBits, bool refresh) {
	if (refresh) {
		this->setShortRegValue(reg, this->readShortRegister(reg));
	}
	uint8_t mask = lenBits << bit;
	return ((this->getShortRegValue(reg) & mask) >> bit);
}

void nrf24l01::setBitRegister(reg_enum reg, uint8_t bit, uint8_t val, uint8_t lenBits) {
	uint8_t reg_value = (this->getShortRegValue(reg) & ~(lenBits << bit)) | (val << bit);
	this->setShortRegValue(reg, reg_value);
	this->writeShortRegister(reg, reg_value);
}

int nrf24l01::ceWrite(int value)
{
	return this->gpio->setPinState(value);
}
