#ifndef SRC_HELPERS_LOOPFLAGS_HPP_INCLUDED
#define SRC_HELPERS_LOOPFLAGS_HPP_INCLUDED

#include "Flags.hpp"

namespace nf {

/**
 * @brief Flags for main drawing/updating loop
*/
class LoopFlags : public Flags
{
public:
    /// @brief This flags determines whenever event pool thread is done
    bool f_t_ep_done = false;
    bool f_t_delete_active_scene = false;
    LoopFlags() : Flags() {}
    ~LoopFlags() = default;
    bool switchedOff();
};

static LoopFlags lf;

};

#endif // SRC_HELPERS_LOOPFLAGS_HPP_INCLUDED
