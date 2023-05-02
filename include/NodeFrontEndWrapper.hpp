#ifndef SRC_API_APIWRAPPER_HPP_INCLUDED
#define SRC_API_APIWRAPPER_HPP_INCLUDED

#include <atomic>

#include "NodeFrontEnd.hpp"
#include "LinkedListNode.hpp"
#include "DoubleLinkedListNode.hpp"
#include "BinaryTreeNode.hpp"

// Main API loop; WRAPPER should be defined in driver
#define START_LOOP while (!WRAPPER.isDone()) {} WRAPPER.destroy(); say("DRIVER OUT");

namespace nf {

/**
 * User-friendly wrapper around API dispatcher
*/
class NodeFrontEndWrapper
{
    bool m_terminated;
    std::atomic<bool> m_done;
    std::thread *m_nfLoop;
    nf::NodeFrontEnd* m_api;
    Context m_settings;
    void init(const char* title = nullptr);
public:
    explicit NodeFrontEndWrapper(const Context& settings);
    NodeFrontEndWrapper();
    void destroy();
    nf::NodeFrontEnd* api();
    bool isDone() { return m_done; }
    bool isTerminated() { return m_terminated; }
};

};

// extern nf::NodeFrontEndWrapper NFWrap;

#endif // SRC_API_APIWRAPPER_HPP_INCLUDED
