#ifndef SRC_PROPERTIES_DRAGGABLE_HPP_INCLUDED
#define SRC_PROPERTIES_DRAGGABLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

namespace nf {

/**
 * @brief Describes draggable property of an object with mouse interaction
 * Used for object mouse drag
*/
class Draggable
{
    bool m_successDrag = false,
         m_movable     = false;
    sf::Vector2f m_offsetMousePos;

public:
    Draggable() {}
    virtual ~Draggable() = default;
    /**
     * Determine available actions based on mouse pointer state for given window
     *  and prepare for its processing
     * @param window RenderWindow in which given object is being dragged
    */
    void trackMousePointer(const sf::RenderWindow &window);
    /**
     * Activate/deactivate dragging state for current object
     * @param state bool
    */
    void setMovable(bool state) { m_movable = state; };
    /**
     * Accessor for `m_movable` member
     * @returns bool
    */
    bool isMoving() { return m_movable; };

    /**
     * Set SFML shape position. Should be overriden
     * @param position sf::Vector2f
    */
    virtual void setPosition(const sf::Vector2f &position) = 0;
    /**
     * Set SFML shape position. Should be overriden
     * @param position sf::Vector2f
    */
    virtual void setPosition(const float x, const float y) = 0;
    
    /**
     * Get SFML shape position. Should be overriden
     * @returns sf::Vector2f
    */
    virtual sf::Vector2f getPosition() const = 0;
    virtual bool mouseInside(const sf::Vector2f &position) = 0;
    /**
     * Get Left Mouse Button status from EventFlags. Should be overriden
     * @returns bool
    */
    virtual bool isLMBPressed() = 0;
    /**
     * Set transformation origin of this shape. Should be overriden
     * @param position sf::Vector2f
    */
    virtual void setOrigin(sf::Vector2f &origin) = 0;
    /**
     * Get SFML shape origin of transformations. Should be overriden
     * @returns sf::Vector2f
    */
    virtual sf::Vector2f getOrigin() = 0;
    /**
     * Get SFML shape global bounds (grid relative). Should be overriden
     * @returns sf::Vector2f
    */
    virtual sf::FloatRect getGlobalBounds() = 0;
};

};

#endif // SRC_PROPERTIES_DRAGGABLE_HPP_INCLUDED
