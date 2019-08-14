
#define F_CPU 16000000
#include<util/delay.h>
#include "SPI.h"

void spiInitMaster(void)
{
	controlddr |= (1<<SCK)|(1<<MOSI) |(1<<DS);		// SCK, MOSI, DS and TS as outputs
	controlddr &= ~(1<<MISO);								// MISO as input
	controlport |= (1<<cs_disp); // | (1<<cs_touch);			// Set Slaves High
	
	SPSR = displaySPSR;				 // Clock/2
	SPCR = displaySPCR;
}

void beginTransaction()
{
	SPSR = (1<<SPI2X);				 // Clock/2
	SPCR = (1<<SPE) | (1<<MSTR);
}

void writeByte (uint8_t b)
{
	controlport |=(1<<dc);		//set dc high for data
	_delay_us(1);				//delay
	controlport &=~(1<<cs_disp);		//set cs low for operation
	spiTransmit(b);
	controlport |= (1<<cs_disp);
	controlport &=~ (1<<dc);	//set dc low
}

void writeCmd (uint8_t cmd)
{
	controlport &=~((1<<dc)|(1<<cs_disp));	//dc and cs both low to send command
	_delay_us(5);						//little delay
	spiTransmit(cmd);
	controlport |=(1<<cs_disp);				//pull high cs
}

void spiStartWrite()
{
	SPCR = displaySPCR;
	SPSR = displaySPSR;
	controlport |=(1<<dc);		//set dc high for data
	_delay_us(1);				//delay
	controlport &= ~(1<<cs_disp);		//Chip select  (low)
}

void spiEndWrite()
{
	controlport |= (1<<cs_disp);			//Chip deselect (high)
	controlport &=~ (1<<dc);	//set dc low
}

void writeByteTouch (uint8_t b)
{
	controlport |=(1<<dc);		//set dc high for data
	_delay_us(1);				//delay
	controlport &=~(1<<cs_touch);		//set cs low for operation
	spiTransmit(b);
	controlport |= (1<<cs_touch);
	controlport &=~ (1<<dc);	//set dc low
}

void spiStartWriteTouch() 
{
	SPCR = touchSPCR;
	SPSR = touchSPSR;
	//controlport |=(1<<dc);		//set dc high for data
	//_delay_us(1);				//delay
	controlport &= ~(1<<cs_touch);		//Chip select  (low)
}
void spiEndWriteTouch()
{
	controlport |= (1<<cs_touch);			//Chip deselect (high)
	//controlport &=~ (1<<dc);	//set dc low
	//SPSR = (1<<SPI2X);	//Clock back to/2
}

void spiInitSlave(void)
{
	controlddr &= ~(1<<SCK) | (1<<MOSI) | (1<<DS) | (1<<TS);   // SCK, MOSI and SS as outputs
	controlddr |= (1<<MISO);					// MISO as input
	
	SPCR &= ~(1<<MSTR);                // Set as slave
	SPCR |= (1<<SPI2X);				 // Clock/2
	SPCR |= (1<<SPE);                // Enable SPI
}

int spiReceive(void)
{
	while(!(SPSR & (1<<SPIF)));    // wait until complete
	dataIn = SPDR;					//Save input
	return dataIn;					
}

int spiTransmit(uint8_t dataOut)
{
	SPDR = dataOut;                 // send data
	asm volatile("nop");
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}