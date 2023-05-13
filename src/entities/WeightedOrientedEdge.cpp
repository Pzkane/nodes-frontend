#include "WeightedOrientedEdge.hpp"

using namespace nf;

void WeightedOrientedEdge::update(const sf::RenderWindow &window, EventFlags &ef) {
    WeightedEdge::_update(window, ef, true);
    OrientedEdge::_update(window, ef, true);
}

void WeightedOrientedEdge::draw(sf::RenderWindow &window) {
    WeightedEdge::_draw(window, true);
    OrientedEdge::_draw(window, true);
}