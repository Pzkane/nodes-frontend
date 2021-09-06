#ifndef SRC_HELPERS_LOOPFLAGS_HPP_INCLUDED
#define SRC_HELPERS_LOOPFLAGS_HPP_INCLUDED

#include "Flags.hpp"

class LoopFlags : Flags
{
public:
    bool f_t_ep_done = false;
    LoopFlags() : Flags() {}
    ~LoopFlags() = default;
    bool switchedOff();
};

#endif // SRC_HELPERS_LOOPFLAGS_HPP_INCLUDED
