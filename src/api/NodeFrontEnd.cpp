#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "NodeFrontEnd.hpp"
#include "MainScene.hpp"
#include "EventType.hpp"
#include "Cache.hpp"
#include "Overlay.hpp"

using namespace nf;

static Cache cache;
sf::Color nf::LL_HIGHLIGHT_COLOR = sf::Color::Black;
float nf::LL_HIGHLIGHT_THICKNESS = 2.f;
const float nf::LL_DEFAULT_THICKNESS = 1.f;

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
                glViewport(0, 0, event.size.width, event.size.height);
                sf::View new_view(sf::FloatRect(0, 0, event.size.width, event.size.height));
                main_m_window.setView(new_view);
                break;
            }

            default:
                break;
            }
            m_eventQueue.pop();
        }
}

// TODO: Add video_mode and title specs
NodeFrontEnd::NodeFrontEnd(const Context& settings, const char *n_title) : m_settings(settings)
{}

void NodeFrontEnd::init()
{
    say("frontend initialization...");
    m_window = new sf::RenderWindow(m_settings.m_videoMode, m_title, sf::Style::Default, m_settings);
    m_thEventPool = new std::thread(event_pool<sf::RenderWindow>, std::ref(*m_window), std::ref(m_eventQueue), std::ref(m_ss), std::ref(lf));
    MainScene *m_mainScene = new MainScene(*m_window);
    m_ss.switchTo(m_mainScene);
    m_initizlized = true;
    say("frontend initialized");
}

int NodeFrontEnd::launch_and_loop()
{
    Overlay ui;
    ui.createWrapper({{100,100}, {10,10}, {10,10}});
    ui.addContainer(Container {{80, 50}, {20,20}});
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
        if (!ui.isHidden()) {
            const auto ef = static_cast<const EventFlags*>(m_ss.getSceneFlags(Flags::Type::Event));
            ui.update(*m_window, *ef, resized);
            ui.draw(*m_window);
        }
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
        say("Destroying main window...");
        m_window->setActive(false);
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
    m_backgroundColor = color;
}

NodeImpl* NodeFrontEnd::addNode(const char *text, float x, float y, bool visible, NodeType n_type)
{
    auto p = reinterpret_cast<NodeImpl *>(m_ss.updateInput(EventType::addNode));
    p->setText(text);
    p->setVisibility(visible);
    switch (n_type)
    {
    case NodeType::LinkedList:
        say(m_ll_shift.x)
        p->setPosition(x+LL_NODE_SPACING, y);
        m_ll_shift = {m_ll_shift.x + LL_NODE_SPACING, m_ll_shift.y};
        break;
    
    default:
        p->setPosition(x, y);
        break;
    }
    return p;
}

void NodeFrontEnd::connectNodes(NodeImpl *n1, NodeImpl *n2)
{
    auto p = reinterpret_cast<Edge *>(m_ss.updateInput(EventType::addEdge));
    p->setNodeEndings(n1, n2);
}
void NodeFrontEnd::connectWeightNodes(NodeImpl *n1, NodeImpl *n2, float weight)
{
    auto p = reinterpret_cast<WeightedEdge *>(m_ss.updateInput(EventType::addWEdge));
    p->setNodeEndings(n1, n2);
    p->setWeight(weight);
}

void NodeFrontEnd::connectOrientedNodes(NodeImpl *n1, NodeImpl *n2)
{
    auto p = reinterpret_cast<Edge *>(m_ss.updateInput(EventType::addOEdge));
    p->setNodeEndings(n1, n2);
}

void NodeFrontEnd::disconnectNodes(NodeImpl *n1, NodeImpl *n2)
{
    Nodes2ptr *pn = new Nodes2ptr{n1, n2};
    m_ss.updateInput(EventType::disconnectNodes, pn);
}

void NodeFrontEnd::destroyNode(NodeImpl *n) {
    m_ss.updateInput(EventType::destroyNode, n);
}

void NodeFrontEnd::setNodePosition(NodeImpl *node, float x, float y)
{
    setNodePosition(node, sf::Vector2f(x, y));
}

void NodeFrontEnd::setNodePosition(NodeImpl *node, sf::Vector2f vf)
{
    node->setPosition(vf);
}

void NodeFrontEnd::highlightNode(NodeImpl *n) {
    n->setOutlineThickness(LL_HIGHLIGHT_THICKNESS);
    if (m_highlighted_node && &*n != &*m_highlighted_node) {
        m_highlighted_node->setOutlineThickness(LL_DEFAULT_THICKNESS);
    }
    m_highlighted_node = n;
}
