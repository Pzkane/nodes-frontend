#include <thread>
#include "NodeFrontEndWrapper.hpp"

#define TITLE "Nodes Frontend"

using namespace nf;

static void launchWindow(NodeFrontEnd *api, const Context& settings, std::atomic<bool> &isDone)
{
    api->init();
    api->launch_and_loop();
    say("API is done");
    isDone = true;
}

void NodeFrontEndWrapper::init(const char* title) {
    m_terminated = false;
    m_done = false;
    m_api = new NodeFrontEnd(m_settings, title ? title : TITLE); // ptr to manage lifecycle
    m_nfLoop = new std::thread(launchWindow, std::ref(m_api), m_settings, std::ref(m_done));
    say("Waiting for init...");
    while (!m_api->isInit()) {}
}

NodeFrontEndWrapper::NodeFrontEndWrapper(const Context& settings) {
    m_settings = settings;
    init();
}

NodeFrontEndWrapper::NodeFrontEndWrapper()
{
    m_settings.m_videoMode.width = 1024;
    m_settings.m_videoMode.height = 768;
    m_settings.depthBits = 24;
    m_settings.stencilBits = 8;
    m_settings.antialiasingLevel = 8;
    m_settings.majorVersion = 3;
    m_settings.minorVersion = 0;
    init();
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
