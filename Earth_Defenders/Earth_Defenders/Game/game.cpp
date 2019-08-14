#ifndef GAME_CPP
#define GAME_CPP
#include "player.h"
#include "game.h"

Game::Game();

void Game::startGame() {
	Player: player = new Player(20, (uint16_t)ILI9341_TFTHEIGHT/2);
	player.show();
}

#endif