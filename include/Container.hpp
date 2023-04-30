#ifndef SRC_ENTITIES_CONTAINER_HPP_INCLUDED
#define SRC_ENTITIES_CONTAINER_HPP_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include "AbstractShape.hpp"
#include "Draggable.hpp"
#include "Entity.hpp"

namespace nf {

/**
 * @brief Entity of a rectangular shape
 * 
 * Contains other child containers
 * 
 * Mainly used as an UI builder but can be used for other purposes (array-/stack-based algorithms, structures, ...)
*/
class Container : public Entity, public AbstractShape, public Draggable, public sf::RectangleShape
{
    using ChildContainers = std::vector<Container>;
    ChildContainers m_children;
    bool m_visible = true;
    void init();

    friend class Overlay;
public:
    sf::Vector2i padding = {0, 0};

    Container() : sf::RectangleShape() { init(); }
    Container(const sf::Vector2f& size,
              const sf::Vector2f& pos = {},
              const sf::Vector2i& padding = {});
    Container(const Container& other);

    /**
     * Append a copy of the new child element to the container child list
     * @param child nf::Container
    */
    void addChildElement(const Container& child);
    /**
     * Move new child element into the container child list
     * @param child nf::Container
    */
    void addChildElement(Container&& child);
    /**
     * Set whenever this object will be rendered on screen
     * @param state Boolean
    */
    void setVisibility(bool state);
    /**
     * Determine whenever this object is being rendered
     * @returns bool
    */
    bool isHidden();

    /**
     * Set SFML shape position
     * @param position sf::Vector2f
    */
    void setPosition(const sf::Vector2f &position) override;
    /**
     * Set SFML shape position
     * @param x
     * @param y
    */
    void setPosition(const float x, const float y) override;
    /**
     * Get SFML shape position
     * @returns sf::Vector2f
    */
    sf::Vector2f getPosition() const override;
    /**
     * Determine whenever given mouse position is inside of this shape
     * @param position sf::Vector2f
    */
    bool mouseInside(const sf::Vector2f &position) override;
    /**
     * Get Left Mouse Button status from EventFlags
     * @returns bool
    */
    bool isLMBPressed() override;
    /**
     * Set transformation origin of this shape
     * @param position sf::Vector2f
    */
    void setOrigin(sf::Vector2f &origin) override;
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

    void update(const sf::RenderWindow &window, EventFlags &ef) override;
    void draw(sf::RenderWindow &window) {};
};

};

#endif // SRC_ENTITIES_CONTAINER_HPP_INCLUDED