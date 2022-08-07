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
        float posX = mousepos.x-m_offsetMousepos.x,
              posY = mousepos.y-m_offsetMousepos.y;
        setPosition(sf::Vector2f(posX > window.getSize().x ? window.getSize().x : posX < 0 ? 0 : posX,
                                 posY > window.getSize().y ? window.getSize().y : posY < 0 ? 0 : posY));
    }
}
