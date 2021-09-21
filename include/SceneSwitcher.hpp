#ifndef SRC_SCENES_SCENESWITCHER_HPP_INCLUDED
#define SRC_SCENES_SCENESWITCHER_HPP_INCLUDED

#include "Scene.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class SceneSwitcher
{
    Scene *m_curr_scene = nullptr;
    sf::RenderWindow *p_window;

public:
    explicit SceneSwitcher(sf::RenderWindow &window) : p_window(&window) {}
    ~SceneSwitcher() = default;
    void switchTo(Scene &scene);
};

#endif // SRC_SCENES_SCENESWITCHER_HPP_INCLUDED
