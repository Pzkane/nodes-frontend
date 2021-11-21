#ifndef SRC_API_NODEFRONTEND_HPP_INCLUDED
#define SRC_API_NODEFRONTEND_HPP_INCLUDED

#include <thread>

#include <SFML/Graphics.hpp>
#include "LoopFlags.hpp"
#include "SceneSwitcher.hpp"
#include "Node.hpp"
#include "utils.hpp"

class NodeFrontEnd
{
    LoopFlags lf;
    std::string title;
    sf::RenderWindow *window;
    Utils::SafeQueue<sf::Event> event_queue;
    std::thread *t_event_pool;
    sf::VideoMode video_mode;
    sf::Color m_backgroundColor = sf::Color::Black;
    SceneSwitcher ss;
    void init();

public:
    NodeFrontEnd(const sf::VideoMode &video_mode, const char *title);
    NodeFrontEnd();
    ~NodeFrontEnd();
    int launch();
    void setWindowColor(const sf::Color &color);
    Node *addNode(const char *text = "");
};

#endif // SRC_API_NODEFRONTEND_HPP_INCLUDED
