#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "EntityInitConfig.h"

class Player {
private:
	EntityInitConfig entityCfg;
	Entity entity;
	int health = this->entityCfg.playerInitLife;
public:
	Player() {}

	Player(int xPos, int yPos) {
		this->entity = Entity(xPos, yPos);
	}

	int getPosX() {
		return this->entity.getPosX();
	}

	int getPosY() {
		return this->entity.getPosY();
	}

};

#endif
