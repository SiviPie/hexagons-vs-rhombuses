#pragma once

class Resource {
public:
	// CONSTRUCTORS
	Resource(float posx = 0, float posy = 0);
	Resource(Resource& r);
	~Resource();

	// GETTERS
	float getPosx();
	float getPosy();

	// SETTERS
	void setPosx(float);
	void setPosy(float);
	void setPos(float, float);

protected:
	float posx;
	float posy;
};
