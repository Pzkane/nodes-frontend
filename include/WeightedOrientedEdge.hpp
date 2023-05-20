#ifndef SRC_ENTITIES_WEIGHTEDORIENTEDEDGE_HPP_INCLUDED
#define SRC_ENTITIES_WEIGHTEDORIENTEDEDGE_HPP_INCLUDED

#include "OrientedEdge.hpp"
#include "WeightedEdge.hpp"

namespace nf {

/**
 * @brief Represents merge of weighted and oriented connection between nodes
*/
class WeightedOrientedEdge : public WeightedEdge, public OrientedEdge
{
public:
    explicit WeightedOrientedEdge(sf::Color color = sf::Color::Black, float _weight = 0.f)
        : WeightedEdge(color, _weight) {}
    WeightedOrientedEdge(NodeImpl *const &start_node, NodeImpl *const &end_node, sf::Color color = sf::Color::Black, float _weight = 0.f)
        : WeightedEdge(start_node, end_node, color, _weight) {}

    void update(const sf::RenderWindow &window, EventFlags &ef) override;
    void draw(sf::RenderWindow &window) override;
};

};

#endif // SRC_ENTITIES_WEIGHTEDORIENTEDEDGE_HPP_INCLUDED