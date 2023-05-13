#include <sstream>
#include "WeightedEdge.hpp"
#include "FontFlags.hpp"
#include "utils.hpp"

using namespace nf;

void WeightedEdge::setWeight(float weight)
{
    m_weight = weight;
    std::stringstream ss;
    ss << m_weight;
    m_weight_label.setString(ss.str());
}

void WeightedEdge::init()
{
    m_weight_label.setFont(ff.font);
    setWeight(m_weight);
    m_weight_label.setFillColor(sf::Color::Black);
}

WeightedEdge::WeightedEdge(sf::Color color, float _weight) : m_weight(_weight), Edge(color)
{
    init();
}

WeightedEdge::WeightedEdge(NodeImpl *const &start_node, NodeImpl *const &end_node, sf::Color color, float _weight)
    : m_weight(_weight), Edge(start_node, end_node, color)
{
    init();
}

void WeightedEdge::_update(const sf::RenderWindow &window, EventFlags &ef, bool updateEdge)
{
    if (!m_nodeRef.start || !m_nodeRef.end) return;
    if (updateEdge)
        Edge::update(window, ef);
    auto idx0 = getIdxPosition(0);
    auto idx1 = getIdxPosition(1);
    float min_x = idx0.position.x < idx1.position.x ? idx0.position.x : idx1.position.x,
          min_y = idx0.position.y < idx1.position.y ? idx0.position.y : idx1.position.y;
    float x = min_x + (abs(idx0.position.x - idx1.position.x) / 2),
          y = min_y + (abs(idx0.position.y - idx1.position.y) / 2);
    m_weight_label.setPosition(x-15, y-20);
}

void WeightedEdge::_draw(sf::RenderWindow &window, bool drawEdge)
{
    if (!m_nodeRef.start || !m_nodeRef.end) return;
    if (drawEdge)
        Edge::draw(window);
    window.draw(m_weight_label.getBox());
    window.draw(m_weight_label);
}

void WeightedEdge::update(const sf::RenderWindow &window, EventFlags &ef) {
    _update(window, ef, true);
}

void WeightedEdge::draw(sf::RenderWindow &window) {
    _draw(window, true);
}