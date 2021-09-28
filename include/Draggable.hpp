#ifndef SRC_PROPERTIES_DRAGGABLE_HPP_INCLUDED
#define SRC_PROPERTIES_DRAGGABLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

class Draggable : public sf::Transformable
{
    bool m_is_dragged = false;

public:
    Draggable() {}
    ~Draggable() = default;
    sf::Vector2f getMousePosf(const sf::RenderWindow &window);
    void drag();
    void checkMousePointer(const sf::RenderWindow &window);
};

#endif // SRC_PROPERTIES_DRAGGABLE_HPP_INCLUDED
