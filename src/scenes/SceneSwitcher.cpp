#include "SceneSwitcher.hpp"

void SceneSwitcher::switchTo(Scene &scene)
{
    if (m_curr_scene)
        m_curr_scene->setActive(false);
    scene.setActive(true);
    m_curr_scene = &scene;
}

void SceneSwitcher::updateScene()
{
    if (m_curr_scene) m_curr_scene->update();
}

void SceneSwitcher::drawScene()
{
    if (m_curr_scene) m_curr_scene->draw();
}

void SceneSwitcher::updateInput(const sf::Event &event)
{
    if (m_curr_scene) m_curr_scene->updateInput(event);
}
