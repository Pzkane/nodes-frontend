#ifndef SRC_API_NODEFRONTEND_HPP_INCLUDED
#define SRC_API_NODEFRONTEND_HPP_INCLUDED

#include <thread>
#include <SFML/Graphics.hpp>
#include "LoopFlags.hpp"
#include "SceneSwitcher.hpp"
#include "_Node.hpp"
#include "utils.hpp"

namespace nf {

struct Context : public sf::ContextSettings {
    sf::VideoMode m_videoMode;
    explicit Context(sf::VideoMode video, sf::ContextSettings context = sf::ContextSettings())
        : m_videoMode(video), sf::ContextSettings(context) {}
    Context() : Context(sf::VideoMode{}, sf::ContextSettings{}) {}
};

class NodeFrontEnd
{
    bool m_initizlized = false;
    std::string m_title;
    sf::RenderWindow *m_window;
    Utils::SafeQueue<sf::Event> m_eventQueue;
    std::thread *m_thEventPool;
    sf::Color m_backgroundColor = sf::Color::Black;
    const Context m_settings;
    SceneSwitcher m_ss;
    void _cleanup();

public:
    NodeFrontEnd(const Context& settings, const char *n_title);
    NodeFrontEnd() = delete;
    ~NodeFrontEnd();
    void init();
    int launch_and_loop();
    void setWindowColor(const sf::Color &color);
    void setNodePosition(_Node *node, float x, float y);
    void setNodePosition(_Node *node, sf::Vector2f vf);
    _Node* addNode(const char *text = "", float x = 0, float y = 0);
    void connectNodes(_Node *n1, _Node *n2);
    void connectOrientedNodes(_Node *n1, _Node *n2);
    void connectWeightNodes(_Node *n1, _Node *n2, float weight = 0);
    void disconnectNodes(_Node *n1, _Node *n2);
    bool isInit() { return m_initizlized; };
};

};

#endif // SRC_API_NODEFRONTEND_HPP_INCLUDED
