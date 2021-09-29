#ifndef SRC_PROPERTIES_DRAGGABLE_HPP_INCLUDED
#define SRC_PROPERTIES_DRAGGABLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

class Draggable
{
    bool m_is_dragged = false;

public:
    Draggable() {}
    virtual ~Draggable() = default;
    sf::Vector2f getMousePosf(const sf::RenderWindow &window);
    void drag();
    void checkMousePointer(const sf::RenderWindow &window);
    virtual void setPosition(float x, float y) = 0;
    virtual void setPosition(const sf::Vector2f& position) = 0;
    virtual sf::Vector2f getPosition() = 0;
};

#endif // SRC_PROPERTIES_DRAGGABLE_HPP_INCLUDED
