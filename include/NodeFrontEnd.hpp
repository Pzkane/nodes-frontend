#ifndef SRC_API_NODEFRONTEND_HPP_INCLUDED
#define SRC_API_NODEFRONTEND_HPP_INCLUDED

#include <thread>
#include <SFML/Graphics.hpp>
#include "LoopFlags.hpp"
#include "SceneSwitcher.hpp"
#include "_Node.hpp"
#include "utils.hpp"

namespace nf {

class NodeFrontEnd
{
    bool m_initizlized = false;
    std::string m_title;
    sf::RenderWindow *m_window;
    Utils::SafeQueue<sf::Event> m_eventQueue;
    std::thread *m_thEventPool;
    sf::VideoMode m_videoMode;
    sf::Color m_backgroundColor = sf::Color::Black;
    SceneSwitcher m_ss;
    void _cleanup();

public:
    NodeFrontEnd(const sf::VideoMode &video_mode, const char *n_title);
    NodeFrontEnd() {}
    ~NodeFrontEnd();
    void init();
    int launch();
    void setWindowColor(const sf::Color &color);
    void setNodePosition(_Node *node, float x, float y);
    void setNodePosition(_Node *node, sf::Vector2f vf);
    _Node *addNode(const char *text = "");
    bool isInit() { return m_initizlized; };
};

};

#endif // SRC_API_NODEFRONTEND_HPP_INCLUDED
