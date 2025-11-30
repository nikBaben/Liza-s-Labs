#pragma once

#include <SFML/Graphics.hpp>

class FunctionPlot
{
public:
    FunctionPlot();

    // y = x^2 - 6/(x - 1) + 3
    float f(float x) const;

    // Рисует график и асимптоту
    void draw(sf::RenderWindow& window,
              float scale,
              const sf::Vector2f& center);

private:
    sf::Font font;

    sf::Vector2f worldToScreen(float x, float y,
                               float scale,
                               const sf::Vector2f& center,
                               const sf::Vector2u& winSize) const;
};
