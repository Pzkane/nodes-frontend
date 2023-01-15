#ifndef SRC_ENTITIES_CONTAINER_HPP_INCLUDED
#define SRC_ENTITIES_CONTAINER_HPP_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include "AbstractShape.hpp"
#include "Draggable.hpp"
#include "Entity.hpp"

namespace nf {

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

    void addChildElement(const Container& child);
    void addChildElement(Container&& child);
    void setVisible(bool state);
    bool isHidden();

    void setPosition(const sf::Vector2f &position) override;
    void setPosition(const float x, const float y) override;
    sf::Vector2f getPosition() const override;
    bool mouseInside(const sf::Vector2f &position) override;
    bool isLMBPressed() override;
    void setOrigin(sf::Vector2f &origin) override;
    sf::Vector2f getOrigin() override;
    sf::FloatRect getGlobalBounds() override;

    void update(const sf::RenderWindow &window, EventFlags &ef) override;
    void draw(sf::RenderWindow &window) {};
};

};

#endif // SRC_ENTITIES_CONTAINER_HPP_INCLUDED