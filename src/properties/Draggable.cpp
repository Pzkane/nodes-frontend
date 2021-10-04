#include "Draggable.hpp"

sf::Vector2f Draggable::getMousePosf(const sf::RenderWindow &window)
{
    return sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}

void Draggable::checkMousePointer(const sf::RenderWindow &window)
{
    if (!getLMBState())
    {
        m_successDrag = false;
        return;
    }

    if (getLMBState() && mouseInside(getMousePosf(window)) || m_successDrag)
        m_successDrag = true;

    if (m_successDrag)
    {
        setPosition(getMousePosf(window));
    }
}
