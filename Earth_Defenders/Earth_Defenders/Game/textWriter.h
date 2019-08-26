#ifndef TEXTWRITER_H
#define TEXTWRITER_H
#include <stdint.h>

class TextWriter {
	public:
	TextWriter();
	void drawChar(char c);
	void setCursorPos(uint16_t xPos, uint16_t yPos);
	void drawString(char *s, uint8_t length);

	private:
	uint16_t cursorX, cursorY;
};


#endif