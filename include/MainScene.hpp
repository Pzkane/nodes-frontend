#ifndef SRC_SCENES_MAINSCENE_HPP_INCLUDED
#define SRC_SCENES_MAINSCENE_HPP_INCLUDED

#include <queue>
#include "Scene.hpp"
#include "Node.hpp"

class MainScene : public Scene
{
    bool m_b_mousePressed = false;
    std::list<Node *> m_nodes;
    std::list<Connector *> m_connectors;
    EventFlags ef;

public:
    MainScene(sf::RenderWindow &window);
    ~MainScene();
    void createNode();
    void pushNode(Node *node);
    void pushConnector(Connector *node);

    void update();
    void draw();
    void updateInput(const sf::Event &event);
};

#endif // SRC_SCENES_MAINSCENE_HPP_INCLUDED
