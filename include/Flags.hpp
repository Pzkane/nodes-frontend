#ifndef SRC_HELPERS_FLAGS_HPP_INCLUDED
#define SRC_HELPERS_FLAGS_HPP_INCLUDED

class Flags
{
public:
    Flags() {}
    ~Flags() = default;
    virtual bool switchedOff() = 0;
};

#endif // SRC_HELPERS_FLAGS_HPP_INCLUDED
