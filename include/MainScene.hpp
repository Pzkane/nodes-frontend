#ifndef SRC_SCENES_MAINSCENE_HPP_INCLUDED
#define SRC_SCENES_MAINSCENE_HPP_INCLUDED

#include <queue>
#include "Scene.hpp"
#include "NodeImpl.hpp"
#include "EventType.hpp"
#include "OrientedEdge.hpp"
#include "WeightedEdge.hpp"
#include "WeightedOrientedEdge.hpp"
#include "Overlay.hpp"
#include "Resource.hpp"

namespace nf {

/**
 * @brief Scene for algorithms
*/
class MainScene : public Scene
{
    bool m_b_mousePressed = false;
    /// @brief List of nodes in scene
    std::list<NodeImpl*> m_nodes;
    /// @brief List of edges in scene
    std::list<Edge*> m_edges;
    /// @brief Current event flags (button presses, global node states (deprecated))
    EventFlags ef;
    /// @brief This scene UI elements
    Resource<Overlay*> m_uis{};
    /// @brief Call to update UI 
    void updateUI(bool resized = false);
public:
    MainScene(sf::RenderWindow &window);
    ~MainScene();
    NodeImpl* createNode(Observable *entity, float radius);
    Edge* createEdge();
    OrientedEdge* createOEdge();
    WeightedEdge* createWEdge();
    WeightedOrientedEdge* createWOEdge();
    void removeNode(NodeImpl *node_ptr_payload);
    void removeEdge(Nodes2ptr* ptr_payload);
    void pushNode(NodeImpl* node);
    void pushEdge(Edge* conn);
    /**
     * @brief Center all elements relative to mouse press
     * 
     * Illusion, view is untouched, everything else is moved by offset
    */
    void centerView();
    /**
     * @brief Move view by given offset using scroll
     * 
     * Illusion, view is untouched, everything else is moved by offset
    */
    void moveView(int offset_x, int offset_y);
    /**
     * Add new overlay section
    */
    void mergeOverlay(Overlay* child);
    /**
     * Remove overlay section from vector
    */
    // void divideOverlay(Overlay *child);

    void update() override;
    void draw() override;
    void* updateInput(const sf::Event &event, void* payload = nullptr) override;
    void* updateInput(const EventType &eventType, void* payload = nullptr) override;
    const void* getFlags(Flags::Type type) override;
};

};

#endif // SRC_SCENES_MAINSCENE_HPP_INCLUDED
