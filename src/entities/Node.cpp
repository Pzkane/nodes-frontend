#include "Node.hpp"

Node::Node(float radius, std::size_t pointCount) : CircleShape(radius, pointCount)
{
    const sf::Vector2f center = CircleShape::getPosition();
    const float R = CircleShape::getRadius();
    sf::CircleShape::setOrigin(center.x + R, center.y + R);
}

void Node::update(const sf::RenderWindow &window, const EventFlags &ef)
{
    CircleShape::setEventFlags(ef);
    checkMousePointer(window);
}
