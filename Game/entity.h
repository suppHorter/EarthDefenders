#ifndef ENTITY_H
#define ENTITY_H

class Entity {
	private:
	uint16_t xCoords,
	uint16_t yCoords,
	uint16_t col;

	public:
	Entity(uint16_t xCoords, uint16_t yCoords, uint16_t col);
	void moveEnt(uint8_t dir, uint8_t spd);
	void getX();
	void getY();
	void render();
};

#endif