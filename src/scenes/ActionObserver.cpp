#include "ActionObserver.hpp"

using namespace nf;

ActionObserver* ActionObserver::m_observer = nullptr;
std::mutex ActionObserver::m_observerMutex;

ActionObserver* ActionObserver::getInstance() {
    std::unique_lock<std::mutex> ul(m_observerMutex);
    if(!m_observer)
        m_observer = new ActionObserver();
    return m_observer;
}