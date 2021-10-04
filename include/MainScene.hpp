#ifndef SRC_SCENES_MAINSCENE_HPP_INCLUDED
#define SRC_SCENES_MAINSCENE_HPP_INCLUDED

#include <queue>
#include "Scene.hpp"
#include "Node.hpp"

class MainScene : public Scene
{
    bool m_b_mousePressed = false;
    std::vector<Node *> m_nodes;
    EventFlags ef;

public:
    MainScene(sf::RenderWindow &window);
    ~MainScene() = default;
    void update();
    void draw();
    void pushNode(Node *node, int at = -1);
    void updateInput(const sf::Event &event);
};

#endif // SRC_SCENES_MAINSCENE_HPP_INCLUDED
