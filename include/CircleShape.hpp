#ifndef SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED
#define SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Draggable.hpp"
#include "Clickable.hpp"
#include "EventFlags.hpp"

class CircleShape : public sf::CircleShape, public Draggable, public Clickable<void*>
{
    bool m_is_dragged = false;
    EventFlags m_event_flags;

public:
    explicit CircleShape(const float radius = 0, const std::size_t pointCount = 30, size_t ms = 50)
        : sf::CircleShape(radius, pointCount), Clickable(ms) {}
    ~CircleShape() = default;
    void setPosition(const float x, const float y);
    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getPosition();
    bool checkPosAgainstShape(const sf::Vector2f &position);
    bool mouseInside(const sf::Vector2f &position);
    void setEventFlags(const EventFlags &ef);
    bool getLMBState();
    void setOrigin(sf::Vector2f &origin);
    void setCallback(VoidCallback callbackFnc);
    sf::Vector2f getOrigin();
    sf::FloatRect getGlobalBounds();
};

#endif // SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED
