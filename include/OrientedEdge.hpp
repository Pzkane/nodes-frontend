#ifndef SRC_ENTITIES_ORIENTEDEDGE_HPP_INCLUDED
#define SRC_ENTITIES_ORIENTEDEDGE_HPP_INCLUDED

#include "Edge.hpp"

namespace nf {

/**
 * @brief Represents oriented connection between nodes
*/
class OrientedEdge : virtual public Edge
{
    struct ArrowHead {
        sf::VertexArray left_line{sf::Lines, 2};
        sf::VertexArray right_line{sf::Lines, 2};
    };
    ArrowHead m_ahPos0, m_ahPos1;
protected:
    void _draw(sf::RenderWindow &window, bool drawEdge);
    void _update(const sf::RenderWindow &window, EventFlags &ef, bool updateEdge);
public:
    explicit OrientedEdge(sf::Color color = sf::Color::Black) : Edge(color) {}
    OrientedEdge(NodeImpl *const &start_node, NodeImpl *const &end_node, sf::Color color = sf::Color::Black)
        : Edge(start_node, end_node, color) {}

    /**
     * Flip this to draw two-way connection
    */
    bool m_2way = false;
    void update(const sf::RenderWindow &window, EventFlags &ef) override;
    void draw(sf::RenderWindow &window) override;
};

};

#endif // SRC_ENTITIES_ORIENTEDEDGE_HPP_INCLUDED