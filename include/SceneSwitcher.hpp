#ifndef SRC_SCENES_SCENESWITCHER_HPP_INCLUDED
#define SRC_SCENES_SCENESWITCHER_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"

class SceneSwitcher
{
public:
    Scene *m_curr_scene = nullptr;

public:
    explicit SceneSwitcher() {}
    ~SceneSwitcher() = default;
    void switchTo(Scene *scene);
    void updateScene();
    void drawScene();
    void unsetScene() { m_curr_scene = nullptr; }
    void updateInput(const sf::Event &event);
};

#endif // SRC_SCENES_SCENESWITCHER_HPP_INCLUDED
