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
};

};

#endif // SRC_ENTITIES_ENTITY_HPP_INCLUDED
