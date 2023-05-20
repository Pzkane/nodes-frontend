#ifndef SRC_ENTITIES_ENTITY_HPP_INCLUDED
#define SRC_ENTITIES_ENTITY_HPP_INCLUDED

#include "EntityFlags.hpp"
#include "EventFlags.hpp"

namespace nf {

/**
 * @brief Abstract class for entities to inherit from if used for rendering
 * 
 * Primarily consists of 2 methods:
 *  1. first handle events and update entity's state
 *  2. draw changes
*/
class Entity
{
public:
    EntityFlags enf;
    Entity() = default;
    virtual ~Entity() = default;
    /**
     * Update entity's state. Should be overriden
     * @param window RenderWindow in which given entity is being drawn
     * @param ef EntityFlags containing recent state based on input changes
    */
    virtual void update(const sf::RenderWindow &window, EventFlags &ef) = 0;
    /**
     * Draw entity on screen. Should be overriden
     * @param window RenderWindow in which given entity is being drawn
    */
    virtual void draw(sf::RenderWindow &window) = 0;
};

};

#endif // SRC_ENTITIES_ENTITY_HPP_INCLUDED
