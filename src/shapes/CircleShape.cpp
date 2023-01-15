#include "cmath"
#include "CircleShape.hpp"

using namespace nf;

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

bool CircleShape::isLMBPressed()
{
    return m_event_flags.f_lmb;
}

void CircleShape::setOrigin(sf::Vector2f &origin)
{
    sf::CircleShape::setOrigin(origin);
}

sf::Vector2f CircleShape::getOrigin()
{
    return sf::CircleShape::getOrigin();
}

sf::FloatRect CircleShape::getGlobalBounds()
{
    return sf::CircleShape::getGlobalBounds();
}

sf::Vector2f CircleShape::getPosition() const
{
    return sf::CircleShape::getPosition();
}

void CircleShape::setCallback(VoidCallback callbackFnc)
{
    Clickable::setCallback(callbackFnc);
}
