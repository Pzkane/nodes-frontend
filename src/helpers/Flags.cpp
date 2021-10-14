#include "Flags.hpp"
#include "utils.hpp"

sf::Font Flags::font;

Flags::Flags()
{
    say(font.getInfo().family);
    if (font.getInfo().family.empty() || font.getInfo().family == "\n")
    {
        say("Loading fonts");
        if (!font.loadFromFile("./arial.ttf"))
            error("Could not load fonts");
    }
}
