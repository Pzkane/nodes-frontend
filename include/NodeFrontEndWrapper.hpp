#ifndef SRC_API_APIWRAPPER_HPP_INCLUDED
#define SRC_API_APIWRAPPER_HPP_INCLUDED

#include <atomic>

#include "NodeFrontEnd.hpp"

namespace nf {

class NodeFrontEndWrapper
{
    std::atomic<bool> m_done;
    std::thread *m_nfLoop;
public:
    nf::NodeFrontEnd m_api;
    NodeFrontEndWrapper();
    ~NodeFrontEndWrapper();
};

};

#endif // SRC_API_APIWRAPPER_HPP_INCLUDED
