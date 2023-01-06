#ifndef SRC_SHAPES_LINE_HPP_INCLUDED
#define SRC_SHAPES_LINE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "AbstractShape.hpp"

namespace nf {

class Line : public sf::VertexArray, public AbstractShape
{
public:
    Line();
    virtual void setIdxPosition(size_t idx, const sf::Vector2f& pos);
    virtual sf::Vertex getIdxPosition(size_t idx) const;
};

};

#endif // SRC_SHAPES_LINE_HPP_INCLUDED
