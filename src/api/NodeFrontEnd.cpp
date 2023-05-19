#include <algorithm>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "NodeFrontEnd.hpp"
#include "MainScene.hpp"
#include "EventType.hpp"
#include "Cache.hpp"

using namespace nf;

static Cache cache;
sf::Color nf::LL_HIGHLIGHT_COLOR = sf::Color::Black;
sf::Color nf::LL_SELECT_COLOR = sf::Color{200, 200, 200};
sf::Color nf::LL_DEFAULT_COLOR = sf::Color{220, 220, 220};
float nf::LL_HIGHLIGHT_THICKNESS = 2.f;
const float nf::LL_DEFAULT_THICKNESS = 1.f;

float NodeFrontEnd::PADDING = 50;
size_t NodeFrontEnd::LL_NODE_SPACING = 150;
int NodeFrontEnd::RANDOM_SPACING = 500;

size_t NodeFrontEnd::BT_PARENT_NODE_CENTER_OFFSET_X = 75;
size_t NodeFrontEnd::BT_PARENT_NODE_CENTER_OFFSET_Y = 100;

template <typename Tw>
static void event_pool(Tw &main_m_window, Utils::SafeQueue<sf::Event> &m_eventQueue, SceneSwitcher &m_ss, LoopFlags &flags)
{
    while (!flags.f_t_ep_done)
        while (m_eventQueue.size())
        {
            auto event = m_eventQueue.front();
            m_ss.updateInput(event);
            switch (event.type)
            {
            case sf::Event::Closed:
                flags.f_t_delete_active_scene = true;
                break;

            case sf::Event::Resized:
            {
                sf::View new_view(sf::FloatRect(0, 0, event.size.width, event.size.height));
                main_m_window.setView(new_view);
                break;
            }

            default:
                break;
            }
            m_eventQueue.pop();
        }
    main_m_window.setActive(false);
}

NodeFrontEnd::NodeFrontEnd(const Context& settings, const char *n_title) : m_settings(settings)
{}

void NodeFrontEnd::init()
{
    say("frontend initialization...");
    m_window = new sf::RenderWindow(m_settings.m_videoMode, m_title, sf::Style::Default, m_settings);
    m_window->setActive(false);
    m_thEventPool = new std::thread(event_pool<sf::RenderWindow>, std::ref(*m_window), std::ref(m_eventQueue), std::ref(m_ss), std::ref(lf));
    MainScene *m_mainScene = new MainScene(*m_window);
    m_ss.switchTo(m_mainScene);
    m_initizlized = true;
    say("frontend initialized");
}

int NodeFrontEnd::launch_and_loop()
{
    sf::Context context;
    bool running = true;

    m_window->setFramerateLimit(75);
    m_window->setActive(true);

    while (running)
    {
        bool resized = false;
        sf::Event event;
        while (m_window->pollEvent(event)) {
            if (event.type == sf::Event::Resized)
                resized = true;
            m_eventQueue.push(event);
        }

        if (lf.f_t_delete_active_scene)
        {
            m_ss.deleteCurrScene();
            lf.f_t_delete_active_scene = false;
            lf.f_t_ep_done = true;
            break;
        }

        m_ss.updateScene();
        m_ss.drawScene();

        m_window->display();
        m_window->clear(m_backgroundColor);

        if (lf.switchedOff())
            running = false;
    }

    m_thEventPool->join();

    return 0;
}

NodeFrontEnd::~NodeFrontEnd()
{
    say("Destroying API...");
    _cleanup();
    say("API destroyed");
}

void NodeFrontEnd::_cleanup()
{
    m_ss.cleanup();
    if (m_window)
    {
        say("Deactivating main window...");
        m_window->setActive(false);
        say("Closing main window...");
        m_window->close();
        delete m_window;
        m_window = nullptr;
        say("Main window destroyed");
    }
    if (m_thEventPool)
    {
        say("Destroying event pool...");
        delete m_thEventPool;
        m_thEventPool = nullptr;
        say("Event pool destroyed");
    }
}

void NodeFrontEnd::setWindowColor(const sf::Color &color)
{
    if (lf.f_t_ep_done) return;
    m_backgroundColor = color;
}

NodeImpl* NodeFrontEnd::addNode(const char *text, float x, float y, bool visible, LayoutType l_type, Observable *entity)
{
    if (lf.f_t_ep_done) return nullptr;
    auto p = reinterpret_cast<NodeImpl *>(m_ss.updateInput(EventType::addNode));
    p->setText(text);
    p->setVisibility(visible);
    switch (l_type)
    {
    case LayoutType::Line:
        p->setPosition(x+LL_NODE_SPACING, y);
        p->setObservable(entity);
        m_ll_shift = {m_ll_shift.x + LL_NODE_SPACING, m_ll_shift.y};
        break;
    case LayoutType::Random:
        p->setPosition(Utils::get_random_number(x, x+RANDOM_SPACING)
                     , Utils::get_random_number(y, y+RANDOM_SPACING));
        p->setObservable(entity);
        break;

    case LayoutType::None:
    default:
        p->setPosition(x, y);
        break;
    }
    return p;
}

