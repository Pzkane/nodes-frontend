#ifndef SRC_MOUSE_HPP_INCLUDED
#define SRC_MOUSE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "utils.hpp"

namespace nf {

class Mouse : public sf::Mouse
{
    const sf::RenderWindow& m_window;
    Entity* m_capture;
public:
    explicit Mouse(const sf::RenderWindow &window, Entity* entity = nullptr)
        : m_window(window), m_capture(entity) {}
    void captureEntity(Entity* e) { m_capture = e; }
    void releaseEntity() { m_capture = nullptr; }
    const Entity* getEntity() { return m_capture; }
    bool isCaptureEmpty() { return !getEntity(); }
};

};

#endif // SRC_MOUSE_HPP_INCLUDED
