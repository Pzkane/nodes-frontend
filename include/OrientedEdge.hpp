#ifndef SRC_ENTITIES_ORIENTEDEDGE_HPP_INCLUDED
#define SRC_ENTITIES_ORIENTEDEDGE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Edge.hpp"

namespace nf {

class OrientedEdge : public Edge
{
    struct ArrowHead {
        sf::VertexArray left_line{sf::Lines, 2};
        sf::VertexArray right_line{sf::Lines, 2};
    };
    ArrowHead m_ahPos0, m_ahPos1;
public:
    bool m_2way = false;
    void update(const sf::RenderWindow &window, EventFlags &ef) override;
    void draw(sf::RenderWindow &window) override;
};

};

#endif // SRC_ENTITIES_ORIENTEDEDGE_HPP_INCLUDED