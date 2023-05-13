#ifndef SRC_PROPERTIES_OBSERVABLE_HPP_INCLUDED
#define SRC_PROPERTIES_OBSERVABLE_HPP_INCLUDED

namespace nf {

/**
 * @brief React to observable object by ActionObserver
*/
class Observable {
public:
    virtual ~Observable() = default;

    /**
     * Set this as callback parameter
    */
    virtual void registerEntity() = 0;
    /**
     * Activate observable
    */
    virtual void invoke() = 0;
};

}; // namespace nf

#endif // SRC_PROPERTIES_OBSERVABLE_HPP_INCLUDED
