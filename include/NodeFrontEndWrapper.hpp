#ifndef SRC_API_APIWRAPPER_HPP_INCLUDED
#define SRC_API_APIWRAPPER_HPP_INCLUDED

#include <atomic>

#include "NodeFrontEnd.hpp"

// Main API loop; WRAPPER should be defined in driver
#define START_LOOP while (!WRAPPER.isDone()) {} WRAPPER.destroy(); say("DRIVER OUT");

namespace nf {

/**
 * @brief User-friendly wrapper around API dispatcher
 * 
 * This class is used to easily determine and manage API class lifecycle
*/
class NodeFrontEndWrapper
{
    bool m_terminated, m_initialized = false;
    std::atomic<bool> m_done;
    std::thread *m_nfLoop;
    nf::NodeFrontEnd* m_api;
    Context m_settings;
public:
    /**
     * @brief Force-init API wrapper
     * Used in some instances where linked could not instantiate wrapper object
     *  in global scope
    */
    void init(const std::string& title = "");
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
