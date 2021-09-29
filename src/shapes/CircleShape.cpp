#include "CircleShape.hpp"

void CircleShape::setPosition(float x, float y)
{
    sf::CircleShape::setPosition(x, y);
}

void CircleShape::setPosition(const sf::Vector2f& position)
{
    sf::CircleShape::setPosition(position);
}

sf::Vector2f CircleShape::getPosition()
{
    return sf::CircleShape::getPosition();
}
