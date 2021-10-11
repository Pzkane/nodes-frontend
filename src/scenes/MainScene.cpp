#include "MainScene.hpp"
#include "utils.hpp"

MainScene::MainScene(sf::RenderWindow &window) : Scene(window)
{}

void MainScene::createNode()
{
    Node *node = new Node(40);
    node->setFillColor(sf::Color::Red);
    node->sf::CircleShape::setPosition(Utils::getMousePosf(*p_window));
    pushNode(node);
}

void MainScene::pushNode(Node *node, int at)
{
    if (at < 0)
        m_nodes.push_back(node);
    else if (at <= m_nodes.size())
        m_nodes.emplace(m_nodes.begin() + at, node);
}

void MainScene::pushConnector(Connector *node, int at)
{
    if (at < 0)
        m_connectors.push_back(node);
    else if (at <= m_connectors.size())
        m_connectors.emplace(m_connectors.begin() + at, node);
}

void MainScene::update()
{
    for (auto *node : m_nodes)
        node->update(*p_window, ef);
    if (ef.p_start_node != nullptr && ef.p_end_node != nullptr)
    {
        pushConnector(ef.p_start_node->connectTo(ef.p_end_node));
        ef.p_start_node = nullptr;
        ef.p_end_node = nullptr;
    }
}

void MainScene::draw()
{
    for (int i = 0; i < m_nodes.size(); ++i)
    {
        if (i < m_connectors.size())
            p_window->draw(m_connectors[i]->getDrawable());
        p_window->draw(*m_nodes[i]);
    }
    Scene::draw();
}

void MainScene::updateInput(const sf::Event &event)
{
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
        switch (event.mouseButton.button)
        {
        case sf::Mouse::Left:
            ef.f_lmb = true;
            break;

        case sf::Mouse::Right:
            ef.f_rmb = true;
            break;

        default:
            break;
        }
        break;

    case sf::Event::MouseButtonReleased:
        switch (event.mouseButton.button)
        {
        case sf::Mouse::Left:
            ef.f_lmb = false;
            break;

        case sf::Mouse::Right:
            ef.f_rmb = false;
            break;

        default:
            break;
        }
        break;

    case sf::Event::KeyReleased:
        switch (event.key.code)
        {
        case sf::Keyboard::LControl:
            createNode();
            break;
        
        default:
            break;
        }
    default:
        break;
    }
}
