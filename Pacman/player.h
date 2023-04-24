#pragma once
#include "entity.h"
class player: public entity
{
public:
	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;
	bool canEatGhosts = false;
	bool canBeEaten = true;
	int movementSpeed = 5;
	int counterWalking = 1;
	int slowAnimation = 0;
	int direction = 0; //1 - up, 2 - down, 3 - left, 4 - right 
	int coins = 0;
	bool alive = true;
	int deadAnimation = 0;
	int lifes = 3;
	int gameTime = 0;

	player();
	void update(int timeADead, int timeC);
	void updateMovement();
	void dead();
};

