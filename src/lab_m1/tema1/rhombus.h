#pragma once
#include "soldier.h"

class Rhombus : public Soldier {
public:
	// CONSTRUCTORS
	Rhombus(float posx = 0, int line = 0, int type = 0, int price = 0);
	Rhombus(Rhombus& );

	// GETTERS
	float getTimeLastBullet();
	int getPrice();
	int getColumn();

	// SETTERS
	void setTimeLastBullet(float time_last_bullet);

protected:
	float time_last_bullet;
	int price;
};