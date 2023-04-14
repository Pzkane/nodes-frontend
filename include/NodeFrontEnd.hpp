#ifndef SRC_API_NODEFRONTEND_HPP_INCLUDED
#define SRC_API_NODEFRONTEND_HPP_INCLUDED

#include <thread>
#include <SFML/Graphics.hpp>
#include "LoopFlags.hpp"
#include "SceneSwitcher.hpp"
#include "NodeImpl.hpp"
#include "Algorithms.hpp"
#include "utils.hpp"

namespace nf {

/**
 * @brief API class for event dispatching
*/
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
    /// Algorithm-specific values (public)
    // LinkedList shift properties
    static const size_t PADDING = 50;
    static const size_t LL_NODE_SPACING = 150;
    sf::Vector2f m_ll_shift = {PADDING, PADDING};

    NodeFrontEnd(const Context& settings, const char *n_title);
    NodeFrontEnd() = delete;
    ~NodeFrontEnd();
    void init();
    int launch_and_loop();
    void setWindowColor(const sf::Color &color);
    void setNodePosition(NodeImpl *node, float x, float y);
    void setNodePosition(NodeImpl *node, sf::Vector2f vf);
    /**
     * Reset padding for linked list
     * @param pad sf::Vector2f
    */
    void setLinkedListShiftPos(sf::Vector2f pad) { m_ll_shift = pad; }
    NodeImpl* addNode(const char *text = "", float x = 0, float y = 0, bool visible = true, NodeType n_type = NodeType::Generic);
    void connectNodes(NodeImpl *n1, NodeImpl *n2);
    void connectOrientedNodes(NodeImpl *n1, NodeImpl *n2);
    void connectWeightNodes(NodeImpl *n1, NodeImpl *n2, float weight = 0);
    void disconnectNodes(NodeImpl *n1, NodeImpl *n2);
    /**
     * Notify scene to destroy given node
     * @param n NodeImpl*
    */
    void destroyNode(NodeImpl *n);
    bool isInit() { return m_initizlized; };
};

};

#endif // SRC_API_NODEFRONTEND_HPP_INCLUDED
