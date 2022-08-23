#ifndef SRC_ENTITIES_WEIGHTEDEDGE_HPP_INCLUDED
#define SRC_ENTITIES_WEIGHTEDEDGE_HPP_INCLUDED

#include "Edge.hpp"

namespace nf {

class WeightedEdge : public Edge
{
    float m_weight;
    sf::Text m_weight_label;
    void init();
public:
    WeightedEdge(sf::Color color = sf::Color::Black, float _weight = 0.f);
    WeightedEdge(_Node *const &start_node, _Node *const &end_node, sf::Color color = sf::Color::Black, float _weight = 0.f);
    ~WeightedEdge() = default;

    void update(const sf::RenderWindow &window, EventFlags &ef) override;
    void draw(sf::RenderWindow &window) override;
};

};

#endif // SRC_ENTITIES_WEIGHTEDEDGE_HPP_INCLUDED