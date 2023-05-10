#include "ActionObserver.hpp"
#include "utils.hpp"

using namespace nf;

ActionObserver* ActionObserver::m_observer = nullptr;
std::mutex ActionObserver::m_observerMutex;

ActionObserver* ActionObserver::getInstance() {
    std::unique_lock<std::mutex> ul(m_observerMutex);
    if(!m_observer)
        m_observer = new ActionObserver();
    return m_observer;
}

ActionObserver::~ActionObserver() {
    destroy();
}

void ActionObserver::setOriginAction(Action *action) {
    destroyOriginAction();
    m_originAction = action;
}

void ActionObserver::setCallbackParameter(void* param) {
    m_callbackParameter = param;
}

void* ActionObserver::getCallbackParameter() {
    void* tmp = m_callbackParameter;
    m_callbackParameter = nullptr;
    return tmp;
}

void ActionObserver::performOriginAction() {
    say("Perform origin action")
    m_originAction->execute();
}

void ActionObserver::destroyOriginAction() {
    if (m_originAction)
        delete m_originAction;
}

void ActionObserver::destroy() {
    destroyOriginAction();
    if (m_observer)
        delete m_observer;
}
