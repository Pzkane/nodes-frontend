#ifndef SRC_HELPERS_FLAGS_HPP_INCLUDED
#define SRC_HELPERS_FLAGS_HPP_INCLUDED

namespace nf {

class Flags
{
public:
    enum class Type { Event };
    Flags() {}
    virtual ~Flags() = default;
    virtual bool switchedOff() { return false; }
};

};

#endif // SRC_HELPERS_FLAGS_HPP_INCLUDED
