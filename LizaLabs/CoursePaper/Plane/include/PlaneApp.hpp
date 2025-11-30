#pragma once

#include <SFML/Graphics.hpp>
#include "Plane.hpp"
#include "Scene.hpp"

class PlaneApp
{
public:
    PlaneApp();
    void run();

private:
    sf::RenderWindow window;

    Scene scene;
    Plane plane;

    // Все объекты, кроме фона, рисуем сюда
    sf::RenderTexture sceneTexture;

    sf::Font font;
    sf::Text hudText;

    float speedFactor;   // множитель скорости анимации
    bool  paused;        // true = пауза

    void processEvents();
    void update(float dt);
    void render();
};
