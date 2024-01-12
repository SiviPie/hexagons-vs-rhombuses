#include "rhombus.h"

// CONSTRUCTORS
Rhombus::Rhombus(float posx, int line, int type, int price) : Soldier(posx, line, type), time_last_bullet(2.5f), price(price) { }

Rhombus::Rhombus(Rhombus& r):Soldier(r), time_last_bullet(r.time_last_bullet), price(r.price) { }

// GETTERS
float Rhombus::getTimeLastBullet() {
	return time_last_bullet;
}

int Rhombus::getPrice() {
	return price;
}

int Rhombus::getColumn() {
	// lines_x: 150, 300, 450
	return posx / 150 - 1;
}

// SETTERS
void Rhombus::setTimeLastBullet(float time_last_bullet) {
	this->time_last_bullet = time_last_bullet;
}