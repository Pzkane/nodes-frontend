#include "NodeFrontEnd.hpp"

#include <thread>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "LoopFlags.hpp"
#include "SceneSwitcher.hpp"
#include "MainScene.hpp"
#include "utils.hpp"

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

int NodeFrontEnd::init(const sf::VideoMode &video_mode, const char *title)
{
    bool running = true;
    LoopFlags lf;
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    sf::RenderWindow window(video_mode, title, sf::Style::Default, settings);
    Utils::SafeQueue<sf::Event> event_queue;

    window.setFramerateLimit(75);
    window.setActive(true);

    SceneSwitcher ss;
    MainScene *main_scene = new MainScene(window);
    ss.switchTo(main_scene);

    std::thread t_event_pool(event_pool<sf::RenderWindow>, std::ref(window), std::ref(event_queue), std::ref(ss), std::ref(lf));
    while (running)
    {
        sf::Event event;
        if (window.pollEvent(event))
            event_queue.push(event);

        if (lf.f_t_delete_active_scene)
        {
            delete main_scene;
            main_scene = nullptr;
            ss.unsetScene();
            lf.f_t_delete_active_scene = false;
            lf.f_t_ep_done = true;
        }

        ss.updateScene();
        ss.drawScene();
        window.display();
        window.clear(m_backgroundColor);

        if (lf.switchedOff())
            running = false;
    }

    t_event_pool.join();

    return 0;
}

NodeFrontEnd::NodeFrontEnd()
{
    init(sf::VideoMode(800, 500), "OpenGL Front End [ Pavels Zuravlovs ]");
}

NodeFrontEnd::NodeFrontEnd(const sf::VideoMode &video_mode, const char *title)
{
    init(video_mode, title);
}

void NodeFrontEnd::setWindowColor(const sf::Color &color)
{
    m_backgroundColor = color;
}