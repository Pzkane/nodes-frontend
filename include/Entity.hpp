#ifndef SRC_ENTITIES_ENTITY_HPP_INCLUDED
#define SRC_ENTITIES_ENTITY_HPP_INCLUDED

#include "EntityFlags.hpp"
#include "EventFlags.hpp"

namespace nf {

class Entity
{
public:
    EntityFlags enf;
    Entity() = default;
    ~Entity() = default;
    virtual void update(const sf::RenderWindow &window, EventFlags &ef) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

};

#endif // SRC_ENTITIES_ENTITY_HPP_INCLUDED
