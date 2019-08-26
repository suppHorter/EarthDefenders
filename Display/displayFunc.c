#include "displayFunc.h"
#include "SPI.h"
#include "Serial.h"
#include <stdio.h>
#define PLAYERSIZE 30
#define PLAYERLEN 113

//cooles Schiff:
uint8_t playerBitmap[PLAYERLEN] = {0,6,0,0,0,60,0,0,1,248,0,0,6,96,0,0,16,128,0,0,66,0,0,129,8,16,2,7,224,64,8,25,129,0,112,102,14,1,67,252,40,5,14,112,160,20,249,242,128,127,255,254,1,207,255,56,6,60,28,96,51,247,124,193,147,221,201,142,143,7,23,60,253,255,60,228,247,242,115,163,223,197,207,63,255,207,57,255,255,156,238,239,119,115,241,60,143,199,132,242,30,12,19,200,48,48,6,0,192,0,0,0};// uint8_t playerBitmap[PLAYERLEN] = {0,0,0,0,0,3,128,7,199,143,143,31,30,56,56,0,0,128,65,1,131,3,7,140,3,240,1,224,0};uint8_t charBitmap[27][13] = {	{0,0,0,0,0,0,0,0,0,0,0,0,0},						// 	{0,15,7,225,152,102,31,135,225,152,102,0,0},		// A
	{0,62,12,195,48,248,51,12,195,48,248,0,0},			// B
	{0,31,14,99,24,192,48,12,99,152,124,0,0 },			// C
	{0,63,12,99,12,195,48,204,51,24,252,0,0},			// D
	{0,63,15,195,0,248,62,12,3,240,252,0,0},			// E
	{0,31,135,225,128,120,30,6,1,128,96,0,0},			// F
	{0,15,7,225,128,96,27,134,97,248,60,0,0},			// G
	{0,25,134,97,152,126,31,134,97,152,102,0,0},		// H
	{0,15,3,192,96,24,6,1,128,240,60,0,0},				// I
	{0,15,131,224,24,6,9,130,96,248,28,0,0},			// J
	{0,25,134,193,224,112,28,7,129,176,102,0,0},		// K
	{0,24,6,1,128,96,24,6,1,248,126,0,0},				// L
	{0,48,204,51,156,255,54,204,51,12,195,0,0},			// M
	{0,48,206,51,204,219,50,204,243,28,195,0,0},		// N
	{0,15,7,227,156,195,48,206,113,248,60,0,0},			// O
	{0,31,6,97,152,102,31,6,1,128,96,0,0},				// P
	{0,31,140,51,12,195,50,204,243,24,125,0,0},			// Q
	{0,31,6,97,152,126,25,6,65,152,102,0,0},			// R
	{0,15,7,225,136,112,7,4,97,248,60,0,0},				// S
	{0,63,207,240,96,24,6,1,128,96,24,0,0},				// T
	{0,25,134,97,152,102,25,134,97,248,60,0,0},			// U
	{0,48,204,51,12,102,25,131,192,96,24,0,0},			// V
	{0,48,204,51,12,219,63,206,115,12,195,0,0},			// W
	{0,48,198,96,240,24,6,3,193,152,195,0,0},			// X
	{0,48,204,49,152,60,6,1,128,96,24,0,0},				// Y	{0,63,140,96,48,24,12,6,3,24,254,0}					// Z};
