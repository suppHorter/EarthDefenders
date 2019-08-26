#include "Touch.h"
#define F_CPU 16000000
#include <util/delay.h>
#include "Serial.h"
#include "SPI.h"
uint8_t tempSPSR;
uint8_t tempSPCR;

uint8_t touch_begin()
{
	controlddr |= (1<<TS);		// SCK, MOSI, DS and TS as outputs
	controlport |= (cs_touch);

	writeReg8(STMPE_SYS_CTRL1, STMPE_SYS_CTRL1_RESET);
	_delay_ms(10);

	for (uint8_t i = 0; i < 65; i++) {
		readReg8(i);
	}

	writeReg8(STMPE_SYS_CTRL2, 0x0); // turn on clocks!
	writeReg8(STMPE_TSC_CTRL, (STMPE_TSC_CTRL_XYZ | STMPE_TSC_CTRL_EN)); // XYZ and enable!
	// Serial.println(readRegister8(STMPE_TSC_CTRL), HEX);
	writeReg8(STMPE_INT_EN, STMPE_INT_EN_TOUCHDET);
	writeReg8(STMPE_ADC_CTRL1, STMPE_ADC_CTRL1_10BIT | (0x6 << 4)); // 96 clocks per conversion
	writeReg8(STMPE_ADC_CTRL2, STMPE_ADC_CTRL2_6_5MHZ);
	writeReg8(STMPE_TSC_CFG, STMPE_TSC_CFG_4SAMPLE |
	STMPE_TSC_CFG_DELAY_1MS |
	STMPE_TSC_CFG_SETTLE_5MS);
	writeReg8(STMPE_TSC_FRACTION_Z, 0x6);
	writeReg8(STMPE_FIFO_TH, 1);
	writeReg8(STMPE_FIFO_STA, STMPE_FIFO_STA_RESET);
	writeReg8(STMPE_FIFO_STA, 0); // unreset
	writeReg8(STMPE_TSC_I_DRIVE, STMPE_TSC_I_DRIVE_50MA);
	writeReg8(STMPE_INT_STA, 0xFF); // reset all ints
	writeReg8(STMPE_INT_CTRL, STMPE_INT_CTRL_POL_HIGH | STMPE_INT_CTRL_ENABLE);
	printf("INIT_DONE\n");
	
	return 1;
}

uint8_t readReg8(uint8_t reg)
{
	uint8_t x;
	spiStartWriteTouch();
	spiTransmit(0x80 | reg);
	spiTransmit(0x00);
	x = spiTransmit(0);
	//x = spiReceive();
	spiEndWriteTouch();

	return x;
}

uint16_t getVersion()
{
	uint16_t v;
	// Serial.print("get version");
	v = readReg8(0);
	v <<= 8;
	v |= readReg8(1);
	return v;
}

void writeReg8(uint8_t reg, uint8_t val)
{
	spiStartWriteTouch();
	spiTransmit(reg);
	spiTransmit(val);
	spiEndWriteTouch();
}

uint8_t touched() 
{
	return (readReg8(STMPE_TSC_CTRL) & 0x80);
}

//TODO: implement z-value 
void getPoint(uint16_t *p_X, uint16_t *p_Y) 
{
	uint16_t x, y;
	uint8_t z;
	while (!bufferEmpty()) {
		readData(&x, &y, &z);
	}
	if (bufferEmpty())
	{
		writeReg8(STMPE_INT_STA, 0xFF); // reset
	}


	*p_X = x / 19;
	*p_Y = y / 15;
}

void scalePoint(uint16_t *x, uint16_t *y) 
{
}

uint8_t bufferSize(void) {
	return readReg8(STMPE_FIFO_SIZE);
}

uint8_t bufferEmpty() 
{
	return (readReg8(STMPE_FIFO_STA) & STMPE_FIFO_STA_EMPTY);
}

void readData(uint16_t *x, uint16_t *y, uint8_t *z) 
{
	uint8_t data[4];

	for (uint8_t i = 0; i < 4; i++) {
		data[i] = readReg8(0xD7); // _spi->transfer(0x00);
	}
	*x = data[0];
	*x <<= 4;
	*x |= (data[1] >> 4);
	*y = data[1] & 0x0F;
	*y <<= 8;
	*y |= data[2];
	*z = data[3];

	writeReg8(STMPE_INT_STA, 0xFF); // reset all ints
}