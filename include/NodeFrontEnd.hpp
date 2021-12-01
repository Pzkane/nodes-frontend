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
    bool initizlized = false;
    LoopFlags lf;
    std::string title;
    sf::RenderWindow *window;
    Utils::SafeQueue<sf::Event> event_queue;
    std::thread *t_event_pool;
    sf::VideoMode video_mode;
    sf::Color m_backgroundColor = sf::Color::Black;
    SceneSwitcher ss;
    void cleanup();

public:
    NodeFrontEnd(const sf::VideoMode &video_mode, const char *title);
    NodeFrontEnd();
    ~NodeFrontEnd();
    void init();
    int launch();
    void setWindowColor(const sf::Color &color);
    Node *addNode(const char *text = "");
    bool isInit() { return initizlized; };
};

#endif // SRC_API_NODEFRONTEND_HPP_INCLUDED
