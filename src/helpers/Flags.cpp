#include "Flags.hpp"
#include "utils.hpp"

sf::Font Flags::font;

Flags::Flags()
{
    if (font.getInfo().family.empty() || font.getInfo().family == "\n")
    {
        say("Loading fonts");
        if (!font.loadFromFile("resources/Inconsolata-Medium.ttf"))
        {
            error("Could not load fonts");
        }
        else
        {
            say("FONTS: ");
            say(font.getInfo().family);
        }
    }
}
