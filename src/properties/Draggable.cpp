#include "Draggable.hpp"
#include "utils.hpp"

void Draggable::checkMousePointer(const sf::RenderWindow &window)
{
    if (!getLMBState())
    {
        m_successDrag = false;
        return;
    }

    sf::Vector2f mousepos = Utils::getMousePosf(window);

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
