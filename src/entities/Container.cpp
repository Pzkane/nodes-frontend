#include "Container.hpp"
#include "MouseCache.hpp"
#include "FontFlags.hpp"
#include "utils.hpp"

using namespace nf;

int Container::ID = 0;

void Container::init() {
    static sf::Color uiBG {0, 0, 0, 45};
    sf::RectangleShape::setFillColor(uiBG);
    sf::RectangleShape::setOutlineColor(sf::Color::Black);
    sf::RectangleShape::setOutlineThickness(1.5);
    m_id = ID++;
}

Container::Container(const sf::Vector2f& size,
                     const sf::Vector2f& pos,
                     const sf::Vector2i& padding)
    : padding(padding), sf::RectangleShape(size) {
    setPosition(pos);
    init();
}

Container::Container(const std::string& text,
                     const std::function<void*(void*)> callback,
                     const sf::Vector2f& size,
                     const sf::Vector2f& pos,
                     const sf::Vector2i& padding)
    : Container(size, pos, padding) {
    m_label.setFont(ff.font);
    m_label.setString(text);
    m_label.setScale(1, 1);
    m_label.setFillColor(sf::Color::Black);
    m_callback = callback;
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

    const float PADDING = 0.3f;
    m_label.setPosition(getPosition());
    // Diameter
    const float D = getLocalBounds().width;
    const sf::FloatRect l_bounds = m_label.getLocalBounds();
    // Scale text size and position to fit into node
    const sf::Vector2f sizeScale(l_bounds.width / D + PADDING, l_bounds.height / D + PADDING);
    const float maxScale = std::max(sizeScale.x, sizeScale.y);
    if (maxScale > 1)
        m_label.setScale(1 / maxScale, 1 / maxScale);
    else
    {
        m_label.setOrigin(sf::Vector2f(m_label.getLocalBounds().width / 2, m_label.getLocalBounds().height * 1.4));
        m_label.setScale(1, 1);
    }

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

    for (auto && it : this->m_children) {
        it.update(window, ef);
    }
}

void Container::draw(sf::RenderWindow &window) {
    window.draw(*this);
    window.draw(m_label);
    for (auto && it : this->m_children) {
        it.draw(window);
    }
}
