#ifndef SRC_ENTITIES__NODE_HPP_INCLUDED
#define SRC_ENTITIES__NODE_HPP_INCLUDED

/* Actual Node class implementation */

#include <list>
#include <string>
#include "CircleShape.hpp"
#include "EventFlags.hpp"
#include "Entity.hpp"
#include "Edge.hpp"

namespace nf {

class Edge;

const size_t DEF_NODE_RAD = 40;

class _Node : public Entity, public CircleShape
{
    static unsigned id;
    bool m_is_dragged = false;
    sf::Text m_text;
    void updateText();
    std::list<_Node*> m_connected_nodes;

public:
    bool m_hovering;
    explicit _Node(float radius = 0, std::size_t pointCount = 30);
    ~_Node() = default;
    void update(const sf::RenderWindow &window, EventFlags &ev) override;
    void draw(sf::RenderWindow &window) override;

    void setText(const std::string &text);
    void setTextColor(const sf::Color& clr);
    void pushConnNode(_Node *const node);
    std::list<_Node*> getConnectedNodes() const;
};

struct Nodes2ptr {
    _Node* n1;
    _Node* n2;
};

};

#endif // SRC_ENTITIES__NODE_HPP_INCLUDED
