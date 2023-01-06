#include "Line.hpp"

using namespace nf;

Line::Line() : sf::VertexArray(sf::Lines, 2) {}

void Line::setIdxPosition(size_t idx, const sf::Vector2f& pos) {
    sf::VertexArray::operator[](idx).position = pos;
}

sf::Vertex Line::getIdxPosition(size_t idx) const {
    return sf::VertexArray::operator[](idx);
}
