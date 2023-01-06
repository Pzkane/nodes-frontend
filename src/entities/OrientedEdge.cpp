#include <cmath>
#include "OrientedEdge.hpp"
#include "utils.hpp"

using namespace nf;

void OrientedEdge::update(const sf::RenderWindow &window, EventFlags &ef) {
    if (!m_nodeRef.start || !m_nodeRef.end) return;
    Edge::update(window, ef);
    sf::Vector2f xAxisVec = {1, 0},
                 edgeVec  = {m_nodeRef.start->getPosition().x - m_nodeRef.end->getPosition().x,
                             m_nodeRef.start->getPosition().y - m_nodeRef.end->getPosition().y};
    float edgeMag = sqrt(pow(edgeVec.x, 2) + pow(edgeVec.y, 2));
    float angleDeg = acos(-(
                        (edgeVec.x*xAxisVec.x + edgeVec.y*xAxisVec.y)
                                                                /
                        (edgeMag * sqrt(pow(xAxisVec.x, 2) + pow(xAxisVec.y, 2)))
                    )) * radian;
    say(std::to_string(angleDeg) + " s " + std::to_string(angleDeg+45));
    float leftLineRad  = (angleDeg+45) / radian,
          rightLineRad = (angleDeg-45) / radian;
    sf::Vector2f leftLineTerminalCoord  = {edgeMag * cos(leftLineRad), edgeMag * sin(leftLineRad)},
                 rightLineTerminalCoord = {edgeMag * cos(rightLineRad), edgeMag * sin(rightLineRad)};

    m_ah.left_line[0].color = this_vertex(0).color;
    m_ah.left_line[1].color = this_vertex(1).color;
    auto pos = m_nodeRef.end->getPosition();
    m_ah.left_line[0].position = leftLineTerminalCoord;
    m_ah.left_line[1].position = pos;


    // setIdxPosition(0, m_nodeRef.start->getPosition());
    // setIdxPosition(1, m_nodeRef.end->getPosition());

}

void OrientedEdge::draw(sf::RenderWindow &window) {
    if (!m_nodeRef.start || !m_nodeRef.end) return;
    Edge::draw(window);
    window.draw(m_ah.left_line);
    window.draw(m_ah.right_line);
}

