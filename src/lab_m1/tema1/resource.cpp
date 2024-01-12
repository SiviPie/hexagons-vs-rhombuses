#include "resource.h"

// CONSTRUCTORS
Resource::Resource(float posx, float posy) : posx(posx), posy(posy) { }

Resource::Resource(Resource& r):posx(r.getPosx()), posy(r.getPosy()) { }

Resource::~Resource() { }

// GETTERS
float Resource::getPosx() {
	return posx;
}

float Resource::getPosy() {
	return posy;
}

// SETTERS
void Resource::setPosx(float posx) {
	this->posx = posx;
}

void Resource::setPosy(float posy) {
	this->posy = posy;
}

void Resource::setPos(float posx, float posy) {
	setPosx(posx);
	setPosy(posy);
}



