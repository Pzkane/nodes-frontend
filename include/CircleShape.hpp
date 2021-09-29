#ifndef SRC_PROPERTIES_CIRCLESHAPE_HPP_INCLUDED
#define SRC_PROPERTIES_CIRCLESHAPE_HPP_INCLUDED

#include "Draggable.hpp"

class CircleShape : public sf::CircleShape, public Draggable
{
    bool m_is_dragged = false;

public:
    explicit CircleShape(float radius = 0, std::size_t pointCount = 30) : sf::CircleShape(radius, pointCount) {}
    ~CircleShape() = default;
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition();
};

#endif // SRC_PROPERTIES_CIRCLESHAPE_HPP_INCLUDED
