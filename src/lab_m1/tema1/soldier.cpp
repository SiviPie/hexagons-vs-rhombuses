#include "soldier.h"

// CONSTRUCTORS
Soldier::Soldier(float posx, float posy, int type, int health, bool isAlive, float scale) : posx(posx), posy(posy), type(type),  isAlive(isAlive), scale(scale) { }

Soldier::Soldier(Soldier& s):posx(s.posx), posy(s.posy), type(s.type), isAlive(s.isAlive), scale(s.scale) { }

// GETTERS
float Soldier::getPosx() {
	return posx;
}

float Soldier::getPosy() {
	return posy;
}

float Soldier::getScale() {
	return scale;
}

int Soldier::getType() {
	return type;
}

int Soldier::getLine() {
	// lines_posy: 400, 250, 100
	return (400 - posy) / 150;
}

bool Soldier::getIsAlive() {
	return isAlive;
}

// SETTERS
void Soldier::setPosx(float posx) {
	this->posx = posx;
}

void Soldier::setPosy(float posy) {
	this->posy = posy;
}

void Soldier::setPos(float posx, float posy) {
	this->posx = posx;
	this->posy = posy;
}

void Soldier::setIsAlive(bool isAlive) {
	this->isAlive = isAlive;
}

void Soldier::setScale(float scale) {
	this->scale = scale;
}