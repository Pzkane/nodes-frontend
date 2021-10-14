#ifndef SRC_HELPERS_FLAGS_HPP_INCLUDED
#define SRC_HELPERS_FLAGS_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Flags
{
public:
    static sf::Font font;
    Flags();
    virtual ~Flags() = default;
    virtual bool switchedOff() { return false; }
};

#endif // SRC_HELPERS_FLAGS_HPP_INCLUDED
