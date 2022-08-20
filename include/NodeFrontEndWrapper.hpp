#ifndef SRC_API_APIWRAPPER_HPP_INCLUDED
#define SRC_API_APIWRAPPER_HPP_INCLUDED

#include <atomic>

#include "NodeFrontEnd.hpp"
#include "Node.hpp"

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

extern NodeFrontEndWrapper gApiWrap;

};

#endif // SRC_API_APIWRAPPER_HPP_INCLUDED
