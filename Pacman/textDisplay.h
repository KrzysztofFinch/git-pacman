#pragma once
#include "entity.h"

class textDisplay: public entity
{
public:
	string myString = "default";
	float movementSpeed = 1.5;
	int counter = 0;
	int lifetime = 30;
	bool destroy = false;

	textDisplay();
	void update();
};

