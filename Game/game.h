#ifndef GAME_H
#define GAME_H
#include "player.h"

class Game {
	private:
		Player player; 
		uint16_t xBounds = 240;
		uint16_t yBounds = 320;

	public:
		Game();
		void startGame();
		void render();
		void setPlayerPos(uint8_t x);
};
#endif