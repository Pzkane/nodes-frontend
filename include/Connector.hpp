#ifndef SRC_ENTITIES_CONNECTOR_HPP_INCLUDED
#define SRC_ENTITIES_CONNECTOR_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Node.hpp"

class Connector
{
    sf::VertexArray line;

    friend class Node;
public:
    Connector(sf::Color color = sf::Color::White);
    ~Connector() = default;

    sf::VertexArray& getDrawable();
};

#endif // SRC_ENTITIES_CONNECTOR_HPP_INCLUDED