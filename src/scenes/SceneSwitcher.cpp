#include "SceneSwitcher.hpp"

void SceneSwitcher::switchTo(Scene &scene)
{
    scene.setWindow(p_window);
    if (m_curr_scene)
        m_curr_scene->setActive(false);
    scene.setActive(true);
    m_curr_scene = &scene;
}
