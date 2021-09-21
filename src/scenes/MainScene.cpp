#include "MainScene.hpp"
#include "utils.hpp"

MainScene::MainScene() : Scene()
{
    for (int i = 0; i < 50; ++i)
    {
        sf::CircleShape *cs = new sf::CircleShape(40);
        cs->setFillColor(sf::Color::Red);
        cs->setPosition(sf::Vector2f(Utils::get_random_number<float>(0.f, 500.f), Utils::get_random_number<float>(0.f, 500.f)));
        pushDrawable(cs);
    }
}

void MainScene::draw()
{
    Scene::draw();
}
