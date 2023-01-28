#include <cmath>
#include "Line.hpp"
#include "utils.hpp"

using namespace nf;

float distance(const sf::Vector2f& pt1, const sf::Vector2f& pt2) {
    return sqrt( pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2) );
}

Line::Line() : sf::VertexArray(sf::Lines, 2) {}

bool Line::inLine(const sf::Vector2f &position) {
    auto pt1 = this_vertex(0).position,
         pt2 = this_vertex(1).position;
    return static_cast<int>(distance(pt1, position) + distance(pt2, position)) == static_cast<int>(distance(pt1, pt2));
}

void Line::setIdxPosition(size_t idx, const sf::Vector2f& pos) {
    this_vertex(idx).position = pos;
}

sf::Vertex Line::getIdxPosition(size_t idx) const {
    return this_vertex(idx);
}
