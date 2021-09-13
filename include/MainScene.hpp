#ifndef SRC_SCENES_MAINSCENE_HPP_INCLUDED
#define SRC_SCENES_MAINSCENE_HPP_INCLUDED

#include "Scene.hpp"

class MainScene : public Scene
{
public:
    MainScene();
    ~MainScene() = default;
    void draw();
};

#endif // SRC_SCENES_MAINSCENE_HPP_INCLUDED
