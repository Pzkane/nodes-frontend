#ifndef SRC_SCENES_SCENESWITCHER_HPP_INCLUDED
#define SRC_SCENES_SCENESWITCHER_HPP_INCLUDED

#include "Scene.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class SceneSwitcher
{
    Scene *m_curr_scene = nullptr;

public:
    explicit SceneSwitcher() {}
    ~SceneSwitcher() = default;
    void switchTo(Scene &scene);
    void updateScene();
    void drawScene();
};

#endif // SRC_SCENES_SCENESWITCHER_HPP_INCLUDED
