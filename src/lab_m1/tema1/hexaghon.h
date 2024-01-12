#pragma once

#include "soldier.h"

class Hexaghon: public Soldier {
public:
	// CONSTRUCTORS
	Hexaghon(float posx = 0, int line = 0, int type = 0, int health = 3);
	Hexaghon(Hexaghon& );

	// GETTERS
	int getHealth();

	// SETTERS
	void setHealth(int);

protected:
	int health; // 0->4, 0 meaning dead
};