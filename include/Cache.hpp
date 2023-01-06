#ifndef SRC_SHAPES_CACHE_HPP_INCLUDED
#define SRC_SHAPES_CACHE_HPP_INCLUDED

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace nf {

static const sf::Color gBGColor(210, 210, 210);

class Cache
{
    void _initCursors();
public:
    static std::vector<sf::Cursor*> m_cursors;
    enum CursorType
    { Arrow, Hand };

    Cache();
    ~Cache() = default;
};

extern Cache cache;

};

#endif // SRC_SHAPES_CACHE_HPP_INCLUDED
