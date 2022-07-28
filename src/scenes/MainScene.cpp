#include "MainScene.hpp"
#include "Connector.hpp"
#include "utils.hpp"

MainScene::MainScene(sf::RenderWindow &window) : Scene(window)
{
#ifdef BENCHMARK
    for (int i = 0; i < 30000; ++i)
    {
        Node *node = new Node(40);
        node->setFillColor(sf::Color::Red);
        node->sf::CircleShape::setPosition(sf::Vector2f(Utils::get_random_number<float>(0.f, 500.f), Utils::get_random_number<float>(0.f, 500.f)));
        pushNode(node);
    }
#endif
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

Node *MainScene::createNode()
{
    Node *node = new Node(40);
    node->setFillColor(sf::Color::Red);
    node->sf::CircleShape::setPosition(Utils::getMousePosf(*p_window));
    node->setText("Testing!");
    pushNode(node);
    return node;
}

void MainScene::pushNode(Node *node)
{
    m_nodes.push_back(node);
}

void MainScene::pushConnector(Connector *node)
{
    m_connectors.push_back(node);
}

void MainScene::update()
{
    for (auto it = m_nodes.begin(); it != m_nodes.end();)
        if ((*it)->enf.f_del)
        {
            delete (*it);
            it = m_nodes.erase(it);
        }
        else
            (*it++)->update(*p_window, ef);

    for (auto it = m_connectors.begin(); it != m_connectors.end();)
        if ((*it)->enf.f_del)
        {
            delete (*it);
            it = m_connectors.erase(it);
        }
        else
            (*it++)->update();

    if (ef.p_start_node != nullptr && ef.p_end_node != nullptr)
    {
        Connector *conn = new Connector(ef.p_start_node, ef.p_end_node);
        pushConnector(conn);
        ef.p_start_node->pushConnector(conn);
        ef.p_end_node->pushConnector(conn);
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
        it->draw(*p_window);
    }
}

void *MainScene::updateInput(const sf::Event &event)
{
    ef.f_lalt = false;
    ef.f_ralt = false;
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
            return createNode();
            break;

        case sf::Keyboard::LAlt:
            ef.f_lalt = true;
            break;

        case sf::Keyboard::RAlt:
            ef.f_ralt = true;
            break;

        default:
            break;
        }
    default:
        break;
    }
    return nullptr;
}

void *MainScene::updateInput(const EventType &eventType)
{
    switch (eventType)
    {
    case addNode:
        return createNode();
    default:
        break;
    }
    return nullptr;
}
