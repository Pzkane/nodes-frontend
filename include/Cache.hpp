#ifndef SRC_SHAPES_CACHE_HPP_INCLUDED
#define SRC_SHAPES_CACHE_HPP_INCLUDED

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace nf {

static const sf::Color gBGColor(210, 210, 210);

/**
 * @brief Manages lifetime of singletons
 * 
 * Manages:
 *  * Fonts
 *  * Cursors
*/
class Cache
{
    /**
     * Initialize and load cursors from system and push them into global `m_cursors` std::vector
    */
    void _initCursors();
public:
    /**
     * Storage for system cursors (arrow, hand, pointers, ...)
    */
    static std::vector<sf::Cursor*> m_cursors;
    /**
     * Cursor type representation
    */
    enum CursorType
    { Arrow, Hand };

    /**
     * Initializes program cache
    */
    Cache();
    ~Cache() = default;
};

extern Cache cache;

};

#endif // SRC_SHAPES_CACHE_HPP_INCLUDED
