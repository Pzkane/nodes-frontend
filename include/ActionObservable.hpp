#ifndef SRC_SCENES_ACTIONOBSERVABLE_HPP_INCLUDED
#define SRC_SCENES_ACTIONOBSERVABLE_HPP_INCLUDED

#include "Action.hpp"
#include "Observable.hpp"

namespace nf {

/**
 * @brief Action for observable entities.
*/
class ActionObservable : public Action {
    Observable *m_entity;
public:
    explicit ActionObservable(Observable *entity) : m_entity(entity) {}

    /**
     * Perform observable's action
    */
    void execute() override;
};

}; // namespace nf

#endif // SRC_SCENES_ACTIONOBSERVABLE_HPP_INCLUDED
