#ifndef SRC_SHAPES_ABSTRACTSHAPE_HPP_INCLUDED
#define SRC_SHAPES_ABSTRACTSHAPE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "EventFlags.hpp"
#include "Callbacks.hpp"

namespace nf {

class AbstractShape
{
public:
    EventFlags m_event_flags;
    AbstractShape() {}
    ~AbstractShape() = default;
    void setEventFlags(const EventFlags &ef);
    virtual bool checkPosAgainstShape(const sf::Vector2f &position) { return true; };
    virtual bool mouseInside(const sf::Vector2f &position) { return true; };
    virtual void setCallback(VoidCallback callbackFnc) {};
};

};

#endif // SRC_SHAPES_ABSTRACTSHAPE_HPP_INCLUDED
