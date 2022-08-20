#include "Node.hpp"

using namespace nf;

void Node::createNode()
{
    m_node = m_api->addNode("API");
}

Node::Node(NodeFrontEnd &api) : m_api(&api)
{
    createNode();
}

void Node::setPosition(float x, float y)
{
    m_api->setNodePosition(m_node, x, y);
}
