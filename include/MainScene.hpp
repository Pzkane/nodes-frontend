#ifndef SRC_SCENES_MAINSCENE_HPP_INCLUDED
#define SRC_SCENES_MAINSCENE_HPP_INCLUDED

#include <queue>
#include "Scene.hpp"
#include "NodeImpl.hpp"
#include "EventType.hpp"
#include "OrientedEdge.hpp"
#include "WeightedEdge.hpp"

namespace nf {

/**
 * @brief Scene for algorithms
*/
class MainScene : public Scene
{
    bool m_b_mousePressed = false;
    std::list<NodeImpl*> m_nodes;
    std::list<Edge*> m_edges;
    EventFlags ef;
    bool m_node_marked_for_delete = false;

public:
    MainScene(sf::RenderWindow &window);
    ~MainScene();
    NodeImpl* createNode(float radius);
    Edge* createEdge();
    OrientedEdge* createOEdge();
    WeightedEdge* createWEdge();
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

    void update() override;
    void draw() override;
    void* updateInput(const sf::Event &event, void* payload = nullptr) override;
    void* updateInput(const EventType &eventType, void* payload = nullptr) override;
    const void* getFlags(Flags::Type type) override;
};

};

#endif // SRC_SCENES_MAINSCENE_HPP_INCLUDED
