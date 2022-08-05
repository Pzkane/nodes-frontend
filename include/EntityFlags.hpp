#ifndef SRC_HELPERS_ENTITYFLAGS_HPP_INCLUDED
#define SRC_HELPERS_ENTITYFLAGS_HPP_INCLUDED

#include "Flags.hpp"

namespace nf {

class EntityFlags : public Flags
{
public:
    bool f_delete_self = false;
    EntityFlags() : Flags() {}
    ~EntityFlags() = default;
};

};

#endif // SRC_HELPERS_ENTITYFLAGS_HPP_INCLUDED
