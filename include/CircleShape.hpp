#ifndef SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED
#define SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Draggable.hpp"
#include "EventFlags.hpp"

class CircleShape : public sf::CircleShape, public Draggable
{
    bool m_is_dragged = false;
    EventFlags m_event_flags;

public:
    explicit CircleShape(const float radius = 0, const std::size_t pointCount = 30) : sf::CircleShape(radius, pointCount) {}
    ~CircleShape() = default;
    void setPosition(const float x, const float y);
    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getPosition();
    bool checkPosAgainstShape(const sf::Vector2f &position);
    bool mouseInside(const sf::Vector2f &position);
    void setEventFlags(const EventFlags &ef);
    bool getLMBState();
    void setOrigin(sf::Vector2f &origin);
    sf::Vector2f getOrigin();
    sf::FloatRect getGlobalBounds();
};

#endif // SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED