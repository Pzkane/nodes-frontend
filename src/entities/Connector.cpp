#include "Connector.hpp"

Connector::Connector(sf::Color color) : line(sf::Lines, 2)
{
    line[0].color = color;
    line[1].color = color;
}

void Connector::start(Node *const node)
{
    line[0].position = node->getPosition();
}

void Connector::end(Node *const node)
{
    line[1].position = node->getPosition();
}

sf::VertexArray& Connector::getDrawable()
{
    return line;
}
