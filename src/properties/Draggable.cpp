#include "Draggable.hpp"

#include <iostream>

sf::Vector2f Draggable::getMousePosf(const sf::RenderWindow &window)
{
    return sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}

void Draggable::drag()
{
    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getPosition() == getMousePosf())
    // {
    //     setPosition(getMousePosf());
    // }
}

void Draggable::checkMousePointer(const sf::RenderWindow &window)
{
    std::cout << getMousePosf(window).x << ":" << getMousePosf(window).y << std::endl;
    std::cout << getPosition().x << ":" << getPosition().y << std::endl;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getPosition() == getMousePosf(window))
    {
        setPosition(getMousePosf(window));
    }
}
