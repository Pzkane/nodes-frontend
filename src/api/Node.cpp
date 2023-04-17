#include <stdexcept>
#include <sstream>
#include "Node.hpp"
#include "Algorithms.hpp"

using namespace nf;

void Node::createNode(bool visible, NodeType type)
{
    m_node = m_api->addNode("API", m_api->m_ll_shift.x, m_api->m_ll_shift.y, visible, type);
}

void Node::checkHighlight() const {
    if (highlighted) {
        m_node->setOutlineThickness(LL_HIGHLIGHT_THICKNESS);
    }else{
        m_node->setOutlineThickness(LL_DEFAULT_THICKNESS);
    }
}

void Node::nodeSanityCheck() const {
    if (m_node == nullptr) {
        std::ostringstream err;
        err << "Node " << this << " already was destroyed!";
        throw std::runtime_error(err.str());
    }
}

Node::Node(NodeFrontEnd *api, NodeType type, bool visible) : m_api(api)
{
    createNode(visible, type);
}

void Node::setVisibility(const bool state) {
    nodeSanityCheck();
    m_node->setVisibility(state);
}

void Node::setPosition(float x, float y)
{
    nodeSanityCheck();
    // Set position and update starting position for all the shifts
    m_api->setNodePosition(m_node, x, y);
    m_api->m_ll_shift = {x,y};
    say("Pos")
    say(m_api->m_ll_shift)
}

void Node::setText(const std::string& label)
{
    nodeSanityCheck();
    m_node->setText(label);
}

const NodeImpl* const Node::getInnerNode() const
{
    nodeSanityCheck();
    return m_node;
}

const bool Node::isVisible() const {
    nodeSanityCheck();
    return m_node->isVisible();
}

Node& Node::operator=(const Node& node)
{
    nodeSanityCheck();
    if (&node == this)
        return *this;
    m_api->connectNodes(m_node, const_cast<NodeImpl*>(node.getInnerNode()));
    return *this;
}

void Node::destroy() {
    nodeSanityCheck();
    m_api->destroyNode(m_node);
    m_node = nullptr;
    m_destroyed = true;
}

void Node::highlight() {
    m_api->highlightNode(m_node);
}
