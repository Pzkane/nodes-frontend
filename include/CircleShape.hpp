#ifndef SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED
#define SRC_SHAPES_CIRCLESHAPE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Draggable.hpp"
#include "AbstractShape.hpp"

namespace nf {

/**
 * @brief Interactive CircleShape used for nodes
*/
class CircleShape : public sf::CircleShape, public AbstractShape, public Draggable
{
    bool m_isDragged = false;

public:
    /**
     * Create SFML graphic circle
     * @param radius
     * @param pointCount Circle aliasing
     * @param ms Click milliseconds for callback
    */
    explicit CircleShape(const float radius = 0, const std::size_t pointCount = 30)
        : sf::CircleShape(radius, pointCount) {}
    ~CircleShape() = default;

    /**
     * Set SFML shape position
     * @param x
     * @param y
    */
    void setPosition(const float x, const float y) override;
    /**
     * Set SFML shape position
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
     * Get SFML shape position
     * @returns sf::Vector2f
    */
    sf::Vector2f getPosition() const override;
    /**
     * Get SFML shape origin of transformations
     * @returns sf::Vector2f
    */
    sf::Vector2f getOrigin() override;
    /**
     * Get SFML shape global bounds (grid relative)
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
