#ifndef SRC_ENTITIES_CONTAINER_HPP_INCLUDED
#define SRC_ENTITIES_CONTAINER_HPP_INCLUDED

#include <functional>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "AbstractShape.hpp"
#include "Draggable.hpp"
#include "Entity.hpp"
#include "Label.hpp"

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
    static int ID;
    using ChildContainers = std::vector<Container>;
    ChildContainers m_children;
    bool m_visible = true;
    std::function<void()> m_callback = nullptr;
    bool m_destroy = false, m_originating = false;
    void init();

    friend class Overlay;
public:
    int m_id;
    sf::Vector2i padding = {0, 0};
    sf::Text m_label;

    Container() : sf::RectangleShape() { init(); }
    /**
     * Just visual container
    */
    Container(const sf::Vector2f& size,
              const sf::Vector2f& pos = {},
              const sf::Vector2i& padding = {});
    /**
     * @brief COntainer with callbacks
     * @param text std::string& displayed name of operation
     * @param callback std::function<void*(void*)> callback procedure for ActionObserver
     * @param originating bool if originating - callback will be called with parameters
     *              from ActionObserver, otherwise - callback will receive `nullptr` as input
     * @param size sf::Vector2f&
     * @param pos sf::Vector2f&
     * @param padding sf::Vector2f&
    */
    Container(const std::string& text,
              const std::function<void()> callback,
              const bool originating,
              const sf::Vector2f& size,
              const sf::Vector2f& pos = {},
              const sf::Vector2i& padding = {});

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

    /**
     * @brief Set state of a container to destruction
    */
    void markDestroy(bool state);

    /**
     * @brief Return current state of all of the containers
     * If at least 1 of the containers (including children) is marked
     * for destruction - return true. Useful for parenting.
     * @returns bool stacked state
    */
    bool markedForDestroy() const;

    void update(const sf::RenderWindow &window, EventFlags &ef) override;
    void draw(sf::RenderWindow &window) override;
};

};

#endif // SRC_ENTITIES_CONTAINER_HPP_INCLUDED