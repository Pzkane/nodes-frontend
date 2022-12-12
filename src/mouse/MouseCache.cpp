#include "MouseCache.hpp"

using namespace nf;

MouseCache* MouseCache::m_moCache {nullptr};
std::mutex MouseCache::m_cacheMutex;

MouseCache::~MouseCache()
{
    if (m_moCache) delete m_moCache;
    m_moCache = nullptr;
}

MouseCache* MouseCache::getInstance(const sf::RenderWindow& window)
{
    std::unique_lock<std::mutex> ul(m_cacheMutex);
    if (!m_moCache)
        m_moCache = new MouseCache(window);
    return m_moCache;
}
