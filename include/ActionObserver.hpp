#ifndef SRC_SCENES_ACTIONOBSERVER_HPP_INCLUDED
#define SRC_SCENES_ACTIONOBSERVER_HPP_INCLUDED

#include <mutex>

namespace nf {

/**
 * @brief Observe incoming entity actions and notify scene/other entities
 *  about changes.
 * 
 * Singleton; cached resource.
*/
class ActionObserver {
protected:
    static ActionObserver* m_observer;
    static std::mutex m_observerMutex;
public:
    ActionObserver() {}
    ~ActionObserver() = default;

    ActionObserver(ActionObserver&) = delete;
    void operator=(const ActionObserver&) = delete;
    static ActionObserver* getInstance();
};

}; // namespace nf

#endif // SRC_SCENES_ACTIONOBSERVER_HPP_INCLUDED
