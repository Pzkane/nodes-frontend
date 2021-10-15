#ifndef SRC_SCENES_SCENE_HPP_INCLUDED
#define SRC_SCENES_SCENE_HPP_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include "EventFlags.hpp"

class Scene
{
    /* Flag mainly to disable processing without destroying the scene */
    bool m_state = false;

protected:
    sf::RenderWindow *const p_window = nullptr;
    std::vector<sf::Drawable *> m_drawables;

public:
    explicit Scene(sf::RenderWindow &window) : p_window(&window) {}
    virtual ~Scene() = default;
    virtual void update() = 0;
    virtual void draw();
    void pushDrawable(sf::Drawable *drawable, int at = -1);
    void popDrawable(int at = -1);
    void setActive(bool state);
    virtual void updateInput(const sf::Event &event) = 0;
};

#endif // SRC_SCENES_SCENE_HPP_INCLUDED
