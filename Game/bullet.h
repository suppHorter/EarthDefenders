#ifndef BULLET_H
#define BULLET_H
#include <stdint.h>


class Bullet {
	private:
		uint16_t xPos, yPos;
	public:
		Bullet();
		void moveBullet();
		void setPos(uint16_t xPos, uint16_t yPos);
		void renderBullet();
};

#endif // BULLET_H
