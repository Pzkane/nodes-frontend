#include "Connector.hpp"
#include "utils.hpp"

using namespace nf;

Connector::Connector(_Node *const &start_node, _Node *const &end_node, sf::Color color) : nodeRef({start_node, end_node})
{
    line[0].color = line[1].color = color;
}

sf::VertexArray &Connector::getDrawable()
{
    return line;
}

void Connector::update(const sf::RenderWindow &window, EventFlags &ef)
{
    if (nodeRef.start->enf.f_delete_self || nodeRef.end->enf.f_delete_self)
    {
        enf.f_delete_self = true;
    }

    // if (mouseInside(Utils::getMousePosf(window)))
    // {
    //     if (ef.f_lalt)
    //         enf.f_delete_self = true;
    // }

    line[0].position = nodeRef.start->getPosition();
    line[1].position = nodeRef.end->getPosition();
}
