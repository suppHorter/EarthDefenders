#ifdef __cplusplus
extern "C" {
	#include "../Display/displayFunc.h"
	#endif
	#ifdef __cplusplus
}
#endif
#include "bullet.h"

Bullet::Bullet() {
	
}

void Bullet::setPos(uint16_t xPos, uint16_t yPos) {
	this->xPos = xPos;
	this->yPos = yPos;
}

void Bullet::moveBullet() {
	this->yPos += 3;
}

void Bullet::renderBullet() {
	drawBitmapBullet(this->xPos, this->yPos);
}