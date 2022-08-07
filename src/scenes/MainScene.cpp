#include <algorithm>

#include "MainScene.hpp"
#include "Connector.hpp"
#include "utils.hpp"

using namespace nf;

const size_t DEF_NODE_RAD = 40;

MainScene::MainScene(sf::RenderWindow &window) : Scene(window)
{
#ifdef BENCHMARK
    for (int i = 0; i < 30000; ++i)
    {
        Node *node = new Node(DEF_NODE_RAD);
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

Node* MainScene::createNode(float radius = DEF_NODE_RAD)
{
    Node *node = new Node(40);
    node->setFillColor(sf::Color::Red);
    sf::Vector2f mPos = Utils::getMousePosf(*p_window);
    sf::Vector2f createPos = mPos;
    sf::Vector2u winSize = p_window->getSize();

    if (mPos.x < 0)
        createPos.x = radius;
    else if (mPos.x > winSize.x)
        createPos.x = winSize.x - radius;

    if (mPos.y < 0)
        createPos.y = radius;
    else if (mPos.y > winSize.y)
        createPos.y = winSize.y - radius;

    node->sf::CircleShape::setPosition(createPos);
    node->setText("Testing!");
    pushNode(node);
    return node;
}

void MainScene::pushNode(Node *node)
{
    m_nodes.push_back(node);
}

void MainScene::pushConnector(Connector *conn)
{
    m_connectors.push_back(conn);
}

void MainScene::centerView()
{
    sf::Vector2f oldMousePos = Utils::getMousePosf(*p_window);
    // for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
    // {
    //     sf::Vector2f currNodePos = (*it)->getPosition();
    //     float offsetX = oldMousePos.x - currNodePos.x;
    //     float offsetY = oldMousePos.y - currNodePos.y;
    //     (*it)->setPosition(p_window->getView().getCenter().x + offsetX,
    //                        p_window->getView().getCenter().y + offsetY);
    // }
    Scene::centerView(oldMousePos);
}

void MainScene::update()
{
    for (auto it = m_connectors.begin(); it != m_connectors.end();)
        if ((*it)->enf.f_delete_self)
        {
            delete (*it);
            it = m_connectors.erase(it);
        }
        else
            (*it++)->update(*p_window, ef);

    for (auto it = m_nodes.begin(); it != m_nodes.end();)
    {
        if ((*it)->enf.f_delete_self)
        {
            delete (*it);
            it = m_nodes.erase(it);
        }
        else
        {
            // TODO: Fix single item drag
            // if (ef.f_lmb)
            //     if ((*m_nodes.rbegin())->isMoving() && it != std::prev(m_nodes.end()))
            //         (*it)->setMovable(false);
            //     else
            //     {
                    (*it)->setMovable(true);
                    if ((*it)->getDragState() && it != std::prev(m_nodes.end()))
                        std::iter_swap(it, m_nodes.rbegin());
            //     }
            // else
            //     (*it)->setMovable(false);
            (*it)->update(*p_window, ef);
            ++it;
        }
    }

    if (ef.p_start_node != nullptr && ef.p_end_node != nullptr)
    {
        auto clearEFNodes = [&](bool clearAll = true)
        {
            if (clearAll)
            {
                ef.p_start_node = nullptr;
                ef.p_end_node = nullptr;
            } else {
                ef.p_start_node = ef.p_end_node;
                ef.p_end_node = nullptr;
            }
            ef.f_rmb = false;
        };

        for(auto &it : ef.p_start_node->getConnectedNodes())
        {
            if (it == ef.p_end_node)
            {
                clearEFNodes(false);
                return;
            }
        }
        Connector *conn = new Connector(ef.p_start_node, ef.p_end_node);
        pushConnector(conn);
        ef.p_start_node->pushConnNode(ef.p_end_node);
        ef.p_end_node->pushConnNode(ef.p_start_node);
        clearEFNodes();
        /* Force RMB flag release to avoid setting starting node */
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

        case sf::Mouse::Middle:
            ef.f_mmb = true;
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

        case sf::Mouse::Middle:
            ef.f_mmb = false;
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

    if (ef.f_mmb)
        centerView();

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
