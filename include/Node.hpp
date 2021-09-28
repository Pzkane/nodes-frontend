#ifndef SRC_PROPERTIES_NODE_HPP_INCLUDED
#define SRC_PROPERTIES_NODE_HPP_INCLUDED

#include "CircleShape.hpp"

class Node : public CircleShape
{
    bool m_is_dragged = false;

public:
    explicit Node(float radius = 0, std::size_t pointCount = 30) : CircleShape(radius, pointCount) {}
    Node(const Node *node) {}
    ~Node() = default;
    void update(const sf::RenderWindow &window);
};

#endif // SRC_PROPERTIES_NODE_HPP_INCLUDED
