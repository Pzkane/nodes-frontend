#include "Container.hpp"
#include "MouseCache.hpp"
#include "utils.hpp"

using namespace nf;

void Container::init() {
    static sf::Color uiBG {0, 0, 0, 75};
    sf::RectangleShape::setFillColor(uiBG);
    sf::RectangleShape::setOutlineColor(sf::Color::Black);
    sf::RectangleShape::setOutlineThickness(1.5);
}

Container::Container(const sf::Vector2f& size,
                     const sf::Vector2f& pos,
                     const sf::Vector2i& padding)
    : padding(padding), sf::RectangleShape(size) {
    setPosition(pos);
    init();
}

void Container::addChildElement(const Container& child) {
    m_children.push_back(child);
}

void Container::addChildElement(Container&& child) {
    m_children.push_back(std::move(child));
}

void Container::setVisibility(bool state) { m_visible = state; }

bool Container::isHidden() { return !m_visible; }

void Container::setPosition(const sf::Vector2f &position) {
    for (auto&& it : m_children) {
        auto it_pos = it.getPosition();
        it.setPosition({position.x + (it_pos.x - getPosition().x),
                        position.y + (it_pos.y - getPosition().y)});
    }
    sf::RectangleShape::setPosition(position);
}

void Container::setPosition(const float x, const float y) {
    setPosition({x, y});
}

sf::Vector2f Container::getPosition() const {
    return sf::RectangleShape::getPosition();
}

bool Container::mouseInside(const sf::Vector2f &position) {
    auto contBounds = sf::RectangleShape::getGlobalBounds();
    if (position.x >= contBounds.left && position.x <= contBounds.left + contBounds.width
     && position.y >= contBounds.top && position.y <= contBounds.top + contBounds.height) {
        return true;
    }
    return false;
}

bool Container::isLMBPressed() {
    return m_event_flags.f_lmb;
}

void Container::setOrigin(sf::Vector2f &origin) {
    sf::RectangleShape::setOrigin(origin);
}

sf::Vector2f Container::getOrigin() {
    return sf::RectangleShape::getOrigin();
}

sf::FloatRect Container::getGlobalBounds() {
    return sf::RectangleShape::getGlobalBounds();
}

void Container::update(const sf::RenderWindow &window, EventFlags &ef) {
    setEventFlags(ef);
    trackMousePointer(window);

    if (mouseInside(Utils::getMousePosf(window))) {
        Mouse& m = MouseCache::getInstance(window)->gMouse;
        if (ef.f_lmb) {
            if (m.isCaptureEmpty())
                m.captureEntity(this);
        } else {
            if (m.getEntity() == this)
                m.releaseEntity();
        }
    }
}
