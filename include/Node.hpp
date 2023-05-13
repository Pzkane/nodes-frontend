#ifndef SRC_API_NODE_HPP_INCLUDED
#define SRC_API_NODE_HPP_INCLUDED

/* Node class abstraction as API */

#include "NodeFrontEnd.hpp"
#include "Observable.hpp"

namespace nf {

class Node
{
protected:
    NodeImpl *m_node;
    NodeFrontEnd *m_api;
    bool m_destroyed = false;

    void createNode(bool visible, LayoutType type, Observable *observable);
    /**
     * Check if owned node pointer is valid
     * @throws std::runtime_error
    */
    void nodeSanityCheck() const;
    void checkHighlight() const;
    /**
     * Request API to highlight current node from mouse click
    */
    void select();
public:
    bool highlighted = false;

    Node(NodeFrontEnd *api, Observable *observable, LayoutType type = LayoutType::None, bool visible = true);
    virtual ~Node() = default;

    Node& operator=(const Node& node);

    /**
     * Set visibility state for node
     * @param state bool
    */
    void setVisibility(const bool state);
    void setPosition(float x, float y);
    void setText(const std::string& label);
    sf::Vector2f getPosition() const;
    const NodeImpl* const getInnerNode() const;
    const bool isVisible() const;
    /**
     * Destroy node
    */
    void destroy();
    /**
     * Request API to highlight current node (publicly available)
    */
    void highlight();
};

};

#endif // SRC_ENTITIES_NODE_HPP_INCLUDED
