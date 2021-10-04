#ifndef SRC_SCENES_SCENESWITCHER_HPP_INCLUDED
#define SRC_SCENES_SCENESWITCHER_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"

class SceneSwitcher
{
    Scene *m_curr_scene = nullptr;

public:
    explicit SceneSwitcher() {}
    ~SceneSwitcher() = default;
    void switchTo(Scene &scene);
    void updateScene();
    void drawScene();
    void updateInput(const sf::Event &event);
};

#endif // SRC_SCENES_SCENESWITCHER_HPP_INCLUDED
