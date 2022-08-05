#ifndef SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED
#define SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Draggable.hpp"
#include "Clickable.hpp"
#include "AbstractShape.hpp"

namespace nf {

class CircleShape : public sf::CircleShape, public AbstractShape, public Draggable, public Clickable<VoidCallback>
{
    bool m_is_dragged = false;

public:
    explicit CircleShape(const float radius = 0, const std::size_t pointCount = 30, size_t ms = 50)
        : sf::CircleShape(radius, pointCount), Clickable(ms) {}
    ~CircleShape() = default;
    void setPosition(const float x, const float y) ;
    void setPosition(const sf::Vector2f &position) ;
    sf::Vector2f getPosition() ;
    bool checkPosAgainstShape(const sf::Vector2f &position) ;
    bool mouseInside(const sf::Vector2f &position) ;
    void setOrigin(sf::Vector2f &origin) ;
    void setCallback(VoidCallback callbackFnc) ;
    sf::Vector2f getOrigin() ;
    sf::FloatRect getGlobalBounds() ;

    bool isLMBPressed();
};

};

#endif // SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED
