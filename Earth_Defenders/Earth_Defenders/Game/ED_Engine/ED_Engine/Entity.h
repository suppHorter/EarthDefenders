#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "EntityInitConfig.h"

using namespace std;

class Entity {
private:
	EntityInitConfig entityCfg;
	int xPos;
	int yPos;

public:
	Entity(){}
	Entity (int xPos, int yPos)
	{
		this->xPos = xPos;
		this->yPos = yPos;
	}

	int getPosX() {
		return this->xPos;
	}

	int getPosY() {
		return this->yPos;
	}

	void move(int dir, int distance) {
		if (dir == entityCfg.moveDirUp) {
			this->yPos += distance;
		}
		
		if (dir == entityCfg.moveDirDown) {
			this->yPos -= distance;
		}

		if (dir == entityCfg.moveDirLeft) {
			this->xPos -= distance;
		}
		
		if (dir == entityCfg.moveDirRight) {
			this->xPos += distance;
		}
	}
};

#endif