#ifndef SRC_ENTITIES_ENTITY_HPP_INCLUDED
#define SRC_ENTITIES_ENTITY_HPP_INCLUDED

#include "EntityFlags.hpp"

namespace nf {

class Entity
{
public:
    EntityFlags enf;
    explicit Entity() {};
    ~Entity() = default;
    virtual void update(const sf::RenderWindow &window, EventFlags &ev) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

};

#endif // SRC_ENTITIES_ENTITY_HPP_INCLUDED
