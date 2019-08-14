#ifndef PLAYER
#define PLAYER
#include "player.h"

Player::Player(uint16_t xCoords, uint16_t yCoords) {
	Entity(xCoords, yCoords, GREEN); 
}

void Player::show() {
	Entity.render();
}

#endif