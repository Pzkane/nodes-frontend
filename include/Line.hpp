#ifndef SRC_SHAPES_LINE_HPP_INCLUDED
#define SRC_SHAPES_LINE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "AbstractShape.hpp"

namespace nf {

class Line : public sf::VertexArray, public AbstractShape
{
public:
    Line() : sf::VertexArray(sf::Lines, 2) {}
    ~Line() = default;
};

};

#endif // SRC_SHAPES_LINE_HPP_INCLUDED
