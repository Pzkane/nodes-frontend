#ifndef SRC_SCENES_MAINSCENE_HPP_INCLUDED
#define SRC_SCENES_MAINSCENE_HPP_INCLUDED

#include "Scene.hpp"
#include "Node.hpp"

class MainScene : public Scene
{
    std::vector<Node *> m_nodes;

public:
    MainScene(sf::RenderWindow &window);
    ~MainScene() = default;
    void update();
    void draw();
    void pushNode(Node *node, int at = -1);
};

#endif // SRC_SCENES_MAINSCENE_HPP_INCLUDED
