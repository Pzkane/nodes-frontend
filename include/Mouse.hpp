#ifndef SRC_MOUSE_HPP_INCLUDED
#define SRC_MOUSE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "utils.hpp"

namespace nf {

/**
 * @brief Mouse which can hold (capture) 1 entity for two-way logic operations
 * 
 * Owner of this resource is MouseCache
*/
class Mouse : public sf::Mouse
{
    const sf::RenderWindow& m_window;
    Entity* m_capture;
public:
    explicit Mouse(const sf::RenderWindow &window, Entity* entity = nullptr)
        : m_window(window), m_capture(entity) {}
    /**
     * Remember pointer to entity
     * @param e Entity*
    */
    void captureEntity(Entity* e) { m_capture = e; }
    /**
     * Forget pointer to entity
    */
    void releaseEntity() { m_capture = nullptr; }
    /**
     * Retrieve active captured entity
    */
    const Entity* getEntity() { return m_capture; }
    bool isCaptureEmpty() { return !getEntity(); }
};

};

#endif // SRC_MOUSE_HPP_INCLUDED
