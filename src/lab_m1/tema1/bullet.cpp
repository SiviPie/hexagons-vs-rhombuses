#include "bullet.h"
// BULLET

Bullet::Bullet(float posx, float posy, int type, float rotation): posx(posx), posy(posy), type(type), rotation(rotation) {}

Bullet::Bullet(Bullet& b): posx(b.posx), posy(b.posy), type(b.type), rotation(b.rotation) {}

// GETTERS
float Bullet::getPosx() {
	return posx;
}

int Bullet::getPosy() {
	return posy;
}

int Bullet::getType() {
	return type;
}

float Bullet::getRotation() {
	return rotation;
}

// SETTERS
void Bullet::setPosx(float posx) {
	this->posx = posx;
}

void Bullet::setPosy(float posy) {
	this->posy = posy;
}

void Bullet::setRotation(float rotation) {
	this->rotation = rotation;
}