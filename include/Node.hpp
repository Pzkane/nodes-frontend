#ifndef SRC_ENTITIES_NODE_HPP_INCLUDED
#define SRC_ENTITIES_NODE_HPP_INCLUDED

#include <list>
#include <string>
#include "CircleShape.hpp"
#include "EventFlags.hpp"
#include "Entity.hpp"
#include "Connector.hpp"

namespace nf {

class Connector;

class Node : public Entity, public CircleShape
{
    bool m_is_dragged = false;
    sf::Text text;
    void updateText();
    std::list<Node*> m_connected_nodes;

public:
    bool m_hovering;
    explicit Node(float radius = 0, std::size_t pointCount = 30);
    explicit Node(const Node *node) {}
    ~Node() = default;
    void update(sf::RenderWindow &window, EventFlags &ev);
    void draw(sf::RenderWindow &window);
    void setText(const std::string &text);
    void pushConnNode(Node *const node);
    std::list<Node*> getConnectedNodes() const;
};

};

#endif // SRC_ENTITIES_NODE_HPP_INCLUDED
