#pragma once
#include "entity.h"
class ghost: public entity
{
public:
	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;
	bool isScared = false;
	int ghostColor;
	int movementSpeed = 0;
	int direction = 0;//1 - up, 2 - down, 3 - left, 4 - right
	int counter = 0;
	int counterWalking = 0;
	int movementLength = 100;


	ghost();
	void update(sf::Time elapsed1);
	void updateMovement();
	void generateGhostXY(int& x, int& y, float distance, int pX, int pY);
	void setGhostColor();
};

