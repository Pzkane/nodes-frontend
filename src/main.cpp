#include <thread>
#include <iostream>
#include <queue>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "LoopFlags.hpp"

template <typename Tw>
void event_pool(Tw &main_window, std::queue<sf::Event> &event_queue, bool &ep_done)
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
                std::cout << "EVENT POOL::KEYPRESS ";
                switch (event.key.code)
                {
                case sf::Keyboard::A:
                    std::cout << "'A'";
                    glRotatef(30, 0, 0, 0);
                    break;

                case sf::Keyboard::D:
                    std::cout << "'D'";
                    break;

                case sf::Keyboard::R:
                    std::cout << "'R'";
                    glLoadIdentity();
                    break;

                default:
                    break;
                }
                std::cout << std::endl;
                break;

            case sf::Event::MouseButtonPressed:
                std::cout << "EVENT POOL::MOUSEPRESS" << std::endl;
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
    sf::RenderWindow window(sf::VideoMode(800, 500), "OpenGL Tree visualizer [ Pavels Zuravlovs ]", sf::Style::Default, settings);
    std::queue<sf::Event> event_queue;
    std::thread t_event_pool(event_pool<sf::RenderWindow>, std::ref(window), std::ref(event_queue), std::ref(lf.f_t_ep_done));

    window.setFramerateLimit(75);
    window.setActive(true);

    sf::CircleShape gr_node(50);
    gr_node.setFillColor(sf::Color::Red);
    gr_node.setPosition(sf::Vector2f(50, 50));

    while (running)
    {
        sf::Event event;
        if (window.pollEvent(event))
            event_queue.push(event);

        // Prepare for drawing
        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //select projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 800, 0, 600, 0, 1); //choose an orthographic projection
                                       //same size as window
                                       //coordinates will have a 1-1 correspondance with pixels

        //draw a green triangle
        glColor3d(0, 1, 0);
        glBegin(GL_TRIANGLES);
        glVertex2d(0, 0);
        glVertex2d(400, 0);
        glVertex2d(400, 300);
        glRotatef(30, 0, 0, 0);
        glEnd();

        glPushMatrix();
        glTranslatef(250, 250, 0.0);   // 3. Translate to the object's position.
        glRotatef(30, 0.0, 0.0, 1.0);  // 2. Rotate the object.
        glTranslatef(-250, -250, 0.0); // 1. Translate to the origin.

        //draw an orange triangle
        glColor3d(1, 0.5, 0);
        glBegin(GL_TRIANGLES);
        glVertex2d(0, 0);
        glVertex2d(400, 0);
        glVertex2d(400, 300);
        glRotatef(30, 0, 0, 0);
        glEnd();

        glPopMatrix();

        glPushMatrix();
        window.resetGLStates();

        sf::CircleShape cs(50);
        cs.setFillColor(sf::Color::Red);
        cs.setPosition(sf::Vector2f(50.f, 50.f));

        window.draw(cs);
        glPopMatrix();

        window.display();

        if (lf.switchedOff())
            running = false;
    }

    t_event_pool.join();

    return 0;
}
