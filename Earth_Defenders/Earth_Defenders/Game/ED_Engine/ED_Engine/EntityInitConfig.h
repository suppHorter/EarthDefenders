#ifndef ENTITYINITCONFIG_H
#define ENTITYINITCONFIG_H

#include "EngineInitConfig.h"

class EntityInitConfig {
private:
	EngineInitConfig engineConfig;
public:
	//Move:
	int moveDirUp = 0;
	int moveDirDown = 1;
	int moveDirLeft = 2;
	int moveDirRight = 3;

	//Player:
	char player2DModel = 'A';
	int playerEntityTypeID = 1;
	int playerInitLife = 100;
	int playerStartPositionX = engineConfig.gameFieldRows / 2; // % Bildschirm - Breite
	int playerStartPositionY = 1; // % Bildschirm - Höhe
	int playerMoveDirection0 = this->moveDirRight;
	int playerMoveDirection1 = this->moveDirLeft;

	//Enemy:
	char enemy2DModel = 'O';
	int enemyEntityTypeID = 2;
	int enemyInitLife = 50;
	int enemyStartPositionY = engineConfig.gameFieldRows; // % Bildschirm - Höhe
	int enemyMoveDistance = 1;
	int enemyMoveDirection = this->moveDirDown;
	int notSpawnedPos = -666;

	//Earth:
	int earthDamageRow = 1;

	EntityInitConfig() {}
};

#endif