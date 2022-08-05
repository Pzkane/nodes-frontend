#ifndef SRC_SCENES_MAINSCENE_HPP_INCLUDED
#define SRC_SCENES_MAINSCENE_HPP_INCLUDED

#include <queue>
#include "Scene.hpp"
#include "Node.hpp"
#include "EventType.hpp"

namespace nf {

class MainScene : public Scene
{
    bool m_b_mousePressed = false;
    std::list<Node *> m_nodes;
    std::list<Connector *> m_connectors;
    EventFlags ef;

public:
    MainScene(sf::RenderWindow &window);
    ~MainScene();
    Node *createNode(float radius);
    void pushNode(Node *node);
    void pushConnector(Connector *conn);

    void update();
    void draw();
    void *updateInput(const sf::Event &event);
    void *updateInput(const EventType &eventType);
};

};

#endif // SRC_SCENES_MAINSCENE_HPP_INCLUDED