void NodeFrontEnd::connectNodes(NodeImpl *n1, NodeImpl *n2)
{
    if (lf.f_t_ep_done) return;
    auto p = reinterpret_cast<Edge *>(m_ss.updateInput(EventType::addEdge));
    p->setNodeEndings(n1, n2);
}
void NodeFrontEnd::connectWeightNodes(NodeImpl *n1, NodeImpl *n2, float weight)
{
    if (lf.f_t_ep_done) return;
    auto p = reinterpret_cast<WeightedEdge *>(m_ss.updateInput(EventType::addWEdge));
    p->setNodeEndings(n1, n2);
    p->setWeight(weight);
}

void NodeFrontEnd::connectOrientedNodes(NodeImpl *n1, NodeImpl *n2)
{
    if (lf.f_t_ep_done) return;
    for (NodeImpl* neighbor : n1->getConnectedNodes()) {
        if (&(*neighbor) == &(*n2)) {
            Nodes2ptr nodes{n1, n2};
            Nodes2ptr *pn = &nodes;
            auto p = reinterpret_cast<OrientedEdge *>(m_ss.updateInput(EventType::queryEdge, pn));
            auto nodeRef = p->getNodeEndings();
            if (&(*(nodeRef.start)) == &(*n2))
                p->m_2way = true;
            return;
        }
    }
    auto p = reinterpret_cast<OrientedEdge *>(m_ss.updateInput(EventType::addOEdge));
    p->setNodeEndings(n1, n2);
}

void NodeFrontEnd::connectWeightOrientedNodes(NodeImpl *n1, NodeImpl *n2, float weight)
{
    if (lf.f_t_ep_done) return;
    for (NodeImpl* neighbor : n1->getConnectedNodes()) {
        if (&(*neighbor) == &(*n2)) {
            Nodes2ptr nodes{n1, n2};
            Nodes2ptr *pn = &nodes;
            auto p = reinterpret_cast<WeightedOrientedEdge *>(m_ss.updateInput(EventType::queryEdge, pn));
            p->setWeight(weight);
            auto nodeRef = p->getNodeEndings();
            if (&(*(nodeRef.start)) == &(*n2))
                p->m_2way = true;
            return;
        }
    }
    auto p = reinterpret_cast<WeightedOrientedEdge *>(m_ss.updateInput(EventType::addWOEdge));
    p->setNodeEndings(n1, n2);
    p->setWeight(weight);
}

void NodeFrontEnd::disconnectNodes(NodeImpl *n1, NodeImpl *n2)
{
    if (lf.f_t_ep_done) return;
    Nodes2ptr nodes{n1, n2};
    Nodes2ptr *pn = &nodes;
    m_ss.updateInput(EventType::disconnectNodes, pn);
}

void NodeFrontEnd::destroyNode(NodeImpl *n) {
    m_ss.updateInput(EventType::destroyNode, n);
}

void NodeFrontEnd::setNodePosition(NodeImpl *node, float x, float y)
{
    if (lf.f_t_ep_done) return;
    setNodePosition(node, sf::Vector2f(x, y));
}

void NodeFrontEnd::setNodePosition(NodeImpl *node, sf::Vector2f vf)
{
    if (lf.f_t_ep_done) return;
    node->setPosition(vf);
}

void NodeFrontEnd::highlightNode(NodeImpl *n) {
    if (lf.f_t_ep_done) return;
    n->setOutlineThickness(LL_HIGHLIGHT_THICKNESS);
    if (m_highlighted_node && &*n != &*m_highlighted_node) {
        m_highlighted_node->setOutlineThickness(LL_DEFAULT_THICKNESS);
    }
    m_highlighted_node = n;
}

void NodeFrontEnd::selectNode(NodeImpl *n) {
    if (lf.f_t_ep_done) return;
    n->setFillColor(LL_SELECT_COLOR);
    if (m_selected_node && &*n != &*m_selected_node) {
        m_selected_node->setFillColor(LL_DEFAULT_COLOR);
    }
    m_selected_node = n;
}

NodeImpl* NodeFrontEnd::getSelectedNode() {
    return m_selected_node;
}

void NodeFrontEnd::mergeOverlay(Overlay &child) {
    Overlay* p_ui = &child;
    m_ss.updateInput(EventType::addOverlay, p_ui);
}
