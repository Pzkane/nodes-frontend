#ifndef SRC_ENTITIES__NODE_HPP_INCLUDED
#define SRC_ENTITIES__NODE_HPP_INCLUDED

/* Actual Node class implementation */

#include <list>
#include <string>
#include "CircleShape.hpp"
#include "EventFlags.hpp"
#include "Entity.hpp"
#include "Connector.hpp"

namespace nf {

class Connector;

const size_t DEF_NODE_RAD = 40;

class _Node : public Entity, public CircleShape
{
    bool m_is_dragged = false;
    sf::Text text;
    void updateText();
    std::list<_Node*> m_connected_nodes;

public:
    bool m_hovering;
    explicit _Node(float radius = 0, std::size_t pointCount = 30);
    explicit _Node(const _Node *node) {}
    ~_Node() = default;
    void update(sf::RenderWindow &window, EventFlags &ev);
    void draw(sf::RenderWindow &window);
    void setText(const std::string &text);
    void pushConnNode(_Node *const node);
    std::list<_Node*> getConnectedNodes() const;
};

};

#endif // SRC_ENTITIES__NODE_HPP_INCLUDED
