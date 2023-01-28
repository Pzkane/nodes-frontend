#include <thread>
#include "NodeFrontEndWrapper.hpp"

using namespace nf;

static void launchWindow(NodeFrontEnd *api, std::atomic<bool> &isDone)
{
    api->init();
    api->launch_and_loop();
    say("It is done");
    isDone = true;
}

NodeFrontEndWrapper::NodeFrontEndWrapper()
{
    m_terminated = false;
    m_done = false;
    m_api = new NodeFrontEnd(); // ptr to manage lifecycle
    m_nfLoop = new std::thread(launchWindow, std::ref(m_api), std::ref(m_done));
    say("Waiting for init...");
    while (!m_api->isInit()) {}
}

void NodeFrontEndWrapper::destroy()
{
    say("Waiting for graphics to end...");
    while (!m_done) {}
    say("Joining API thread...");
    m_nfLoop->join();
    say("API thread joined");
    delete m_api;
    m_terminated = true;
    delete m_nfLoop;
    m_nfLoop = nullptr;
}

nf::NodeFrontEnd* NodeFrontEndWrapper::api()
{
    return m_api;
}
