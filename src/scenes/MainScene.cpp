#include "MainScene.hpp"
#include "Connector.hpp"
#include "utils.hpp"

MainScene::MainScene(sf::RenderWindow &window) : Scene(window)
{
}

MainScene::~MainScene()
{
    for (auto &&it = m_connectors.begin(); it != m_connectors.end();)
    {
        auto tmp_ = it;
        ++it;
        delete *tmp_;
    }

    for (auto &&it = m_nodes.begin(); it != m_nodes.end();)
    {
        auto tmp_ = it;
        ++it;
        delete *tmp_;
    }
}

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

void MainScene::popNode(int at)
{
    if (!m_nodes.size())
        return;

    if (at < 0)
    {
        delete m_nodes[m_nodes.size() - 1];
        m_nodes.pop_back();
    }
    else if (at < m_nodes.size())
    {
        delete m_nodes[at];
        m_nodes.erase(m_nodes.begin() + at);
    }
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
    for (auto &&node : m_nodes)
        node->update(*p_window, ef);

    for (auto &&conn : m_connectors)
        conn->update();

    if (ef.p_start_node != nullptr && ef.p_end_node != nullptr)
    {
        pushConnector(new Connector(ef.p_start_node, ef.p_end_node));
        ef.p_start_node = nullptr;
        ef.p_end_node = nullptr;
        /* Force RMB flag release to avoid setting starting node */
        ef.f_rmb = false;
        say("BUTTONS CLEARED");
    }
}

void MainScene::draw()
{
    for (auto &&it : m_connectors)
    {
        p_window->draw(it->getDrawable());
    }

    for (auto &&it : m_nodes)
    {
        p_window->draw(*it);
    }
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
