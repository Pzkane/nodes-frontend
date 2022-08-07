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

    void setPosition(const float x, const float y) override;
    void setPosition(const sf::Vector2f &position) override;
    bool checkPosAgainstShape(const sf::Vector2f &position);
    bool mouseInside(const sf::Vector2f &position);
    void setOrigin(sf::Vector2f &origin) override;
    void setCallback(VoidCallback callbackFnc) override;
    sf::Vector2f getPosition() override;
    sf::Vector2f getOrigin() override;
    sf::FloatRect getGlobalBounds() override;

    bool isLMBPressed();
};

};

#endif // SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED
