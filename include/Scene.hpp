#ifndef SRC_SCENES_SCENE_HPP_INCLUDED
#define SRC_SCENES_SCENE_HPP_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>

class Scene
{
    bool m_state = false;
    sf::RenderWindow *p_window = nullptr;

protected:
    std::vector<sf::Drawable *> m_drawables;

public:
    Scene() {}
    virtual ~Scene() = default;
    virtual void draw();
    void pushDrawable(sf::Drawable *drawable, size_t at = -1);
    void popDrawable(size_t at = -1);
    void setActive(bool state);
    void setWindow(const sf::RenderWindow *window);
};

#endif // SRC_SCENES_SCENE_HPP_INCLUDED
