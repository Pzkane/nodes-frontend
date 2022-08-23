#include "Edge.hpp"
#include "utils.hpp"

using namespace nf;

void Edge::init(sf::Color color)
{
    line[0].color = line[1].color = color;
}

Edge::Edge(sf::Color color) : nodeRef({nullptr, nullptr})
{
    init(color);
}

Edge::Edge(_Node *const &start_node, _Node *const &end_node, sf::Color color) : nodeRef({start_node, end_node})
{
    init(color);
}

void Edge::setNodeEndings(_Node *const &start_node, _Node *const &end_node)
{
    nodeRef.start = start_node;
    nodeRef.end = end_node;
}

NodeRef& Edge::getNodeEndings() const
{
    return const_cast<NodeRef&>(nodeRef);
}

sf::VertexArray &Edge::getDrawable()
{
    return line;
}

void Edge::update(const sf::RenderWindow &window, EventFlags &ef)
{
    if (!nodeRef.start || !nodeRef.end) return;
    if (nodeRef.start->enf.f_delete_self || nodeRef.end->enf.f_delete_self)
        enf.f_delete_self = true;

    // if (mouseInside(Utils::getMousePosf(window)))
    // {
    //     if (ef.f_lalt)
    //         enf.f_delete_self = true;
    // }

    line[0].position = nodeRef.start->getPosition();
    line[1].position = nodeRef.end->getPosition();
}

void Edge::draw(sf::RenderWindow &window)
{
    if (!nodeRef.start || !nodeRef.end) return;
    window.draw(this->getDrawable());
}
