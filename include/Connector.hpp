#ifndef SRC_ENTITIES_CONNECTOR_HPP_INCLUDED
#define SRC_ENTITIES_CONNECTOR_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "_Node.hpp"
#include "Line.hpp"

namespace nf {

class Connector : public Entity, public Line
{
    Line line;
    struct NodeRef
    {
        _Node *start = nullptr;
        _Node *end = nullptr;
    };

    NodeRef nodeRef;

    friend class _Node;

public:
    Connector(_Node *const &start_node, _Node *const &end_node, sf::Color color = sf::Color::White);
    ~Connector() = default;

    sf::VertexArray &getDrawable();
    void update(const sf::RenderWindow &window, EventFlags &ef);
};

};

#endif // SRC_ENTITIES_CONNECTOR_HPP_INCLUDED