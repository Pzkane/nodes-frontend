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
    void *m_callbackParameter = nullptr, *m_originParameter = nullptr;

    void destroyOriginAction();
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
     * Set callback parameter to be returned
    */
    void setCallbackParameter(void* param);

    /**
     * Return specified callback parameter
    */
    void* getCallbackParameter();

    /**
     * Execute action conditions
    */
    void performOriginAction();
};

}; // namespace nf

#endif // SRC_SCENES_ACTIONOBSERVER_HPP_INCLUDED
