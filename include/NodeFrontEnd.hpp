#ifndef SRC_API_NODEFRONTEND_HPP_INCLUDED
#define SRC_API_NODEFRONTEND_HPP_INCLUDED

#include <thread>
#include <SFML/Graphics.hpp>
#include "LoopFlags.hpp"
#include "SceneSwitcher.hpp"
#include "NodeImpl.hpp"
#include "Algorithms.hpp"
#include "utils.hpp"
#include "Observable.hpp"
#include "Overlay.hpp"

namespace nf {

/**
 * Color and thickness of an outline and background during highlight/select
*/
extern sf::Color LL_HIGHLIGHT_COLOR;
extern sf::Color LL_SELECT_COLOR;
extern sf::Color LL_DEFAULT_COLOR;
extern float LL_HIGHLIGHT_THICKNESS;
extern const float LL_DEFAULT_THICKNESS;

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
    sf::Color m_backgroundColor = sf::Color(210, 210, 210);
    const Context m_settings;
    SceneSwitcher m_ss;
    NodeImpl *m_highlighted_node = nullptr
           , *m_selected_node = nullptr;

    void _cleanup();
public:
    /// Algorithm-specific values (public)
    // LinkedList shift properties
    static float PADDING;
    static size_t LL_NODE_SPACING;
    sf::Vector2f m_ll_shift = {PADDING, PADDING};

    // BinaryTree shift properties
    static size_t BT_PARENT_NODE_CENTER_OFFSET_X;
    static size_t BT_PARENT_NODE_CENTER_OFFSET_Y;

    // Graph shift properties
    static int RANDOM_SPACING;

    NodeFrontEnd(const Context& settings, const char *n_title);
    NodeFrontEnd() = delete;
    ~NodeFrontEnd();
    void init();
    int launch_and_loop();
    void setWindowColor(const sf::Color &color);
    const sf::RenderWindow * getWindow() { return m_window; }
    void setNodePosition(NodeImpl *node, float x, float y);
    void setNodePosition(NodeImpl *node, sf::Vector2f vf);
    /**
     * Reset padding for linked list
     * @param pad sf::Vector2f
    */
    void setLinkedListShiftPos(sf::Vector2f pad) { m_ll_shift = pad; }
    void setLinkedListHighlightThickness(float thickness) { LL_HIGHLIGHT_THICKNESS = thickness; }
    NodeImpl* addNode(const char *text = "", float x = 0, float y = 0, bool visible = true, LayoutType n_type = LayoutType::None, Observable *entity = nullptr);
    void connectNodes(NodeImpl *n1, NodeImpl *n2);
    void connectOrientedNodes(NodeImpl *n1, NodeImpl *n2);
    void connectWeightNodes(NodeImpl *n1, NodeImpl *n2, float weight = 0);
    void connectWeightOrientedNodes(NodeImpl *n1, NodeImpl *n2);
    void disconnectNodes(NodeImpl *n1, NodeImpl *n2);
    /**
     * Notify scene to destroy given node
     * @param n NodeImpl*
    */
    void destroyNode(NodeImpl *n);
    /**
     * Set or swap a single node to be highlighted
     * @param n NodeImpl*
    */
    void highlightNode(NodeImpl *n);
    /**
     * Set or swap a single node to be selected on mouse press
     * @param n NodeImpl*
    */
    void selectNode(NodeImpl *n);
    /**
     * Get currently selected node under the mouse pointer
    */
    NodeImpl* getSelectedNode();
    /**
     * @brief Determine if window and its internals were initialized
    */
    bool isInit() { return m_initizlized; };
    /**
     * Add new overlay section
    */
    void mergeOverlay(Overlay &child);
    /**
     * Remove overlay section from vector
    */
    // void divideOverlay(Overlay *child);
};

};

#endif // SRC_API_NODEFRONTEND_HPP_INCLUDED
