#ifndef SRC_API_NODE_HPP_INCLUDED
#define SRC_API_NODE_HPP_INCLUDED

/* Node class abstraction as API */

#include "NodeFrontEnd.hpp"

namespace nf {

class Node
{
protected:
    NodeImpl *m_node;
    NodeFrontEnd *m_api;

    void createNode(bool visible);
    /**
     * Check if owned node pointer is valid
     * @throws std::runtime_error
    */
    void nodeSanityCheck() const;
    void checkHighlight() const;
protected:
    bool m_destroyed = false;
public:
    bool highlighted = false;

    Node(NodeFrontEnd *api, bool visible = true);
    ~Node() = default;

    Node& operator=(const Node& node);

    /**
     * Set visibility state for node
     * @param state bool
    */
    void setVisibility(const bool state);
    void setPosition(float x, float y);
    void setText(const std::string& label);
    const NodeImpl* const getInnerNode() const;
    const bool isVisible() const;
    /**
     * Destroy node
    */
    void destroy();
    /**
     * Request API to highlight current node
    */
    void highlight();
};

};

#endif // SRC_ENTITIES_NODE_HPP_INCLUDED
