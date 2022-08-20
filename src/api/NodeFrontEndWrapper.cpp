#include <thread>
#include "NodeFrontEndWrapper.hpp"

using namespace nf;

static void launchWindow(NodeFrontEnd &api, std::atomic<bool> &isDone)
{
    api.init();
    api.launch();
    isDone = true;
}

NodeFrontEndWrapper::NodeFrontEndWrapper()
{
    m_done = false;
    m_nfLoop = new std::thread(launchWindow, std::ref(m_api), std::ref(m_done));
    while (!m_api.isInit()) {}
}

NodeFrontEndWrapper::~NodeFrontEndWrapper()
{
    while (!m_done) {};
    m_nfLoop->join();
    delete m_nfLoop;
}

NodeFrontEndWrapper gApiWrap{};
