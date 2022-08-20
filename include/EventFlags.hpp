#ifndef SRC_HELPERS_EVENTFLAGS_HPP_INCLUDED
#define SRC_HELPERS_EVENTFLAGS_HPP_INCLUDED

#include "Flags.hpp"

namespace nf {

/* Forward declaration */
class _Node;

class EventFlags : public Flags
{
public:
    bool f_lmb = false;
    bool f_mmb = false;
    bool f_rmb = false;
    bool f_lalt = false;
    bool f_ralt = false;
    _Node *p_start_node = nullptr;
    _Node *p_end_node = nullptr;
    EventFlags() : Flags() {}
    ~EventFlags() = default;
};

};

#endif // SRC_HELPERS_EVENTFLAGS_HPP_INCLUDED
