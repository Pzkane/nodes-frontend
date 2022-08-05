#include "NodeFrontEnd.hpp"

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "MainScene.hpp"
#include "EventType.hpp"

using namespace nf;

template <typename Tw>
static void event_pool(Tw &main_window, Utils::SafeQueue<sf::Event> &event_queue, SceneSwitcher &ss, LoopFlags &flags)
{
    while (!flags.f_t_ep_done)
        while (event_queue.size())
        {
            auto event = event_queue.front();
            ss.updateInput(event);
            switch (event.type)
            {
            case sf::Event::Closed:
                flags.f_t_delete_active_scene = true;
                break;

            case sf::Event::Resized:
            {
                glViewport(0, 0, event.size.width, event.size.height);
                sf::View new_view(sf::FloatRect(0, 0, event.size.width, event.size.height));
                main_window.setView(new_view);
                break;
            }

            default:
                break;
            }
            event_queue.pop();
        }
}

void NodeFrontEnd::init()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    window = new sf::RenderWindow(video_mode, title, sf::Style::Default, settings);
    MainScene *main_scene = new MainScene(*window);
    ss.switchTo(main_scene);
    t_event_pool = new std::thread(event_pool<sf::RenderWindow>, std::ref(*window), std::ref(event_queue), std::ref(ss), std::ref(lf));
    initizlized = true;
}

int NodeFrontEnd::launch()
{
    bool running = true;

    window->setFramerateLimit(75);
    window->setActive(true);

    while (running)
    {
        sf::Event event;
        if (window->pollEvent(event))
            event_queue.push(event);

        if (lf.f_t_delete_active_scene)
        {
            ss.deleteCurrScene();
            lf.f_t_delete_active_scene = false;
            lf.f_t_ep_done = true;
        }

        ss.updateScene();
        ss.drawScene();
        window->display();
        window->clear(m_backgroundColor);

        if (lf.switchedOff())
            running = false;
    }

    t_event_pool->join();
    cleanup();

    return 0;
}

NodeFrontEnd::NodeFrontEnd() : video_mode(sf::VideoMode(800, 500)), title("OpenGL Front End [ Pavels Zuravlovs ]")
{
}

NodeFrontEnd::NodeFrontEnd(const sf::VideoMode &video_mode, const char *title) : video_mode(video_mode), title(title)
{
}

NodeFrontEnd::~NodeFrontEnd()
{
    cleanup();
}

void NodeFrontEnd::cleanup()
{
    if (window)
    {
        delete window;
        window = nullptr;
    }
}

void NodeFrontEnd::setWindowColor(const sf::Color &color)
{
    m_backgroundColor = color;
}

Node *NodeFrontEnd::addNode(const char *text)
{
    auto p = reinterpret_cast<Node *>(ss.updateInput(EventType::addNode));
    p->setText(text);
    return p;
}
