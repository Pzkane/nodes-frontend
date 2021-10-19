#ifndef SRC_HELPERS_ENTITYFLAGS_HPP_INCLUDED
#define SRC_HELPERS_ENTITYFLAGS_HPP_INCLUDED

#include "Flags.hpp"

class EntityFlags : public Flags
{
public:
    bool f_del = false;
    EntityFlags() : Flags() {}
    ~EntityFlags() = default;
};

#endif // SRC_HELPERS_ENTITYFLAGS_HPP_INCLUDED
