#pragma once
#include "utils/glm_utils.h" //for glm::vec2

class Soldier {
public:
	// CONSTRUCTORS
	Soldier(float posx = 0, float posy = 0, int type = 0, int health = 0, bool isAlive = true, float scale = 1);
	Soldier::Soldier(Soldier& s);

	// GETTERS
	float getPosx();
	float getPosy();
	float getScale();
	int getType();
	int getLine();
	bool getIsAlive();

	// SETTERS
	void setPosx(float posx);
	void setPosy(float posy);
	void setPos(float posx, float posy);
	void setIsAlive(bool isAlive);
	void setScale(float scale);

protected:
	float posx;
	float posy;
	float scale;
	int type;
	bool isAlive;
};