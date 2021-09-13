#include "SceneSwitcher.hpp"

void SceneSwitcher::switchTo(Scene &scene)
{
    scene.setWindow(p_window);
    scene.setActive(true);

    m_curr_scene->setActive(false);
    m_curr_scene = &scene;
}
