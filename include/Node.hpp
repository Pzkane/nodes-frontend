#ifndef SRC_ENTITIES_NODE_HPP_INCLUDED
#define SRC_ENTITIES_NODE_HPP_INCLUDED

#include <vector>
#include <string>
#include "CircleShape.hpp"
#include "EventFlags.hpp"
#include "Connector.hpp"

class Connector;

class Node : public CircleShape
{
    bool m_is_dragged = false;
    sf::Text text;

public:
    explicit Node(float radius = 0, std::size_t pointCount = 30);
    explicit Node(const Node *node) {}
    ~Node() = default;
    void update(const sf::RenderWindow &window, EventFlags &ev);
    void draw(sf::RenderWindow &window);
    void setText(const std::string &text);
};

#endif // SRC_ENTITIES_NODE_HPP_INCLUDED
