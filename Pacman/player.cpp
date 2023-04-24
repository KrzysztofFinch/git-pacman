#include "player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
player::player()
{
	rect.setSize(sf::Vector2f(40, 40));
	rect.setFillColor(sf::Color::Blue);
	rect.setPosition(920, 350);
	sprite.setTextureRect(sf::IntRect(850, 0, 40, 46));
}

void player::update(int timeADead, int timeC)
{
	sprite.setPosition(rect.getPosition());
	if ((canBeEaten == false) && (timeC - timeADead == 5)) {
		canBeEaten = true;
	}
}

void player::updateMovement()
{
	//1 - up, 2 - down, 3 - left, 4 - right 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (canMoveUp) {
			rect.move(0, -movementSpeed);
			sprite.setTextureRect(sf::IntRect(850, (counterWalking + 9) * 45.8, 40, 48));
			direction = 1;
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}	
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (canMoveDown) {
			rect.move(0, movementSpeed);
			if (counterWalking != 3) {
				sprite.setTextureRect(sf::IntRect(850, (counterWalking + 3) * 38.8, 40, 45));
			}
			else {
				sprite.setTextureRect(sf::IntRect(850, (counterWalking + 3) * 40.8, 40, 45));
			}
			direction = 2;
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (canMoveLeft)
		{
			rect.move(-movementSpeed, 0);
			if (counterWalking != 3) {
				sprite.setTextureRect(sf::IntRect(850, (counterWalking + 6) * 43.8, 40, 45));
			}
			else {
				sprite.setTextureRect(sf::IntRect(850, (counterWalking + 6) * 44.8, 40, 45));
			}
			direction = 3;
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (canMoveRight) {
			rect.move(movementSpeed, 0);
			if (counterWalking != 3) {
				sprite.setTextureRect(sf::IntRect(850, counterWalking * 49, 40, 45));
			}
			else {
				sprite.setTextureRect(sf::IntRect(850, counterWalking * 51, 40, 45));
			}
			direction = 4;
			canMoveUp = true;
			canMoveDown = true;
			canMoveLeft = true;
			canMoveRight = true;
		}		
	}

	//spowolnienie animacji ruchu
	if (counterWalking == slowAnimation) {
		counterWalking++;
		slowAnimation = -3;
	}
	else {
		slowAnimation++;
	}
	
	
	if (counterWalking == 4) {
		counterWalking = 1;
	} 
}

void player::dead()
{
	if (deadAnimation != 12) {
		sprite.setTextureRect(sf::IntRect(350, deadAnimation * 50, 50, 50));
		deadAnimation++;
	}
}
