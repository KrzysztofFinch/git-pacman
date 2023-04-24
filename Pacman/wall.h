#pragma once
#include "entity.h"
class wall: public entity
{
public:
	int wallSize = 45;
	wall();
	void update();
};

