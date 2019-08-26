
#ifdef __cplusplus
extern "C" {
	#include "../Display/displayFunc.h"
	#endif
	#ifdef __cplusplus
}
#endif
#include "textWriter.h"
#include <stdint.h>

TextWriter::TextWriter() {
	this->cursorX = 0;
	this->cursorY = 0;
}

void TextWriter::setCursorPos(uint16_t xPos, uint16_t yPos) {
	this->cursorX = xPos;
	this->cursorY = yPos;
}

void TextWriter::drawChar(char c) {
	if (c == ' ') {c = 64;}
	uint8_t arrayIndex = c - 64;

	if (this->cursorX > ILI9341_TFTWIDTH-10) {
		this->cursorX = 10;
		this->cursorY += 10;
	} else {
		this->cursorX += 10;
	}
	drawBitmapChar(this->cursorX, this->cursorY, arrayIndex);
}

void TextWriter::drawString(char *s, uint8_t length) {
	uint8_t i = 0;
	for (;i<length;i++) {
		this->drawChar(s[i]);
	}
}