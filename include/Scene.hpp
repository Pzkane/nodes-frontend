#ifndef SRC_SCENES_SCENE_HPP_INCLUDED
#define SRC_SCENES_SCENE_HPP_INCLUDED

#include <list>
#include <SFML/Graphics.hpp>
#include "EventFlags.hpp"
#include "EventType.hpp"
#include "MouseCache.hpp"

namespace nf {

class Scene
{
    /* Flag to disable processing without destroying the scene */
    bool m_state = false;

protected:
    sf::RenderWindow *const p_window = nullptr;
    std::list<sf::Drawable *> m_drawables;
    MouseCache* m_mouseCache;

public:
    explicit Scene(sf::RenderWindow &window) : p_window(&window), m_mouseCache(MouseCache::getInstance(window)) {}
    virtual ~Scene();
    virtual void update() = 0;
    virtual void draw();
    virtual void *updateInput(const sf::Event &event, void* payload = nullptr) = 0;
    virtual void *updateInput(const EventType &eventType, void* payload = nullptr) = 0;
    virtual const void* getFlags(Flags::Type type) = 0;

    void pushDrawable(sf::Drawable *drawable);
    void popDrawable();
    void setActive(bool state);
    void centerView(const sf::Vector2f ptrPos);
};

};

#endif // SRC_SCENES_SCENE_HPP_INCLUDED
