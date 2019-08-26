#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "Game/game.h"
#include "Game/textWriter.h"

#ifdef __cplusplus
extern "C" {
	#include "Display/displayFunc.h"
	#include "Display/Touch.h"
	#include "Display/Serial.h"
	#include <stdio.h>
	#endif
	#ifdef __cplusplus
}
#endif


int main(void)
{
	Serial_begin();
	controller_begin();
	if (!touch_begin())
	{
		printf("No Touch!\n");
	}

	fillRect(0, 0,ILI9341_TFTWIDTH-1, ILI9341_TFTHEIGHT-1, BLACK);

	TextWriter textService = TextWriter();
	textService.setCursorPos(ILI9341_TFTWIDTH-10, 300);
	
	textService.drawString("HALLO WELT", 10);
	
	textService.setCursorPos(ILI9341_TFTWIDTH-10, 270);
	
	textService.drawString("HALLO FELIX", 11);

	Game game = Game();
	game.startGame();

	uint16_t col = 0xFFFF;
	uint16_t pxX = 50;
	uint16_t pxY = 50;

	while (1)
	{
		if (bufferEmpty()) 
		{
			_delay_ms(100);
		}
		if (!touched())
		{		
			_delay_ms(100);
		} 
		else 
		{
			drawPixel(pxX, 60, BLACK);
			getPoint(&pxX, &pxY);
			game.setPlayerPos(pxX);
			// drawBitmap(pxX, 60, player);
			// printf("\nTouch %d %d", pxX, pxY);
		}
		game.render();
	}
}
