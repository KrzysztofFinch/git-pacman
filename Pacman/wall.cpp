#include "wall.h"

wall::wall() {
	rect.setSize(sf::Vector2f(wallSize, wallSize));
	rect.setFillColor(sf::Color::Blue);
	rect.setPosition(20, 20);
}

void wall::update()
{
	sprite.setPosition(rect.getPosition());
}
