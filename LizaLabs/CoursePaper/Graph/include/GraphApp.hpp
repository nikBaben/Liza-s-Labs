#pragma once

#include <SFML/Graphics.hpp>
#include "CoordinateSystem.hpp"
#include "FunctionPlot.hpp"

class GraphApp
{
public:
    GraphApp();
    void run();

private:
    sf::RenderWindow window;
    CoordinateSystem coords;
    FunctionPlot plot;

    float scale;           // пикселей на единицу
    sf::Vector2f center;   // мировые координаты центра экрана

    void processEvents();
    void update();
    void render();
};
