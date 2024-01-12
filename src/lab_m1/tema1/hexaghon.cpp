#include "hexaghon.h"

// CONSTRUCTORS
Hexaghon::Hexaghon(float posx, int line, int type, int health) : Soldier(posx, line, type), health(health) { }

Hexaghon::Hexaghon(Hexaghon& h) : Soldier(h), health(h.health) { }

// GETTERS
int Hexaghon::getHealth() {
	return health;
}

// SETTERS
void Hexaghon::setHealth(int health) {
	this->health = health;
}