#ifndef SRC_ENTITIES_NODE_HPP_INCLUDED
#define SRC_ENTITIES_NODE_HPP_INCLUDED

#include <vector>
#include "CircleShape.hpp"
#include "EventFlags.hpp"
#include "Connector.hpp"

class Connector;

class Node : public CircleShape
{
    bool m_is_dragged = false;
    struct ConnectorRef
    {
        Connector *conn = nullptr;
        sf::Vertex *p_connector_end = nullptr;
    };
    
    std::vector<ConnectorRef> m_connectors;

public:
    explicit Node(float radius = 0, std::size_t pointCount = 30);
    Node(const Node *node) {}
    ~Node();
    Connector* connectTo(Node *const p_node);
    void update(const sf::RenderWindow &window, EventFlags &ev);
};

#endif // SRC_ENTITIES_NODE_HPP_INCLUDED
