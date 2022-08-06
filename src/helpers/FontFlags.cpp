#include "FontFlags.hpp"
#include "utils.hpp"

using namespace nf;

sf::Font FontFlags::font;

FontFlags::FontFlags() : Flags()
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
