#ifndef SRC_ENTITIES_NODEIMPL_HPP_INCLUDED
#define SRC_ENTITIES_NODEIMPL_HPP_INCLUDED

/* Actual Node class implementation */

#include <list>
#include <string>
#include "CircleShape.hpp"
#include "EventFlags.hpp"
#include "Entity.hpp"
#include "Edge.hpp"
#include "Clickable.hpp"

namespace nf {

/* Forward declaration */
class Edge;

const size_t DEF_NODE_RAD = 40;

/**
 * Internal Node implementation
*/
class NodeImpl : public Entity, public CircleShape, public Clickable<VoidCallback>
{
    static unsigned id;
    bool m_isDragged = false,
         m_isVisible = true,
         m_destroy = false;
    sf::Text m_text;
    std::list<NodeImpl*> m_connected_nodes;

    void updateText();
public:
    const float RADIUS;
    bool m_hovering;
    explicit NodeImpl(float radius = 0, std::size_t pointCount = 30, const std::size_t ms = 50);
    ~NodeImpl() = default;
    void update(const sf::RenderWindow &window, EventFlags &ef) override;
    void draw(sf::RenderWindow &window) override;

    /**
     * Set visibility state for node
     * @param state bool
    */
    void setVisibility(const bool state);
    void setText(const std::string &text);
    void setTextColor(const sf::Color& clr);
    /**
     * Register node into list of edge connected nodes
     * @param node NodeImpl *const
    */
    void pushConnNode(NodeImpl *const node);
    /**
     * Return list of edge connected nodes
     * @returns std::list<NodeImpl*> Reference to a list
    */
    const std::list<NodeImpl*>& getConnectedNodes() const;
    /**
     * Get visiblity state
     * @returns bool
    */
    bool isVisible() const;
    /**
     * Mark node for destruction for next update cycle
    */
    void destroy();
};

struct Nodes2ptr {
    NodeImpl* n1;
    NodeImpl* n2;
};

};

#endif // SRC_ENTITIES_NODEIMPL_HPP_INCLUDED
