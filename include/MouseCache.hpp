#ifndef SRC_MOUSE_MOUSECACHE_HPP_INCLUDED
#define SRC_MOUSE_MOUSECACHE_HPP_INCLUDED

#include <mutex>
#include <SFML/Graphics.hpp>
#include "Mouse.hpp"

namespace nf {

class MouseCache
{
    MouseCache(const sf::RenderWindow& window) : gMouse(window) {}
    ~MouseCache();
protected:
    static MouseCache* m_moCache;
    static std::mutex m_cacheMutex;
public:
    Mouse gMouse;

    MouseCache(MouseCache&) = delete;
    void operator=(const MouseCache&) = delete;
    static MouseCache* getInstance(const sf::RenderWindow& window);
};

};

#endif // SRC_MOUSE_MOUSECACHE_HPP_INCLUDED
