#ifndef SRC_HELPERS_EVENTFLAGS_HPP_INCLUDED
#define SRC_HELPERS_EVENTFLAGS_HPP_INCLUDED

#include "Flags.hpp"

class EventFlags : public Flags
{
public:
    bool f_lmb = false;
    EventFlags() : Flags() {}
    ~EventFlags() = default;
};

#endif // SRC_HELPERS_EVENTFLAGS_HPP_INCLUDED