uint8_t Stern[7]={146,81,207,231,21,73,0};void controller_begin() 
{
	spiInitMaster();
	initDisplay();
	//soft reset
	writeCmd(0x01);
	_delay_ms(1000);

	//power control A
	writeCmd(0xCB);
	writeByte(0x39);
	writeByte(0x2C);
	writeByte(0x00);
	writeByte(0x34);
	writeByte(0x02);

	//power control B
	writeCmd(0xCF);
	writeByte(0x00);
	writeByte(0xC1);
	writeByte(0x30);

	//driver timing control A
	writeCmd(0xE8);
	writeByte(0x85);
	writeByte(0x00);
	writeByte(0x78);

	//driver timing control B
	writeCmd(0xEA);
	writeByte(0x00);
	writeByte(0x00);

	//power on sequence control
	writeCmd(0xED);
	writeByte(0x64);
	writeByte(0x03);
	writeByte(0x12);
	writeByte(0x81);

	//pump ratio control
	writeCmd(0xF7);
	writeByte(0x20);

	//power control,VRH[5:0]
	writeCmd(ILI9341_PWCTR1);
	writeByte(0x23);

	//Power control,SAP[2:0];BT[3:0]
	writeCmd(ILI9341_PWCTR1);
	writeByte(0x10);

	//vcm control
	writeCmd(ILI9341_VMCTR1);
	writeByte(0x3E);
	writeByte(0x28);

	//vcm control 2
	writeCmd(ILI9341_VMCTR2);
	writeByte(0x86);

	//memory access control
	writeCmd(ILI9341_MADCTL);
	writeByte(0x48); // 0100 1000
	
	//vertical Scroll
	writeCmd(ILI9341_VSCRSADD);
	writeByte(0x00);

	//pixel format
	writeCmd(ILI9341_PIXFMT);
	writeByte(0x55);

	//frameration control,normal mode full colours
	writeCmd(ILI9341_FRMCTR1);
	writeByte(0x00);
	writeByte(0x18);

	//display function control
	writeCmd(ILI9341_DFUNCTR);
	writeByte(0x08);
	writeByte(0x82);
	writeByte(0x27);

	//3gamma function disable
	writeCmd(0xF2);
	writeByte(0x00);

	//gamma curve selected
	writeCmd(ILI9341_GAMMASET);
	writeByte(0x01);

	//set positive gamma correction
	writeCmd(ILI9341_GMCTRP1);
	writeByte(0x0F);
	writeByte(0x31);
	writeByte(0x2B);
	writeByte(0x0C);
	writeByte(0x0E);
	writeByte(0x08);
	writeByte(0x4E);
	writeByte(0xF1);
	writeByte(0x37);
	writeByte(0x07);
	writeByte(0x10);
	writeByte(0x03);
	writeByte(0x0E);
	writeByte(0x09);
	writeByte(0x00);

	//set negative gamma correction
	writeCmd(ILI9341_GMCTRN1);
	writeByte(0x00);
	writeByte(0x0E);
	writeByte(0x14);
	writeByte(0x03);
	writeByte(0x11);
	writeByte(0x07);
	writeByte(0x31);
	writeByte(0xC1);
	writeByte(0x48);
	writeByte(0x08);
	writeByte(0x0F);
	writeByte(0x0C);
	writeByte(0x31);
	writeByte(0x36);
	writeByte(0x0F);

	//exit sleep
	writeCmd(ILI9341_SLPOUT);
	_delay_ms(120);
	writeByte(0x80);
	
	//display on
	writeCmd(ILI9341_DISPON);
	writeByte(0x80);
}
void resetDisplay()	
{
	rstport |=(1<<rst);			//pull high if low previously
	_delay_ms(200);
	rstport &=~(1<<rst);		//low for reset
	_delay_ms(200);
	rstport |=(1<<rst);			//again pull high for normal operation
	_delay_ms(200);
}void initDisplay()
{
	resetDisplay();
	rstddr=0xFF;				//output for reset
	rstport |=(1<<rst);			//pull high for normal operation
	controlddr|=(1<<dc);		//D/C as output
}void writeWord (uint16_t w)
{
	writeByte(w >> 8);					// write upper 8 bits
	writeByte(w & 0x00FF);				// write lower 8 bits
}//0x00 - 0x13F oder 0x00 - 0xEFvoid setAddrWindow(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h)
{
	writeCmd(ILI9341_CASET); // Column addr set
	writeWord(x0);
	writeWord(x0 + w - 1);
	writeCmd(ILI9341_PASET); // Row addr set
	writeWord(y0);
	writeWord(y0 + h - 1);
	writeCmd(ILI9341_RAMWR); // write to RAM
}

void write565(uint16_t data, uint32_t count)
{
	for(;count>0;count--) 
	{
		writeWord(data);	 //send all pixeldata
	}	
}

void drawPixel (uint16_t x, uint16_t y, uint16_t color)
{
	if((x >= 0) && (x < ILI9341_TFTWIDTH) && (y >= 0) && (y < ILI9341_TFTHEIGHT))
	{
		spiStartWrite();
		setAddrWindow(x, y, PXSIZE, PXSIZE); // set active region = 1 pixel
		write565(color, PXSIZE * PXSIZE); // send color for this pixel
		spiEndWrite();
	}
}

void fillRect (uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t color)
{
	spiStartWrite();
	setAddrWindow(x0, y0, w, h); // set active region
	write565(color, w * h); // set color data for all pixels
	spiEndWrite();
}


void writeBitmap(uint8_t data[], uint32_t count, uint16_t col)
{
	uint8_t bitMask = 128;
	uint32_t i = 0;
	for(;i<count;i++)
	{
		bitMask = 128;
		while (bitMask) 
		{
			if ((data[i] & bitMask))
			{
				writeWord(col);	 //send col1
			}
			else
			{
				writeWord(BLACK);	 //send col2
			}
			bitMask = (bitMask >> 1);
		}
	}
}

void drawBitmapPlayer(uint16_t x, uint16_t y)
{
	if((x >= 0) && (x < ILI9341_TFTWIDTH) && (y >= 0) && (y < ILI9341_TFTHEIGHT))
	{
		spiStartWrite();
		setAddrWindow(x, y, PLAYERSIZE, PLAYERSIZE); // set active region = 30 x 30
		writeBitmap(playerBitmap, PLAYERLEN, GREEN); // send color for this pixel
		spiEndWrite();
	}
}

void drawBitmapChar(uint16_t x, uint16_t y, uint8_t charArrayIndex)
{
	if((x >= 0) && (x < ILI9341_TFTWIDTH) && (y >= 0) && (y < ILI9341_TFTHEIGHT))
	{
		spiStartWrite();
		setAddrWindow(x, y, 10, 10); // set active region = 1 pixel
		writeBitmap(charBitmap[charArrayIndex], 10, WHITE); // send color for this pixel
		spiEndWrite();
	}
}

void drawStar(uint16_t x, uint16_t y)
{
	if((x >= 0) && (x < ILI9341_TFTWIDTH) && (y >= 0) && (y < ILI9341_TFTHEIGHT))
	{
		spiStartWrite();
		setAddrWindow(x, y, 7, 7); // set active region = 1 pixel
		writeBitmap(Stern, 7, WHITE); // send color for this pixel
		spiEndWrite();
	}
}