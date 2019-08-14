#include "displayFunc.h"
#include "SPI.h"
#include <stdio.h>


uint8_t *buffer;
void controller_begin() 
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
	setAddrWindow(x0, y0, w, h); // set active region
	write565(color, w * h); // set color data for all pixels
}

