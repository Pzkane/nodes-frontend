#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "NodeFrontEnd.hpp"
#include "MainScene.hpp"
#include "EventType.hpp"
#include "Cache.hpp"

using namespace nf;

static Cache cache;

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
NodeFrontEnd::NodeFrontEnd(const sf::VideoMode &video_mode, const char *n_title)
{}

void NodeFrontEnd::init()
{
    say("frontend initialization...");
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    m_videoMode.width = 800;
    m_videoMode.height = 640;
    m_window = new sf::RenderWindow(m_videoMode, m_title, sf::Style::Default, settings);
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
        sf::Event event;
        if (m_window->pollEvent(event))
            m_eventQueue.push(event);

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

_Node* NodeFrontEnd::addNode(const char *text, float x, float y)
{
    auto p = reinterpret_cast<_Node *>(m_ss.updateInput(EventType::addNode));
    p->setText(text);
    p->setPosition(x, y);
    return p;
}

void NodeFrontEnd::connectNodes(_Node *n1, _Node *n2)
{
    auto p = reinterpret_cast<Edge *>(m_ss.updateInput(EventType::addEdge));
    p->setNodeEndings(n1, n2);
}
void NodeFrontEnd::connectWeightNodes(_Node *n1, _Node *n2, float weight)
{
    auto p = reinterpret_cast<WeightedEdge *>(m_ss.updateInput(EventType::addWEdge));
    p->setNodeEndings(n1, n2);
    p->setWeight(weight);
}

void NodeFrontEnd::connectOrientedNodes(_Node *n1, _Node *n2)
{
    auto p = reinterpret_cast<Edge *>(m_ss.updateInput(EventType::addOEdge));
    p->setNodeEndings(n1, n2);
}

void NodeFrontEnd::disconnectNodes(_Node *n1, _Node *n2)
{
    Nodes2ptr *pn = new Nodes2ptr{n1, n2};
    m_ss.updateInput(EventType::disconnectNodes, pn);
}

void NodeFrontEnd::setNodePosition(_Node *node, float x, float y)
{
    setNodePosition(node, sf::Vector2f(x, y));
}

void NodeFrontEnd::setNodePosition(_Node *node, sf::Vector2f vf)
{
    node->setPosition(vf);
}
