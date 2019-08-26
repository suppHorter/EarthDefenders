
#ifdef __cplusplus
extern "C" {
	#include "../Display/displayFunc.h"
	#endif
	#ifdef __cplusplus
}
#endif
#include "player.h"
#include <stdint.h>

Player::Player(uint16_t xPos, uint16_t yPos) {
	this->pxX = xPos;
	this->pxY = yPos;
}

Player::Player() {
	this->pxX = 50;
	this->pxY = 50;
}

void Player::movePlayer(uint16_t newXPos) {
	this->pxX = newXPos;
}

void Player::renderPlayer() {
	drawBitmapPlayer(this->pxX, 60);
}