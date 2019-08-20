#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include "EntityInitConfig.h"

class Enemy {
private:
	EntityInitConfig entityCfg;
	Entity entity;
	int health = this->entityCfg.playerInitLife;
	bool ghostFlag;

public:
	Enemy(int xPos, int yPos) {
		this->entity = Entity(xPos, yPos);
		this->ghostFlag = false;
	}

	Enemy() {
		this->entity = Entity(entityCfg.notSpawnedPos, entityCfg.notSpawnedPos);
		this->ghostFlag = true;
	}

	int getPosX() {
		return this->entity.getPosX();
	}

	int getPosY() {
		return this->entity.getPosY();
	}

	void makeMove() {
		if (this->getPosY() >= entityCfg.earthDamageRow) {
			this->entity.move(entityCfg.enemyMoveDirection, entityCfg.enemyMoveDistance);
		}
	}
};

#endif
