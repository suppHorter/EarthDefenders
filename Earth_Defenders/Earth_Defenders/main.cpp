#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "Game/game.h"
#include "Game/textWriter.h"

#include <avr/io.h>
#define F_CPU 16000000
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


uint16_t pxX = ILI9341_TFTWIDTH / 2;
uint16_t pxY = ILI9341_TFTHEIGHT - 50;
int main(void)
{
	Serial_begin();
	controller_begin();
	if (!touch_begin())
	{
		printf("No Touch!\n");
	}

	Game game = Game();
	game.startGame();

	while (1)
	{
		if (bufferEmpty()) {
			_delay_ms(50);
		}
		if (!touched()) {
			_delay_ms(50);
		} 
		else
		{
			drawPixel(pxX, ILI9341_TFTHEIGHT - 50, BLACK);
			getPoint(&pxX, &pxY);
			game.setPlayerPos(pxX);
		}
		game.render();
	}
}
