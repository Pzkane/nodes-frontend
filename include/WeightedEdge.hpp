#ifndef SRC_ENTITIES_WEIGHTEDEDGE_HPP_INCLUDED
#define SRC_ENTITIES_WEIGHTEDEDGE_HPP_INCLUDED

#include "Edge.hpp"
#include "Label.hpp"

namespace nf {

class WeightedEdge : virtual public Edge
{
    float m_weight;
    Label m_weight_label;
    void init();
protected:
    void _draw(sf::RenderWindow &window, bool drawEdge);
    void _update(const sf::RenderWindow &window, EventFlags &ef, bool updateEdge);
public:
    WeightedEdge(sf::Color color = sf::Color::Black, float _weight = 0.f);
    WeightedEdge(NodeImpl *const &start_node, NodeImpl *const &end_node, sf::Color color = sf::Color::Black, float _weight = 0.f);
    ~WeightedEdge() = default;

    void setWeight(float weight);
    void update(const sf::RenderWindow &window, EventFlags &ef) override;
    void draw(sf::RenderWindow &window) override;
};

};

#endif // SRC_ENTITIES_WEIGHTEDEDGE_HPP_INCLUDED