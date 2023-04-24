#include "ghost.h"
#include "random.h"



ghost::ghost()
{
	srand(time(NULL));
	rect.setFillColor(sf::Color::Blue);
	rect.setSize(sf::Vector2f(40, 40));
	//sprite.setTextureRect(sf::IntRect(-3, 0, 45, 45)); //45px x 45px ; -3px zeby byl idealnie na srodku rect

	
}

void ghost::update(sf::Time elapsed1)
{

	sprite.setPosition(rect.getPosition());
	if (!isScared) {
			sprite.setTextureRect(sf::IntRect((ghostColor * 49), 0, 45, 45)); //45px x 45px ; -3px zeby byl idealnie na srodku rect		
	}
	else {
		if (elapsed1.asSeconds() > 0.3) {
			sprite.setTextureRect(sf::IntRect(-3, 550, 45, 45));
		}
		else {
			sprite.setTextureRect(sf::IntRect(45, 550, 45, 45));
		}
		
	}
}

void ghost::updateMovement()
{
	//1 - up, 2 - down, 3 - left, 4 - right
	if (direction == 1) { 
		if (canMoveUp) {
			rect.move(0, -movementSpeed); //up
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (direction == 2) {
		if (canMoveDown) {
			rect.move(0, movementSpeed); //down
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}		
	}
	else if (direction == 3) {
		if (canMoveLeft) {
			rect.move(-movementSpeed, 0); // left
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}		
	}
	else if (direction == 4) {
		if (canMoveRight) {
			rect.move(movementSpeed, 0); // right
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}		
	}
	else {
		//no move
	}

	counter++;
	if (counter == movementLength) {
		direction = generateRandom(4);
		counter = 0;
	}

	
}

void ghost::generateGhostXY(int &x, int &y, float distance, int pX, int pY)
{
	float dx;
	float dy;
	while (distance < 100) {
		while (x < 45 || x > 1875) {
			x = generateRandom(1920);
		}
		while (y < 45 || y > 1035) {
			y = generateRandom(1080);
		}
		
		dx = x - pX;
		dy = y - pY;
		distance = sqrt(dx * dx + dy * dy);
	}
}

void ghost::setGhostColor()
{
	ghostColor = generateRandom(6) - 1;
}
