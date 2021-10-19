#include "Scene.hpp"

void Scene::draw()
{
    if (m_state)
        for (auto &&drawable : m_drawables)
            p_window->draw(*drawable);
}

void Scene::pushDrawable(sf::Drawable *drawable)
{
    m_drawables.push_back(std::move(drawable));
}

void Scene::popDrawable()
{
    if (!m_drawables.size())
        return;

    m_drawables.pop_back();
}

void Scene::setActive(bool state)
{
    m_state = state;
}
