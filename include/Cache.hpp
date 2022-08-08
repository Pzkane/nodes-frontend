#ifndef SRC_SHAPES_CACHE_HPP_INCLUDED
#define SRC_SHAPES_CACHE_HPP_INCLUDED

#include <vector>
#include <SFML/Window.hpp>

namespace nf {

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
