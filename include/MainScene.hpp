#ifndef SRC_SCENES_MAINSCENE_HPP_INCLUDED
#define SRC_SCENES_MAINSCENE_HPP_INCLUDED

#include <queue>
#include "Scene.hpp"
#include "Node.hpp"

class MainScene : public Scene
{
    bool m_b_mousePressed = false;
    std::vector<Node *> m_nodes;
    std::vector<Connector *> m_connectors;
    EventFlags ef;

public:
    MainScene(sf::RenderWindow &window);
    ~MainScene() = default;
    void createNode();
    void pushNode(Node *node, int at = -1);
    void pushConnector(Connector *node, int at = -1);

    void update();
    void draw();
    void updateInput(const sf::Event &event);
};

#endif // SRC_SCENES_MAINSCENE_HPP_INCLUDED
