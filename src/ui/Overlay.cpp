#include "Overlay.hpp"
#include "MouseCache.hpp"

using namespace nf;

void Overlay::createWrapper(const Container& container){
    if (m_wrapper) return;
    m_wrapper = new Container(container);
}

void Overlay::destroyWrapper() {
    delete m_wrapper;
}

Overlay::Overlay() {}

Overlay::Overlay(const Container& wrapper) {
    createWrapper(wrapper);
}

Overlay::~Overlay() {
    destroyWrapper();
}

void Overlay::copy(const Overlay& o) {
    if (m_wrapper)
        delete m_wrapper;
    m_wrapper = o.m_wrapper;
    m_visible = o.m_visible;
}

void Overlay::move(Overlay&& o) {
    if (m_wrapper)
        delete m_wrapper;
    m_wrapper = o.m_wrapper;
    o.m_wrapper = nullptr;
    m_visible = o.m_visible;
}

Overlay::Overlay(const Overlay& o) {
    copy(o);
}

Overlay& Overlay::operator=(const Overlay& o) {
    copy(o);
    return *this;
}

Overlay::Overlay(Overlay&& o) {
    move(std::move(o));
}

Overlay& Overlay::operator=(Overlay&& o) {
    move(std::move(o));
    return *this;
}


void Overlay::addContainer(Container&& container) {
    struct Wrapper_Not_Created{};
    if (m_wrapper == nullptr) throw Wrapper_Not_Created{};
    m_wrapper->addChildElement(std::move(container));
}

void Overlay::addContainer(const Container& container) {
    addContainer(std::move(container));
}

void Overlay::update(sf::RenderWindow& window, const EventFlags& ef, bool resized) {
    Mouse& m = MouseCache::getInstance(window)->gMouse;
    
    if (resized) {
        auto viewport = window.getViewport(window.getView());
        auto wrap_pos = m_wrapper->getPosition();
        auto wrap_bounds = m_wrapper->getGlobalBounds();
        m_wrapper->setPosition(viewport.left + viewport.width - wrap_bounds.width - m_wrapper->padding.x,
                               viewport.top + m_wrapper->padding.y);
    } else {
        m_wrapper->update(window, const_cast<EventFlags&>(ef));
        if (m.getEntity() == m_wrapper)
            m_wrapper->setMovable(true);
        else
            m_wrapper->setMovable(false);
    }
}

void Overlay::draw(sf::RenderWindow& window) {
    window.draw(*m_wrapper);
    for (auto && it : m_wrapper->m_children) {
        window.draw(it);
    }
}
