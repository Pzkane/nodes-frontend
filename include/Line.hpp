#ifndef SRC_SHAPES_LINE_HPP_INCLUDED
#define SRC_SHAPES_LINE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "AbstractShape.hpp"

#define this_vertex(idx) sf::VertexArray::operator[](idx)

namespace nf {

/**
 * @brief Visible line object. Used for edges
*/
class Line : public sf::VertexArray, public AbstractShape
{
public:
    Line();
    bool inLine(const sf::Vector2f &position);
    /**
     * Set position for one of the line edges (0 or 1)
     * @param idx size_t
     * @param pos sf::Vector2f&
    */
    virtual void setIdxPosition(size_t idx, const sf::Vector2f& pos);
    /**
     * Get position of one of the line edges (0 or 1)
     * @param idx size_t
    */
    virtual sf::Vertex getIdxPosition(size_t idx) const;
};

};

#endif // SRC_SHAPES_LINE_HPP_INCLUDED
