#include "Connector.hpp"

Connector::Connector(Node *const &start_node, Node *const &end_node, sf::Color color) : line(sf::Lines, 2), nodeRef({start_node, end_node})
{
    line[0].color = color;
    line[1].color = color;
}

sf::VertexArray &Connector::getDrawable()
{
    return line;
}

void Connector::update()
{
    line[0].position = nodeRef.start->getPosition();
    line[1].position = nodeRef.end->getPosition();
}
