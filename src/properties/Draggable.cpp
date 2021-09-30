#include "Draggable.hpp"

#include <iostream>

sf::Vector2f Draggable::getMousePosf(const sf::RenderWindow &window)
{
    return sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}

void Draggable::checkMousePointer(const sf::RenderWindow &window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseInside(getMousePosf(window)))
    {
        setPosition(getMousePosf(window));
    }
}
