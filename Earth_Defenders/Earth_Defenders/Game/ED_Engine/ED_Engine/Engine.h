#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <stdlib.h>
#include "Player.h"
#include "Enemy.h"
#include "EngineInitConfig.h"
#include "EntityInitConfig.h"
#include "RandomNumberGenerator.cpp"

#define ENEMY_ARRAY_HEIGHT 9 // TODO: muss mit config initialisiert werden...
#define ENEMY_ARRAY_WIDTH 6 // TODO: muss mit config initialisiert werden...

#define ENEMY_ARRAY_LEN ENEMY_ARRAY_HEIGHT * ENEMY_ARRAY_WIDTH

#include <iostream>
using namespace std;

class Engine {
private:
	int enemyHighestIndex;
	bool gameStarted; // ToImplement
	EntityInitConfig entConfig;
	EngineInitConfig engineConfig;
	RandomNumberGenerator rng;
	Enemy enemies[ENEMY_ARRAY_HEIGHT][ENEMY_ARRAY_WIDTH];
	int enemyPos[ENEMY_ARRAY_LEN][2];
	Player player;

	void spawnPlayer() {
		player = Player(entConfig.playerStartPositionX, entConfig.playerStartPositionY);
	}

	void spawnEnemy() {
		//check if Enemies same pos
		enemyHighestIndex++;
		for (int i = 0; i < ENEMY_ARRAY_WIDTH; i++) {
			int rndNum = rng.getRandomNumber(engineConfig.gameFieldCols);
			if (!enemyPositionBlocked(rndNum)) {
				enemies[0][i] = Enemy(rndNum, entConfig.enemyStartPositionY);
			}
			else {
				enemies[0][i] = Enemy(); // Ghost
			}
		}
	}

	bool enemyPositionBlocked(int pos) {
		for (int i = 0; i < ENEMY_ARRAY_WIDTH; i++) {
			if (enemies[0][i].getPosX() == pos) {
				return true;
			}
		}
		return false;
	}

public:
	Engine() {}
	Engine(RandomNumberGenerator rng) {
		this->rng = rng;
	}

	void startGame() {
		this->enemyHighestIndex = 0;
		for (int i = 0; i < ENEMY_ARRAY_LEN; i++) {
			enemies[0][i] = Enemy();
		}
		spawnEnemy();
		spawnPlayer();
	}

	void calculateNextView() {
		for (int i = 0; (i < ENEMY_ARRAY_HEIGHT) && (i <= enemyHighestIndex); i++) {
			for (int j = 0; j < ENEMY_ARRAY_WIDTH; j++) {
				this->enemies[i][j].makeMove();
				this->enemies[i + 1][j] = this->enemies[i][j];
			}
		}

		spawnEnemy();
	}

	void renderView() {
		system("CLS");

		cout << "\n-----\nPlayer-Pos: X: " << this->player.getPosX() << "Y: " << this->player.getPosY() << endl << endl;
		int enemyCnt = 0;
		for (int i = 0; i < ENEMY_ARRAY_HEIGHT; i++) {
			for (int j = 0; j < ENEMY_ARRAY_WIDTH; j++) {
				this->enemyPos[enemyCnt][0] = this->enemies[i][j].getPosX();
				this->enemyPos[enemyCnt][1] = this->enemies[i][j].getPosY();
				enemyCnt++;
			}
		}

		for (int i = ENEMY_ARRAY_HEIGHT; i >= 0 ; i--) {
			for (int j = ENEMY_ARRAY_WIDTH; j >= 0; j--) {
				if (enemyOnPosition(i, j)) {
					cout << entConfig.enemy2DModel;
				} else {
					cout << ' ';
				}
			}
			cout << endl;
		}
	}
	bool enemyOnPosition(int posX, int posY) {
		for (int i = 0; i < ENEMY_ARRAY_LEN; i++) {
			if ((this->enemyPos[i][1] == posX) && (this->enemyPos[i][0] == posY)) {
				return true;
			}
		}
		return false;
	}
};
#endif