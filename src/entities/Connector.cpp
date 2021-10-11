#include "Connector.hpp"

Connector::Connector(sf::Color color) : line(sf::Lines, 2)
{
    line[0].color = color;
    line[1].color = color;
}

sf::VertexArray& Connector::getDrawable()
{
    return line;
}
