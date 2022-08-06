#ifndef SRC_SCENES_SCENE_HPP_INCLUDED
#define SRC_SCENES_SCENE_HPP_INCLUDED

#include <list>
#include <SFML/Graphics.hpp>
#include "EventFlags.hpp"
#include "EventType.hpp"

namespace nf {

class Scene
{
    /* Flag mainly to disable processing without destroying the scene */
    bool m_state = false;

protected:
    sf::RenderWindow *const p_window = nullptr;
    std::list<sf::Drawable *> m_drawables;

public:
    explicit Scene(sf::RenderWindow &window) : p_window(&window) {}
    virtual ~Scene() = default;
    virtual void update() = 0;
    virtual void draw();
    virtual void *updateInput(const sf::Event &event) = 0;
    virtual void *updateInput(const EventType &eventType) = 0;

    void pushDrawable(sf::Drawable *drawable);
    void popDrawable();
    void setActive(bool state);
};

};

#endif // SRC_SCENES_SCENE_HPP_INCLUDED
