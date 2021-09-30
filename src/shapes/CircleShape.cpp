#include "CircleShape.hpp"

#include "cmath"

void CircleShape::setPosition(const float x, const float y)
{
    sf::CircleShape::setPosition(x, y);
}

void CircleShape::setPosition(const sf::Vector2f &position)
{
    sf::CircleShape::setPosition(position);
}

bool CircleShape::mouseInside(const sf::Vector2f &position)
{
    return checkPosAgainstShape(position);
}

bool CircleShape::checkPosAgainstShape(const sf::Vector2f &position)
{
    sf::Vector2f center = sf::CircleShape::getPosition();
    if (sqrt(pow((position.x - center.x), 2) + pow(position.y - center.y, 2)) <= sf::CircleShape::getRadius())
        return true;
    return false;
}
