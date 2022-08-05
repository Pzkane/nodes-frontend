#ifndef SRC_ENTITIES_CONNECTOR_HPP_INCLUDED
#define SRC_ENTITIES_CONNECTOR_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include "Line.hpp"

namespace nf {

class Connector : public Entity, public Line
{
    Line line;
    struct NodeRef
    {
        Node *start = nullptr;
        Node *end = nullptr;
    };

    NodeRef nodeRef;

    friend class Node;

public:
    Connector(Node *const &start_node, Node *const &end_node, sf::Color color = sf::Color::White);
    ~Connector() = default;

    sf::VertexArray &getDrawable();
    void update(const sf::RenderWindow &window, EventFlags &ef);
};

};

#endif // SRC_ENTITIES_CONNECTOR_HPP_INCLUDED