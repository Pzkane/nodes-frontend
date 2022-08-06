#ifndef SRC_HELPERS_FONTFLAGS_HPP_INCLUDED
#define SRC_HELPERS_FONTFLAGS_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "Flags.hpp"

namespace nf {

class FontFlags : public Flags
{
public:
    static sf::Font font;
    FontFlags();
    ~FontFlags() = default;
};

extern FontFlags ff;

};

#endif // SRC_HELPERS_FONTFLAGS_HPP_INCLUDED
