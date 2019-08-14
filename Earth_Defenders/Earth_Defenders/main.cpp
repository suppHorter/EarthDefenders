#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

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

	uint16_t col = 0xFFFF;
	uint16_t pxX = 50;
	uint16_t pxY = 50;

	while (1)
	{
		drawPixel(pxX, pxY + 10, RED);
		drawPixel(pxX, pxY + 5, GREEN);
		drawPixel(pxX, pxY, BLUE);

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
			getPoint(&pxX, &pxY);
			printf("\nTouch %d %d", pxX, pxY);
		}
	}
}

