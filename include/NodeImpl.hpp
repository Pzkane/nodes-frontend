#ifndef SRC_ENTITIES_NODEIMPL_HPP_INCLUDED
#define SRC_ENTITIES_NODEIMPL_HPP_INCLUDED

/* Actual Node class implementation */

#include <list>
#include <string>
#include "CircleShape.hpp"
#include "EventFlags.hpp"
#include "Entity.hpp"
#include "Edge.hpp"

namespace nf {

/* Forward declaration */
class Edge;

const size_t DEF_NODE_RAD = 40;

/**
 * Internal Node implementation
*/
class NodeImpl : public Entity, public CircleShape
{
    static unsigned id;
    bool m_is_dragged = false,
         m_isVisible = true,
         m_destroy = false;
    sf::Text m_text;
    std::list<NodeImpl*> m_connected_nodes;

    void updateText();
public:
    const float RADIUS;
    bool m_hovering;
    explicit NodeImpl(float radius = 0, std::size_t pointCount = 30);
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
    void pushConnNode(NodeImpl *const node);
    const std::list<NodeImpl*>& getConnectedNodes() const;
    /**
     * Get visiblity state
     * @returns bool
    */
    bool isVisible() const;
    /**
     * Mark node for destruction for following render cycle
    */
    void destroy();
};

struct Nodes2ptr {
    NodeImpl* n1;
    NodeImpl* n2;
};

};

#endif // SRC_ENTITIES_NODEIMPL_HPP_INCLUDED
