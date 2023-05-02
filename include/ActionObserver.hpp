#ifndef SRC_SCENES_ACTIONOBSERVER_HPP_INCLUDED
#define SRC_SCENES_ACTIONOBSERVER_HPP_INCLUDED

#include <mutex>
#include "Action.hpp"

namespace nf {

/**
 * @brief Observe incoming entity actions and notify scene/other entities
 *  about changes. Perceive it as 'event handler' for scene on high level.
 * 
 * Singleton; cached resource.
*/
class ActionObserver {
protected:
    static ActionObserver* m_observer;
    static std::mutex m_observerMutex;

    Action *m_originAction = nullptr, *m_callbackAction = nullptr;

    void destroyOriginAction();
    void destroyCallbackAction();
    void destroy();
public:
    ActionObserver() = default;
    ~ActionObserver();

    ActionObserver(ActionObserver&) = delete;
    void operator=(const ActionObserver&) = delete;

    /**
     * Get ActionObserver instance
    */
    static ActionObserver* getInstance();

    /**
     * @brief Set starting action conditions (e.g. right click to spawn UI container)
     * (Re-)Initializes observer session and resource
    */
    void setOriginAction(Action *action);

    /**
     * @brief Set action callback (e.g. left click on node to confirm)
     * (Re-)Initializes resource
    */
    void setCallbackAction(Action *action);

    /**
     * Return last notified action conditions
    */
    const Action* getOriginAction() const;

    /**
     * Return action callback
    */
    const Action* getCallbackAction() const;

    /**
     * Execute action conditions
    */
    void performOriginAction();
    
    /**
     * Execute response action
    */
    void performCallbackAction();
};

}; // namespace nf

#endif // SRC_SCENES_ACTIONOBSERVER_HPP_INCLUDED
