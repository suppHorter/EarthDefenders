#ifndef PLAYER
#define PLAYER

class Player: Entity {
	private:
	uint16_t col;
	public:
	Player(uint16_t xCoords, uint16_t yCoords);
	Player::show();
};

#endif