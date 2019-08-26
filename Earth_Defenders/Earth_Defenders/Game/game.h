#ifndef GAME_H
#define GAME_H
#include "player.h"

class Game {
	private:
		Player player;

	public:
		Game();
		void startGame();
		void render();
		void setPlayerPos(uint8_t x);
};
#endif