#ifndef SRC_HELPERS_FLAGS_HPP_INCLUDED
#define SRC_HELPERS_FLAGS_HPP_INCLUDED

class Flags
{
public:
    Flags() {}
    virtual ~Flags() = default;
    virtual bool switchedOff() { return false; }
};

#endif // SRC_HELPERS_FLAGS_HPP_INCLUDED
