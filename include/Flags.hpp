#ifndef SRC_HELPERS_FLAGS_HPP_INCLUDED
#define SRC_HELPERS_FLAGS_HPP_INCLUDED

namespace nf {

/**
 * @brief Generic flag class
*/
class Flags
{
public:
    enum class Type { Event };
    Flags() {}
    virtual ~Flags() = default;
    /**
     * Check some property, should be overridden
    */
    virtual bool switchedOff() { return false; }
};

};

#endif // SRC_HELPERS_FLAGS_HPP_INCLUDED
