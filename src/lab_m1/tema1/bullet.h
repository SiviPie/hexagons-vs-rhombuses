#pragma once

class Bullet {
public:
	// CONSTRUCTORS
	Bullet(float posx = 0, float posy = 0, int type = 0, float rotation = 0);
	Bullet(Bullet& b);

	// GETTERS
	float getPosx();
	int getPosy();
	int getType();
	float getRotation();

	// SETTERS
	void setPosx(float posx);
	void setPosy(float posy);
	void setRotation(float rotation);

protected:
	float posx;
	float posy;
	float rotation;
	int type;
};