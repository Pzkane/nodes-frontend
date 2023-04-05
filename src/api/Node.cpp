#include "Node.hpp"
#include "Algorithms.hpp"

using namespace nf;

void Node::createNode()
{
    m_node = m_api->addNode("API", m_api->m_ll_shift.x, m_api->m_ll_shift.y, NodeType::LinkedList);
}

Node::Node(NodeFrontEnd *api) : m_api(api)
{
    createNode();
}

void Node::setPosition(float x, float y)
{
    // Set position and update starting position for all the shifts
    m_api->setNodePosition(m_node, x, y);
    m_api->m_ll_shift = {x,y};
    say("Pos")
    say(m_api->m_ll_shift)
}

void Node::setText(const std::string& label)
{
    m_node->setText(label);
}

const NodeImpl* const Node::getInnerNode() const
{
    return m_node;
}

Node& Node::operator=(const Node& node)
{
    if (&node == this)
        return *this;
    m_api->connectNodes(m_node, const_cast<NodeImpl*>(node.getInnerNode()));
    return *this;
}

