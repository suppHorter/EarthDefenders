#ifndef ENTITY_H
#define ENTITY_H
#include "entity.h"
#include <>

Entity::Entity(uint16_t xCoords, uint16_t yCoords, uint16_t col) {
	this->xCoords = xCoords;
	this->yCoords = yCoords;
}

void Entity::moveEnt(uint8_t dir, uint8_t spd) {
	//DIR:  1UP, 2RIGHT, 3DOWN, 4LEFT
	
	if (dir == 1) {
		xCoords += spd;
	}

	if (dir == 2) {
		yCoords += spd;
	}
	if (dir == 3) {
		xCoords -= spd;
	}

	if (dir == 4) {
		yCoords -= spd;
	}
	
}

void Entity::getX() {
	return xCoords;
}

void Entity::getY() {
	return yCoords;
}

void Entity::render() {
	drawPixel(Entity->xCoords, Entity->yCoords, Entity->col);
	_delay_ms(10);
	drawPixel(Entity->xCoords, Entity->yCoords, BLACK);
}

#endif