#include "Scene.hpp"

void Scene::draw()
{
    if (m_state && p_window != nullptr)
        for (auto drawable : m_drawables)
            p_window->draw(*drawable);
}

void Scene::pushDrawable(sf::Drawable *drawable, size_t at)
{
    if (at < 0)
        m_drawables.push_back(std::move(drawable));
    else if (at <= m_drawables.size())
        m_drawables.emplace(m_drawables.begin() + at, std::move(drawable));
}

void Scene::popDrawable(size_t at)
{
    if (!m_drawables.size())
        return;

    if (at < 0)
        m_drawables.pop_back();
    else
        m_drawables.erase(m_drawables.begin() + at);
}

void Scene::setActive(bool state)
{
    m_state = state;
}

void Scene::setWindow(const sf::RenderWindow *window)
{
    p_window = const_cast<sf::RenderWindow *>(window);
}
