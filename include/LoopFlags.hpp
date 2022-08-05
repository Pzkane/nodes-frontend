#ifndef SRC_HELPERS_LOOPFLAGS_HPP_INCLUDED
#define SRC_HELPERS_LOOPFLAGS_HPP_INCLUDED

#include "Flags.hpp"

namespace nf {

class LoopFlags : public Flags
{
public:
    bool f_t_ep_done = false;
    bool f_t_delete_active_scene = false;
    LoopFlags() : Flags() {}
    ~LoopFlags() = default;
    bool switchedOff();
};

};

#endif // SRC_HELPERS_LOOPFLAGS_HPP_INCLUDED
