#include <cmath>
#include <utility>
#include "OrientedEdge.hpp"
#include "utils.hpp"

using namespace nf;

void OrientedEdge::update(const sf::RenderWindow &window, EventFlags &ef) {
    if (!m_nodeRef.start || !m_nodeRef.end) return;
    Edge::update(window, ef);

    // Explanation: https://www.codeproject.com/Articles/3274/Drawing-Arrows
    sf::Vector2f primaryVec  = { m_nodeRef.end->getPosition().x - m_nodeRef.start->getPosition().x,
                                 m_nodeRef.end->getPosition().y - m_nodeRef.start->getPosition().y },
                 primaryNormVec = { -primaryVec.y, primaryVec.x };

    float angleValue = .4f, // Tweaked values, approx. 45deg
          arrHeadBaseWidth = 20.f,
          primaryVecMag = sqrt(pow(primaryVec.x, 2) + pow(primaryVec.y, 2)),
          tPointOnLine = arrHeadBaseWidth / (2 * (atan(angleValue) / 2) * primaryVecMag ),
          tPrimaryNorm = arrHeadBaseWidth / (2 * primaryVecMag),
          distRatio = m_nodeRef.end->RADIUS / primaryVecMag;

    sf::Vector2f
    scaledPrimaryVec = { primaryVec.x * -tPointOnLine, primaryVec.y * -tPointOnLine },
    pointOnLine = { m_nodeRef.end->getPosition().x + scaledPrimaryVec.x, m_nodeRef.end->getPosition().y + scaledPrimaryVec.y },
    primaryNormVecScaled = { primaryNormVec.x * tPrimaryNorm, primaryNormVec.y * tPrimaryNorm };

    sf::Vector2f startPos = { m_nodeRef.start->getPosition().x, m_nodeRef.start->getPosition().y },
                 endPos = { m_nodeRef.end->getPosition().x, m_nodeRef.end->getPosition().y };
    m_ahPos0.left_line[0].color = this_vertex(0).color;
    m_ahPos0.left_line[1].color = this_vertex(1).color;
    m_ahPos0.left_line[0].position = {pointOnLine.x + primaryNormVecScaled.x, pointOnLine.y + primaryNormVecScaled.y};
    // Point offset: https://math.stackexchange.com/questions/175896/finding-a-point-along-a-line-a-certain-distance-away-from-another-point
    m_ahPos0.left_line[1].position = { (1-distRatio) * endPos.x + distRatio * startPos.x, (1-distRatio) * endPos.y + distRatio * startPos.y };

    m_ahPos0.right_line[0].color = this_vertex(0).color;
    m_ahPos0.right_line[1].color = this_vertex(1).color;
    m_ahPos0.right_line[0].position = { pointOnLine.x - primaryNormVecScaled.x, pointOnLine.y - primaryNormVecScaled.y} ;
    m_ahPos0.right_line[1].position = { (1-distRatio) * endPos.x + distRatio * startPos.x, (1-distRatio) * endPos.y + distRatio * startPos.y };

    if (m_2way) {
        primaryVec = {-primaryVec.x, -primaryVec.y};
        scaledPrimaryVec = { primaryVec.x * -tPointOnLine, primaryVec.y * -tPointOnLine },
        pointOnLine = { m_nodeRef.start->getPosition().x + scaledPrimaryVec.x, m_nodeRef.start->getPosition().y + scaledPrimaryVec.y };
        distRatio = m_nodeRef.start->RADIUS / primaryVecMag;
        m_ahPos1.left_line[0].color = this_vertex(0).color;
        m_ahPos1.left_line[1].color = this_vertex(1).color;
        m_ahPos1.left_line[0].position = {pointOnLine.x + primaryNormVecScaled.x, pointOnLine.y + primaryNormVecScaled.y};
        m_ahPos1.left_line[1].position = { (1-distRatio) * startPos.x + distRatio * endPos.x, (1-distRatio) * startPos.y + distRatio * endPos.y }; //ok

        m_ahPos1.right_line[0].color = this_vertex(0).color;
        m_ahPos1.right_line[1].color = this_vertex(1).color;
        m_ahPos1.right_line[0].position = { pointOnLine.x - primaryNormVecScaled.x, pointOnLine.y - primaryNormVecScaled.y} ;
        m_ahPos1.right_line[1].position = { (1-distRatio) * startPos.x + distRatio * endPos.x, (1-distRatio) * startPos.y + distRatio * endPos.y };
    }
}

void OrientedEdge::draw(sf::RenderWindow &window) {
    if (!m_nodeRef.start || !m_nodeRef.end) return;
    Edge::draw(window);
    window.draw(m_ahPos0.left_line);
    window.draw(m_ahPos0.right_line);
    if (m_2way) {
        window.draw(m_ahPos1.left_line);
        window.draw(m_ahPos1.right_line);
    }
}

