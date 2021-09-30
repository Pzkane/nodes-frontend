#ifndef SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED
#define SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Draggable.hpp"

class CircleShape : public sf::CircleShape, public Draggable
{
    bool m_is_dragged = false;

public:
    explicit CircleShape(const float radius = 0, const std::size_t pointCount = 30) : sf::CircleShape(radius, pointCount) {}
    ~CircleShape() = default;
    void setPosition(const float x, const float y);
    void setPosition(const sf::Vector2f &position);
    bool checkPosAgainstShape(const sf::Vector2f &position);
    bool mouseInside(const sf::Vector2f &position);
};

#endif // SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED
