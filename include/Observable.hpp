#ifndef SRC_PROPERTIES_OBSERVABLE_HPP_INCLUDED
#define SRC_PROPERTIES_OBSERVABLE_HPP_INCLUDED

namespace nf {

/**
 * @brief Observable is a generic object to create 2-way reference between internal
 *          implementation and high-level node accessed through API. This means that
 *          observable will be a user-defined type
*/
class Observable {
public:
    virtual ~Observable() = default;

    /**
     * Set this object as callback parameter
    */
    virtual void registerEntity() = 0;
    /**
     * Activate observable
    */
    virtual void invoke() = 0;
};

}; // namespace nf

#endif // SRC_PROPERTIES_OBSERVABLE_HPP_INCLUDED
