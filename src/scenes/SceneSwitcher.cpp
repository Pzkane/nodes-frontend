#include "SceneSwitcher.hpp"

using namespace nf;

void SceneSwitcher::cleanup()
{
    if (m_curr_scene)
    {
        m_curr_scene->setActive(false);
        deleteCurrScene();
    }
}

void SceneSwitcher::switchTo(Scene *scene)
{
    if (m_curr_scene)
        m_curr_scene->setActive(false);
    scene->setActive(true);
    m_curr_scene = scene;
}

void SceneSwitcher::updateScene()
{
    if (m_curr_scene)
        m_curr_scene->update();
}

void SceneSwitcher::drawScene()
{
    if (m_curr_scene)
        m_curr_scene->draw();
}

void *SceneSwitcher::updateInput(const sf::Event &event, void* payload)
{
    if (m_curr_scene)
        return m_curr_scene->updateInput(event, payload);
    return nullptr;
}

void *SceneSwitcher::updateInput(const EventType &eventType, void* payload)
{
    if (m_curr_scene)
        return m_curr_scene->updateInput(eventType, payload);
    return nullptr;
}

void SceneSwitcher::deleteCurrScene()
{
    delete m_curr_scene;
    m_curr_scene = nullptr;
}

const void* SceneSwitcher::getSceneFlags(Flags::Type type) {
    return m_curr_scene->getFlags(type);
}

