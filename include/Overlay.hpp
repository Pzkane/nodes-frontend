#ifndef SRC_UI_OVERLAY_HPP_INCLUDED
#define SRC_UI_OVERLAY_HPP_INCLUDED

#include "Container.hpp"

namespace nf {

class Overlay
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

    bool isHidden() { return !m_visible; }
    void createWrapper(const Container& container);
    void addContainer(Container&& container);
    void addContainer(const Container& container);
    void update(sf::RenderWindow& window, const EventFlags& ef, bool resized);
    void draw(sf::RenderWindow& window);
};

};

#endif // SRC_UI_OVERLAY_HPP_INCLUDED