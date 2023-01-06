#include "Edge.hpp"
#include "utils.hpp"

using namespace nf;

void Edge::init(sf::Color color)
{
    this_vertex(0).color = this_vertex(1).color = color;
}

Edge::Edge(sf::Color color) : m_nodeRef({nullptr, nullptr})
{
    init(color);
}

Edge::Edge(_Node *const &start_node, _Node *const &end_node, sf::Color color) : m_nodeRef({start_node, end_node})
{
    init(color);
}

void Edge::setNodeEndings(_Node *const &start_node, _Node *const &end_node)
{
    m_nodeRef.start = start_node;
    m_nodeRef.end = end_node;
}

NodeRef& Edge::getNodeEndings() const
{
    return const_cast<NodeRef&>(m_nodeRef);
}

const sf::VertexArray& Edge::getDrawable() const
{
    return *this;
}

void Edge::update(const sf::RenderWindow &window, EventFlags &ef)
{
    if (!m_nodeRef.start || !m_nodeRef.end) return;
    if (m_nodeRef.start->enf.f_delete_self || m_nodeRef.end->enf.f_delete_self)
        enf.f_delete_self = true;

    // if (mouseInside(Utils::getMousePosf(window)))
    // {
    //     if (ef.f_lalt)
    //         enf.f_delete_self = true;
    // }

    setIdxPosition(0, m_nodeRef.start->getPosition());
    setIdxPosition(1, m_nodeRef.end->getPosition());
}

void Edge::draw(sf::RenderWindow &window)
{
    if (!m_nodeRef.start || !m_nodeRef.end) return;
    window.draw(this->getDrawable());
}
