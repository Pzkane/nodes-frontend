#include "MainScene.hpp"
#include "utils.hpp"

MainScene::MainScene(sf::RenderWindow &window) : Scene(window)
{
    for (int i = 0; i < 1; ++i)
    {
        Node *node = new Node(40);
        node->setFillColor(sf::Color::Red);
        node->sf::CircleShape::setPosition(sf::Vector2f(Utils::get_random_number<float>(0.f, 500.f), Utils::get_random_number<float>(0.f, 500.f)));
        pushNode(node);
    }
}

void MainScene::update()
{
    for (auto *node : m_nodes)
        node->update(*p_window, ef);
}

void MainScene::draw()
{
    for (auto *node : m_nodes)
        p_window->draw(*node);
    Scene::draw();
}

void MainScene::pushNode(Node *node, int at)
{
    if (at < 0)
        m_nodes.push_back(std::move(node));
    else if (at <= m_drawables.size())
        m_nodes.emplace(m_nodes.begin() + at, std::move(node));
}

void MainScene::updateInput(const sf::Event &event)
{
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
        ef.f_lmb = true;
        break;

    case sf::Event::MouseButtonReleased:
        ef.f_lmb = false;
        break;

    default:
        break;
    }
}
