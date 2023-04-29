#ifndef SRC_SCENES_ACTION_HPP_INCLUDED
#define SRC_SCENES_ACTION_HPP_INCLUDED

namespace nf {

/**
 * @brief Base class representing generic entity action.
 * Treat them as 'events' for scene handler (observer) on high level.
*/
class Action {
public:
    virtual ~Action() = default;

    /**
     * Perform observable's action
    */
    virtual void execute() = 0;
};

}; // namespace nf

#endif // SRC_SCENES_ACTION_HPP_INCLUDED
