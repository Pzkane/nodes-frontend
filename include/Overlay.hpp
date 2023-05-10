#ifndef SRC_UI_OVERLAY_HPP_INCLUDED
#define SRC_UI_OVERLAY_HPP_INCLUDED

#include "Container.hpp"
#include "Entity.hpp"

namespace nf {

/**
 * @brief Custom interface builder
 * 
 * Overlay consists of containers with text
*/
class Overlay : public Entity
{
    bool m_visible = true;
    Container* m_wrapper = nullptr;
    void copy(const Overlay& o);
    void move(Overlay&& o);
    void destroyWrapper();
public:
    Overlay();
    explicit Overlay(const Container& wrapper);
    ~Overlay();

    Overlay(const Overlay& o);
    Overlay& operator=(const Overlay& o);

    Overlay(Overlay&& o);
    Overlay& operator=(Overlay&& o);

    void show() { m_visible = true; }
    void hide() { m_visible = false; }
    /**
     * Check if whole UI element is visible
    */
    bool isHidden() { return !m_visible; }
    /**
     * Lazy-initialize main wrapper container
    */
    void createWrapper(const Container& container);
    /**
     * Return main wrapper container
    */
    const Container* getWrapper();
    /**
     * Add child container to UI
    */
    void addContainer(Container&& container);
    void addContainer(const Container& container);
    void update(sf::RenderWindow& window, const EventFlags& ef, bool resized);
    void draw(sf::RenderWindow& window) override;

    // Stub
    void update(const sf::RenderWindow &window, EventFlags &ef) {};
};

};

#endif // SRC_UI_OVERLAY_HPP_INCLUDED