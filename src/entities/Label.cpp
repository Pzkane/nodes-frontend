#include "Label.hpp"
#include "utils.hpp"
#include "Cache.hpp"

using namespace nf;

void Label::setPosition(const sf::Vector2f& pos) {
    auto bounds = sf::Text::getLocalBounds();
    m_box.setPosition(pos.x, pos.y+10);
    m_box.setSize({bounds.width+3, bounds.height+3});
    m_box.setFillColor(gBGColor);
    sf::Text::setPosition(pos);
}

void Label::setPosition(float x, float y) {
    setPosition({x, y});
}
