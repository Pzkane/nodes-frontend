#include <sstream>
#include "WeightedEdge.hpp"
#include "FontFlags.hpp"
#include "utils.hpp"

using namespace nf;

void WeightedEdge::init()
{
    m_weight_label.setFont(ff.font);
    std::stringstream ss;
    ss << m_weight;
    m_weight_label.setString(ss.str());
    m_weight_label.setFillColor(sf::Color::Black);
}

WeightedEdge::WeightedEdge(sf::Color color, float _weight) : m_weight(_weight), Edge(color)
{
    init();
}

WeightedEdge::WeightedEdge(_Node *const &start_node, _Node *const &end_node, sf::Color color, float _weight) : m_weight(_weight), Edge(start_node, end_node, color)
{
    init();
}

void WeightedEdge::update(const sf::RenderWindow &window, EventFlags &ef)
{
    if (!nodeRef.start || !nodeRef.end) return;
    Edge::update(window, ef);
    float min_x = line[0].position.x < line[1].position.x ? line[0].position.x : line[1].position.x,
          min_y = line[0].position.y < line[1].position.y ? line[0].position.y : line[1].position.y;
    float x = min_x + (abs(line[0].position.x - line[1].position.x) / 2),
          y = min_y + (abs(line[0].position.y - line[1].position.y) / 2);
    m_weight_label.setPosition(x, y);
}

void WeightedEdge::draw(sf::RenderWindow &window)
{
    if (!nodeRef.start || !nodeRef.end) return;
    Edge::draw(window);
    window.draw(m_weight_label);
}
