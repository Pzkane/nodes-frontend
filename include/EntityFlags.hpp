#ifndef SRC_HELPERS_ENTITYFLAGS_HPP_INCLUDED
#define SRC_HELPERS_ENTITYFLAGS_HPP_INCLUDED

#include "Flags.hpp"

namespace nf {

/**
 * @brief Generic flags for Entity objects
*/
class EntityFlags : public Flags
{
public:
    /// @brief This flag is used to signal owner of the resource to destroy
    ///         current object
    bool f_delete_self = false;
    EntityFlags() : Flags() {}
    ~EntityFlags() = default;
};

};

#endif // SRC_HELPERS_ENTITYFLAGS_HPP_INCLUDED
