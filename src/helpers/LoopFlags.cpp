#include "LoopFlags.hpp"

bool LoopFlags::switchedOff()
{
    return f_t_ep_done && !f_t_delete_active_scene;
}
