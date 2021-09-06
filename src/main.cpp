#include <thread>
#include <iostream>
#include <queue>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "LoopFlags.hpp"

void event_pool(sf::Window &main_window, std::queue<sf::Event> &event_queue, bool &ep_done)
{
    while (true)
        while (!event_queue.empty())
        {
            auto event = event_queue.front();
            switch (event.type)
            {
            case sf::Event::Closed:
                ep_done = true;
                return;

            case sf::Event::KeyPressed:
                std::cout << "EVENT POOL::PRESS" << std::endl;
                break;

            case sf::Event::Resized:
                glViewport(0, 0, event.size.width, event.size.height);
                break;

            default:
                break;
            }
            event_queue.pop();
        }
}

int main()
{
    bool running = true;
    LoopFlags lf;
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    sf::Window window(sf::VideoMode(800, 60), "OpenGL Tree visualizer [ Pavels Zuravlovs ]", sf::Style::Default, settings);
    std::queue<sf::Event> event_queue;
    std::thread t_event_pool(event_pool, std::ref(window), std::ref(event_queue), std::ref(lf.f_t_ep_done));

    window.setFramerateLimit(75);
    window.setActive(true);

    while (running)
    {
        sf::Event event;
        if (window.pollEvent(event))
            event_queue.push(event);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        window.display();

        if (lf.switchedOff())
            running = false;
    }

    t_event_pool.join();

    return 0;
}
