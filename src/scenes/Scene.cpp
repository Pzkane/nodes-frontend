#include "Scene.hpp"

using namespace nf;

Scene::~Scene()
{
    for (auto &&it = m_drawables.begin(); it != m_drawables.end();)
    {
        auto tmp_ = it;
        ++it;
        delete *tmp_;
    }
}

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

void Scene::centerView(const sf::Vector2f ptrPos)
{
    sf::View currView = p_window->getView();
    currView.setCenter(ptrPos);
    p_window->setView(currView);
}
