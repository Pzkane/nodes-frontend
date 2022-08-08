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
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    m_videoMode.width = 800;
    m_videoMode.height = 640;
    m_window = new sf::RenderWindow(m_videoMode, m_title, sf::Style::Default, settings);
    MainScene *m_mainScene = new MainScene(*m_window);
    m_ss.switchTo(m_mainScene);
    m_thEventPool = new std::thread(event_pool<sf::RenderWindow>, std::ref(*m_window), std::ref(m_eventQueue), std::ref(m_ss), std::ref(lf));
    m_initizlized = true;
    say("frontend initialized");
}

int NodeFrontEnd::launch()
{
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
    _cleanup();

    return 0;
}

NodeFrontEnd::~NodeFrontEnd()
{
    _cleanup();
}

void NodeFrontEnd::_cleanup()
{
    if (m_thEventPool)
    {
        delete m_thEventPool;
        m_thEventPool = nullptr;
    }
    if (m_window)
    {
        delete m_window;
        m_window = nullptr;
    }
}

void NodeFrontEnd::setWindowColor(const sf::Color &color)
{
    m_backgroundColor = color;
}

Node *NodeFrontEnd::addNode(const char *text)
{
    auto p = reinterpret_cast<Node *>(m_ss.updateInput(EventType::addNode));
    p->setText(text);
    return p;
}
