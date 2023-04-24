#include "pickup.h"

pickup::pickup() 
{
	srand(time(NULL));
	rect.setSize(sf::Vector2f(15,15));
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(300, 300);
	
}

void pickup::update()
{
	sprite.setPosition(rect.getPosition());
}

void pickup::setCherryTexture()
{
	if (isCherry) {
		rect.setSize(sf::Vector2f(20, 20));
		rect.setFillColor(sf::Color::Magenta);
		sprite.setTextureRect(sf::IntRect(0, 0, 20, 20));
	}
}

