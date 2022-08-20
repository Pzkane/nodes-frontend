#ifndef SRC_ENTITIES_NODE_HPP_INCLUDED
#define SRC_ENTITIES_NODE_HPP_INCLUDED

/* Node class abstraction as API */

#include "NodeFrontEnd.hpp"

namespace nf {

class Node
{
    _Node *m_node;
    NodeFrontEnd *m_api;
    void createNode();
public:
    Node(NodeFrontEnd &api);
    ~Node() = default;
    void setPosition(float x, float y);
};

};

#endif // SRC_ENTITIES_NODE_HPP_INCLUDED
