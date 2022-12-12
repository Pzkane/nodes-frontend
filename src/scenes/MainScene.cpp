#include <algorithm>

#include "MainScene.hpp"
#include "Edge.hpp"
#include "WeightedEdge.hpp"
#include "Cache.hpp"
#include "utils.hpp"
#include "MouseCache.hpp"

using namespace nf;

MainScene::MainScene(sf::RenderWindow &window) : ef(), Scene(window)
{
#ifdef BENCHMARK
    for (int i = 0; i < 30000; ++i)
    {
        _Node *node = new _Node(DEF_NODE_RAD);
        node->setFillColor(sf::Color::Red);
        node->sf::CircleShape::setPosition(sf::Vector2f(Utils::get_random_number<float>(0.f, 500.f), Utils::get_random_number<float>(0.f, 500.f)));
        pushNode(node);
    }
#endif
}

MainScene::~MainScene()
{
    for (auto &&it = m_edges.begin(); it != m_edges.end();)
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

_Node* MainScene::createNode(float radius = DEF_NODE_RAD)
{
    _Node *node = new _Node(DEF_NODE_RAD);
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

Edge* MainScene::createEdge()
{
    Edge *conn = new Edge;
    pushEdge(conn);
    return conn;
}

void MainScene::removeEdge(Nodes2ptr *ptr_payload)
{
    for (auto &&it : m_edges)
    {
        auto nodeRef = it->getNodeEndings();
        if (
            (nodeRef.start == ptr_payload->n1 || nodeRef.start == ptr_payload->n2)
            &&
            (nodeRef.end == ptr_payload->n1 || nodeRef.end == ptr_payload->n2)
        )
            it->enf.f_delete_self = true;
    }
}

void MainScene::pushNode(_Node *node)
{
    m_nodes.push_back(node);
}

void MainScene::pushEdge(Edge *conn)
{
    m_edges.push_back(conn);
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
    Cache::CursorType cursorType = Cache::CursorType::Arrow;

    for (auto it = m_edges.begin(); it != m_edges.end();)
        if ((*it)->enf.f_delete_self)
        {
            delete (*it);
            it = m_edges.erase(it);
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
            // Unintentional, but useful feature - wil always
            // swap 2 of overlaying elements
            if ((*it)->isMoving() && it != std::prev(m_nodes.end()))
                std::iter_swap(it, m_nodes.rbegin());

            (*it)->update(*p_window, ef);

            Mouse& m = MouseCache::getInstance(*p_window)->gMouse;

            if (m.getEntity() == (*it))
                (*it)->setMovable(true);
            else
                (*it)->setMovable(false);

            if ((*it)->m_hovering)
                cursorType = Cache::CursorType::Hand;
            ++it;
        }
    }

    switch (cursorType)
    {
    case Cache::CursorType::Hand:
        p_window->setMouseCursor(*cache.m_cursors[Cache::CursorType::Hand]);
        break;

    case Cache::CursorType::Arrow:
        p_window->setMouseCursor(*cache.m_cursors[Cache::CursorType::Arrow]);
        break;
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
        Edge *conn;
        if (ef.f_space)
            conn = new WeightedEdge(ef.p_start_node, ef.p_end_node);
        else
            conn = new Edge(ef.p_start_node, ef.p_end_node);
        pushEdge(conn);
        ef.p_start_node->pushConnNode(ef.p_end_node);
        ef.p_end_node->pushConnNode(ef.p_start_node);
        clearEFNodes();
        /* Force RMB flag release to avoid setting starting node */
        say("BUTTONS CLEARED");
    }
}

void MainScene::draw()
{
    for (auto &&it : m_edges)
    {
        it->draw(*p_window);
    }

    for (auto &&it : m_nodes)
    {
        it->draw(*p_window);
    }
}

void *MainScene::updateInput(const sf::Event &event, void* payload)
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

        case sf::Keyboard::Space:
            say("Space toggle");
            ef.f_space = !ef.f_space;
            break;

        case sf::Keyboard::R:
            say("R toggle");
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }

    if (ef.f_mmb)
        centerView();

    return nullptr;
}

void* MainScene::updateInput(const EventType &eventType, void* payload)
{
    switch (eventType)
    {
    case addNode:
        return createNode();
    case addEdge:
        return createEdge();
    case disconnectNodes:
        removeEdge(reinterpret_cast<Nodes2ptr*>(payload));
        return nullptr;
    default:
        break;
    }
    return nullptr;
}
