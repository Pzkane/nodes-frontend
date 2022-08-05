#include "Draggable.hpp"
#include "utils.hpp"

using namespace nf;

void Draggable::trackMousePointer(const sf::RenderWindow &window)
{
    if (!m_movable || (m_movable && !isLMBPressed()))
    {
        m_successDrag = false;
        return;
    }

    sf::Vector2f mousepos = Utils::getMousePosf(window);

    if (isLMBPressed() && mouseInside(mousepos) && !m_successDrag)
    {
        sf::FloatRect bounds = getGlobalBounds();
        sf::Vector2f origin = getOrigin();
        sf::Vector2f gOrigin(bounds.left + origin.x, bounds.top + origin.y);
        m_offsetMousepos = sf::Vector2f(mousepos.x - gOrigin.x, mousepos.y - gOrigin.y);
        m_successDrag = true;
    }

    if (m_movable && m_successDrag)
    {
        setPosition(sf::Vector2f(mousepos.x-m_offsetMousepos.x, mousepos.y-m_offsetMousepos.y));
    }
}
