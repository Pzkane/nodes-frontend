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

    sf::Vector2f mousepos = getMousePosf(window);

    if (getLMBState() && mouseInside(mousepos) && !m_successDrag)
    {
        sf::FloatRect bounds = getGlobalBounds();
        sf::Vector2f origin = getOrigin();
        sf::Vector2f gOrigin(bounds.left + origin.x, bounds.top + origin.y);
        m_offsetMousepos = sf::Vector2f(mousepos.x - gOrigin.x, mousepos.y - gOrigin.y);
        m_successDrag = true;
    }

    if (m_successDrag)
    {
        setPosition(sf::Vector2f(mousepos.x-m_offsetMousepos.x, mousepos.y-m_offsetMousepos.y));
    }
}
