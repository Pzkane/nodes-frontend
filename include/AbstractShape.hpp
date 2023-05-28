#ifndef SRC_SHAPES_ABSTRACTSHAPE_HPP_INCLUDED
#define SRC_SHAPES_ABSTRACTSHAPE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "EventFlags.hpp"

namespace nf {

/**
 * @brief Generalized class for all visual shapes with overridable helper utilities
 * 
 * Abstract shape provides generic methods for any kind of shape
 * Consists of current EventFlags
*/
class AbstractShape
{
public:
    EventFlags m_event_flags;
    AbstractShape() {}
    ~AbstractShape() = default;

    /**
     * Set/replace latest internal `m_event_flags` member for shape
     * @param ef EventFlags reference
    */
    void setEventFlags(const EventFlags &ef);
    /**
     * Determine whenever given position is inside of this shape
     * @param position sf::Vector2f reference
     * @returns bool Always returns `true` if not overriden
    */
    virtual bool checkPosAgainstShape(const sf::Vector2f &position) { return true; };
    /**
     * Explicit member to determine whenever given mouse position is inside of this shape
     * Usually internally calls `checkPosAgainstShape`
     * @param position sf::Vector2f reference
     * @returns bool Always returns `true` if not overriden
    */
    virtual bool mouseInside(const sf::Vector2f &position) { return true; };
};

};

#endif // SRC_SHAPES_ABSTRACTSHAPE_HPP_INCLUDED
