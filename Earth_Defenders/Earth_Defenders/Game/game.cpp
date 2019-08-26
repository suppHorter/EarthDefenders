#include "game.h"

Game::Game() {
}

void Game::startGame()
{
	this->player = Player(40, 40);
}

void Game::setPlayerPos(uint8_t x) {
	this->player.movePlayer(x);
}

void Game::render() {
	this->player.renderPlayer();
}
