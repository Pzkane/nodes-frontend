#ifndef SRC_SCENES_SCENESWITCHER_HPP_INCLUDED
#define SRC_SCENES_SCENESWITCHER_HPP_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "EventType.hpp"

namespace nf {

/**
 * @brief Provides facilities to switch between active/inactive scenes.
 * Should own pointer to the scene
*/
class SceneSwitcher
{
public:
    Scene *m_curr_scene = nullptr;

public:
    explicit SceneSwitcher() {}
    ~SceneSwitcher() = default;
    /**
     * Switch to new scene
     * @param scene Scene*
    */
    void switchTo(Scene *scene);
    /**
     * Update state of current scene
    */
    void updateScene();
    /**
     * Draw everything related to the current scene
    */
    void drawScene();
    /**
     * Deletes scene and invalidates pointer
    */
    void deleteCurrScene();
    /**
     * Update current scene state by given input
     * @param event sf::Event
     * @param payload void*
    */
    void* updateInput(const sf::Event &event, void* payload = nullptr);
    /**
     * Update current scene state by given input
     * @param eventType EventType
     * @param payload void*
    */
    void* updateInput(const EventType &eventType, void* payload = nullptr);
    void cleanup();
    /**
     * Retrieve current scene flags
    */
    const void* getSceneFlags(Flags::Type type);
};

};

#endif // SRC_SCENES_SCENESWITCHER_HPP_INCLUDED
