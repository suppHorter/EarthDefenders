#include "game.h"

Game::Game() {
}

void Game::startGame()
{
	this->player = Player(this->xBounds / 2, this->yBounds - 50);
}

void Game::setPlayerPos(uint8_t x) {
	this->player.movePlayer(x);
}

void Game::render() {
	this->player.renderPlayer();
}
