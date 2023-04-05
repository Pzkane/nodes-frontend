#ifndef SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED
#define SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Draggable.hpp"
#include "Clickable.hpp"
#include "AbstractShape.hpp"

namespace nf {

/**
 * @brief Interactive CircleShape used for nodes
*/
class CircleShape : public sf::CircleShape, public AbstractShape, public Draggable, public Clickable<VoidCallback>
{
    bool m_is_dragged = false;

public:
    /**
     * Create SMFL graphic circle
     * @param radius
     * @param pointCount Circle aliasing
     * @param ms Click milliseconds for callback
    */
    explicit CircleShape(const float radius = 0, const std::size_t pointCount = 30, const std::size_t ms = 50)
        : sf::CircleShape(radius, pointCount), Clickable(ms) {}
    ~CircleShape() = default;

    /**
     * Set SMFL shape position
     * @param x
     * @param y Circle aliasing
    */
    void setPosition(const float x, const float y) override;
    /**
     * Set SMFL shape position
     * @param position sf::Vector2f
    */
    void setPosition(const sf::Vector2f &position) override;
    /**
     * Determine whenever given position is inside of this shape
     * @param position sf::Vector2f
    */
    bool checkPosAgainstShape(const sf::Vector2f &position);
    /**
     * Determine whenever given mouse position is inside of this shape
     * @param position sf::Vector2f
    */
    bool mouseInside(const sf::Vector2f &position);
    /**
     * Set transformation origin of this shape
     * @param position sf::Vector2f
    */
    void setOrigin(sf::Vector2f &origin) override;
    /**
     * !Not finished
     * Set callback for this shape which will be called during specific event
     * @param position sf::Vector2f
    */
    void setCallback(VoidCallback callbackFnc) override;
    /**
     * Get SMFL shape position
     * @returns sf::Vector2f
    */
    sf::Vector2f getPosition() const override;
    /**
     * Get SMFL shape origin of transformations
     * @returns sf::Vector2f
    */
    sf::Vector2f getOrigin() override;
    /**
     * Get SMFL shape global bounds (grid relative)
     * @returns sf::Vector2f
    */
    sf::FloatRect getGlobalBounds() override;
    /**
     * Get Left Mouse Button status from EventFlags
     * @returns bool
    */
    bool isLMBPressed();
};

};

#endif // SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED
