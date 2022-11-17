#include "Node.hpp"

using namespace nf;

void Node::createNode()
{
    m_node = m_api->addNode("API");
}

Node::Node(NodeFrontEnd *api) : m_api(api)
{
    createNode();
}

void Node::setPosition(float x, float y)
{
    m_api->setNodePosition(m_node, x, y);
}

const _Node* const Node::getInnerNode() const
{
    return m_node;
}

Node& Node::operator=(const Node& node)
{
    if (&node == this)
        return *this;
    m_api->connectNodes(m_node, const_cast<_Node*>(node.getInnerNode()));
    return *this;
}

