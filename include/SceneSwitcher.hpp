#ifndef SRC_SCENES_SCENESWITCHER_HPP_INCLUDED
#define SRC_SCENES_SCENESWITCHER_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "EventType.hpp"

namespace nf {

class SceneSwitcher
{
public:
    Scene *m_curr_scene = nullptr;

public:
    explicit SceneSwitcher() {}
    ~SceneSwitcher() = default;
    void switchTo(Scene *scene);
    void updateScene();
    void drawScene();
    void deleteCurrScene();
    void* updateInput(const sf::Event &event, void* payload = nullptr);
    void* updateInput(const EventType &eventType, void* payload = nullptr);
    void cleanup();
};

};

#endif // SRC_SCENES_SCENESWITCHER_HPP_INCLUDED
