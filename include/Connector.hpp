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
    void start(Node *const node);
    void end(Node *const node);

    sf::VertexArray& getDrawable();
};

#endif // SRC_ENTITIES_CONNECTOR_HPP_INCLUDED