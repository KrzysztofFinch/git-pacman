#pragma once
#include "entity.h"
class pickup: public entity
{
public:
	int coinValue = 1;
	int cherryValue = 100;
	bool isCoin = true;
	bool destroy = false;
	bool isCherry = false;
	pickup();
	void update();
	void setCherryTexture();
};

