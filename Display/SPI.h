#ifndef SPI
#define SPI
#include <avr/io.h>

#define controlport PORTB
#define controlddr DDRB
#define controlpin PINB
#define rstport PORTD
#define rstddr DDRD
#define rstpin PIND
#define rst PORTD7			//RESET

#define dc PORTB1			//DATA / COMMAND
#define cs_disp PORTB2			//DISP SELECT - Arduino Pin: 10

#define cs_touch PORTB0		//TOUCH SELECT - A Pin: 8

#define DS DDB2		//DISPLAY SELECT DDRB
#define TS DDB0		//TOUCH SELECT DDRB
#define MOSI DDB3
#define MISO DDB4
#define SCK DDB5

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C
#define SPI_MODE_MASK 0x0C  // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03  // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 0x01  // SPI2X = bit 0 on SPSR

#define displaySPCR (1<<SPE) | (1<<MSTR)	//passt so nix ändern
#define displaySPSR (1<<SPI2X)				//passt so nix ändern

#define touchSPCR (1<<SPE) | (1<<MSTR) | (1<<SPR0)
#define touchSPSR 0			

char dataIn;

void spiInitMaster(void);
void spiInitSlave(void);
void writeByte (uint8_t b);
void writeByteTouch (uint8_t b);
void writeCmd (uint8_t cmd);
void spiStartWrite();
void spiStartWriteTouch();
void spiEndWrite();
void spiEndWriteTouch();
int spiReceive(void);
int spiTransmit(uint8_t dataOut);
void setDataMode(uint8_t dataMode);

 #endif