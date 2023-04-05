#ifndef SRC_ENTITIES_EDGE_HPP_INCLUDED
#define SRC_ENTITIES_EDGE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "NodeImpl.hpp"
#include "Line.hpp"

namespace nf {

struct NodeRef
{
    NodeImpl *start = nullptr;
    NodeImpl *end = nullptr;
};

class Edge : public Entity, public Line
{
    void init(sf::Color color);
protected:
    NodeRef m_nodeRef;

    friend class NodeImpl;

public:
    explicit Edge(sf::Color color = sf::Color::Black);
    Edge(NodeImpl *const &start_node, NodeImpl *const &end_node, sf::Color color = sf::Color::Black);
    ~Edge() = default;
    void setNodeEndings(NodeImpl *const &start_node, NodeImpl *const &end_node);
    NodeRef& getNodeEndings() const;

    const sf::VertexArray& getDrawable() const;
    bool mouseInside(const sf::Vector2f &position) override;
    void update(const sf::RenderWindow &window, EventFlags &ef) override;
    void draw(sf::RenderWindow &window) override;
};

};

#endif // SRC_ENTITIES_EDGE_HPP_INCLUDED