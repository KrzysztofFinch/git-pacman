#include "textDisplay.h"

textDisplay::textDisplay()
{
    text.setFillColor(sf::Color::Yellow);
    text.setString(myString);
    text.setCharacterSize(30);
}

void textDisplay::update()
{
    text.move(0, -movementSpeed);

    counter++;
    if (counter >= lifetime) {
        destroy = true;
    }
}
