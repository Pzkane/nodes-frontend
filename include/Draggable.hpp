#ifndef SRC_PROPERTIES_DRAGGABLE_HPP_INCLUDED
#define SRC_PROPERTIES_DRAGGABLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

namespace nf {

class Draggable
{
    bool m_successDrag = false,
         m_movable     = false;
    sf::Vector2f m_offsetMousePos;

public:
    Draggable() {}
    virtual ~Draggable() = default;
    void trackMousePointer(const sf::RenderWindow &window);
    bool getDragState() const { return m_successDrag && m_movable; }
    void setMovable(bool state) { m_movable = state; };
    bool isMoving() { return m_movable; };

    virtual void setPosition(const sf::Vector2f &position) = 0;
    virtual void setPosition(const float x, const float y) = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual bool mouseInside(const sf::Vector2f &position) = 0;
    virtual bool isLMBPressed() = 0;
    virtual void setOrigin(sf::Vector2f &origin) = 0;
    virtual sf::Vector2f getOrigin() = 0;
    virtual sf::FloatRect getGlobalBounds() = 0;
};

};

#endif // SRC_PROPERTIES_DRAGGABLE_HPP_INCLUDED
