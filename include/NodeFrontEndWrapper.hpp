#ifndef SRC_API_APIWRAPPER_HPP_INCLUDED
#define SRC_API_APIWRAPPER_HPP_INCLUDED

#include <atomic>

#include "NodeFrontEnd.hpp"
#include "LinkedListNode.hpp"

namespace nf {

class NodeFrontEndWrapper
{
    bool m_terminated;
    std::atomic<bool> m_done;
    std::thread *m_nfLoop;
    nf::NodeFrontEnd* m_api;
public:
    NodeFrontEndWrapper();
    void destroy();
    nf::NodeFrontEnd* api();
    bool isDone() { return m_done; }
    bool isTerminated() { return m_terminated; }
};

};

// extern nf::NodeFrontEndWrapper NFWrap;

#endif // SRC_API_APIWRAPPER_HPP_INCLUDED
