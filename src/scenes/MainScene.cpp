#include <algorithm>

#include "MainScene.hpp"
#include "Edge.hpp"
#include "Cache.hpp"
#include "utils.hpp"
#include "MouseCache.hpp"

using namespace nf;

MainScene::MainScene(sf::RenderWindow &window) : ef(), Scene(window)
{
#ifdef BENCHMARK
    for (int i = 0; i < 30000; ++i)
    {
        NodeImpl *node = new NodeImpl(nullptr, DEF_NODE_RAD);
        node->setFillColor(sf::Color::Red);
        node->sf::CircleShape::setPosition(sf::Vector2f(Utils::get_random_number<float>(0.f, 500.f), Utils::get_random_number<float>(0.f, 500.f)));
        pushNode(node);
    }
#endif
    // Overlay* ui = new Overlay();
    // ui->createWrapper({{100,100}, {10,10}, {10,10}});
    // ui->addContainer(Container {{80, 50}, {20,20}});
    // Overlay** p_ui = m_uis.createResource();
    // *p_ui = *&ui;
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

NodeImpl* MainScene::createNode(Observable *entity = nullptr, float radius = DEF_NODE_RAD)
{
    NodeImpl *node = new NodeImpl(entity, radius);
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
    Edge* conn = new Edge;
    pushEdge(conn);
    return conn;
}

OrientedEdge* MainScene::createOEdge()
{
    OrientedEdge* conn = new OrientedEdge;
    pushEdge(conn);
    return conn;
}

WeightedEdge* MainScene::createWEdge()
{
    WeightedEdge* conn = new WeightedEdge;
    pushEdge(conn);
    return conn;
}

void MainScene::removeNode(NodeImpl *node_ptr_payload)
{
    for (auto* it : m_nodes)
    {
        if (&(*it) == &(*node_ptr_payload)) {
            it->destroy();
            break;
        }
    }
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

void MainScene::pushNode(NodeImpl *node)
{
    m_nodes.push_back(node);
}

void MainScene::pushEdge(Edge *conn)
{
    m_edges.push_back(conn);
}

void MainScene::centerView()
{
    sf::Vector2f mousePos = Utils::getMousePosf(*p_window);
    sf::Vector2f currCenter = p_window->getView().getCenter();
    sf::Vector2f offset {currCenter.x - mousePos.x, currCenter.y - mousePos.y};
    for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it) {
        sf::Vector2f currNodePos = (*it)->getPosition();
        (*it)->setPosition(currNodePos.x + offset.x, currNodePos.y + offset.y);
    }
}

void MainScene::moveView(int offset_x, int offset_y)
{
    for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it) {
        sf::Vector2f currNodePos = (*it)->getPosition();
        (*it)->setPosition(currNodePos.x + offset_x, currNodePos.y + offset_y);
    }
}

void MainScene::mergeOverlay(Overlay* child) {
    Overlay** p_ui = m_uis.createResource();
    *p_ui = *&child;
}

// void MainScene::divideOverlay(Overlay* child) {
//     m_uis.erase(std::remove_if(m_uis.begin(), m_uis.end(), [&child](Overlay *element) -> bool {
//         if (&element == &child) return true;
//         return false;
//     }), m_uis.end());
// }

void MainScene::update()
{
    Cache::CursorType cursorType = Cache::CursorType::Arrow;

    for (auto it = m_nodes.rbegin(); it != m_nodes.rend();)
    {
        if ((*it)->enf.f_delete_self)
        {
            delete (*it);
            // Temp iterator for reverse action
            auto tmp = m_nodes.erase(--it.base());
            it = std::list<NodeImpl*>::reverse_iterator(tmp);
        }
        else
        {
            // Move last dragged node on top
            if ((*it)->isMoving() && it != std::prev(m_nodes.rend()))
                std::iter_swap(it, m_nodes.rbegin());

            (*it)->update(*p_window, ef);
            
            // Check if any node in current order is marked for removal and disable event flag
            if ((*it)->enf.f_delete_self) {
                ef.f_lalt = false;
            }

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

    for (auto it = m_edges.rbegin(); it != m_edges.rend();)
    if ((*it)->enf.f_delete_self) {
        delete (*it);
        // Temp iterator for reverse action
        auto tmp = m_edges.erase(--it.base());
        it = std::list<Edge*>::reverse_iterator(tmp);
    } else {
        (*it)->update(*p_window, ef);

        // Check if any node in current order is marked for removal and disable event flag
        if ((*it)->enf.f_delete_self) {
            ef.f_lalt = false;
        }
        ++it;
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
    updateUI();
}

void MainScene::updateUI(bool resized) {
    for (Resource<Overlay*>::iterator el = m_uis.begin(); el != m_uis.end();) {
        if (!(*el)) {
            el = m_uis.erase(el);
            continue;
        }

        if (!(**el)->isHidden()) {
            (**el)->update(*p_window, ef, resized);
        }
        ++el;
    }
}

void MainScene::draw()
{
    for (auto &&it : m_edges)
    {
        if (it->isVisible())
            it->draw(*p_window);
    }

    for (auto &&it : m_nodes)
    {
        if (it->isVisible())
            it->draw(*p_window);
    }

    for (Resource<Overlay*>::iterator el = m_uis.begin(); el != m_uis.end();) {
        if (!(*el)) {
            el = m_uis.erase(el);
            continue;
        }
        if (!(**el)->isHidden()) {
            (**el)->draw(*p_window);
        }
        ++el;
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

    case sf::Event::KeyPressed:
        switch (event.key.code)
        {
        case sf::Keyboard::LShift:
            ef.f_lshift = true;
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
            ef.f_space = true;
            break;

        case sf::Keyboard::LShift:
            ef.f_lshift = false;
            break;

        default:
            break;
        }
        break;

    case sf::Event::MouseWheelScrolled:
        {
            float scrolled = event.mouseWheelScroll.delta;
            if (!ef.f_lshift) {
                moveView(0, scrolled*50);
            } else {
                moveView(scrolled*50, 0);
            }
        }
        break;

    case sf::Event::Resized:
        updateUI(true);
        break;

    default:
        break;
    }

    if (ef.f_mmb) {
        centerView();
        // Reset dragging
        ef.f_mmb = false;
    }

    return nullptr;
}

void* MainScene::updateInput(const EventType &eventType, void* payload)
{
    switch (eventType)
    {
    case EventType::addNode:
        return createNode(reinterpret_cast<Observable*>(payload));
    case EventType::addEdge:
        return createEdge();
    case EventType::addOEdge:
        return createOEdge();
    case EventType::addWEdge:
        return createWEdge();
    case EventType::addOverlay:
        mergeOverlay(reinterpret_cast<Overlay*>(payload));
        return nullptr;
    case EventType::disconnectNodes:
        removeEdge(reinterpret_cast<Nodes2ptr*>(payload));
        return nullptr;
    case EventType::destroyNode:
        removeNode(reinterpret_cast<NodeImpl*>(payload));
        return nullptr;
    default:
        break;
    }
    return nullptr;
}

const void* MainScene::getFlags(Flags::Type type) {
    struct Bad_Flag_Type {};
    switch (type)
    {
    case Flags::Type::Event:
        return &ef;
    }
    throw Bad_Flag_Type {};
}
