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

void ActionObserver::setOriginAction(Action *action) {
    if (m_originAction)
        delete m_originAction;
    m_originAction = action;
}

void ActionObserver::setCallbackAction(Action *action) {
    if (m_callbackAction)
        delete m_callbackAction;
    m_callbackAction = action;
}

const Action* ActionObserver::getOriginAction() const {
    return m_originAction;
}

const Action* ActionObserver::getCallbackAction() const {
    return m_callbackAction;
}

void ActionObserver::performOriginAction() {
    say("Perform origin action")
    m_originAction->execute();
}

void ActionObserver::performCallbackAction() {
    m_callbackAction->execute();
}
