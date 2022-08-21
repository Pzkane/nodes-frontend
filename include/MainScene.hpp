#ifndef SRC_SCENES_MAINSCENE_HPP_INCLUDED
#define SRC_SCENES_MAINSCENE_HPP_INCLUDED

#include <queue>
#include "Scene.hpp"
#include "_Node.hpp"
#include "EventType.hpp"

namespace nf {

class MainScene : public Scene
{
    bool m_b_mousePressed = false;
    std::list<_Node *> m_nodes;
    std::list<Connector *> m_connectors;
    EventFlags ef;

public:
    MainScene(sf::RenderWindow &window);
    ~MainScene();
    _Node *createNode(float radius);
    Connector* createConnector();
    void removeConnector(Nodes2ptr *ptr_payload);
    void pushNode(_Node *node);
    void pushConnector(Connector *conn);
    void centerView();

    void update() override;
    void draw() override;
    void* updateInput(const sf::Event &event, void* payload = nullptr) override;
    void* updateInput(const EventType &eventType, void* payload = nullptr) override;
};

};

#endif // SRC_SCENES_MAINSCENE_HPP_INCLUDED
