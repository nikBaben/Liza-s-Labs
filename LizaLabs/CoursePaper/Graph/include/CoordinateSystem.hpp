#pragma once

#include <SFML/Graphics.hpp>

class CoordinateSystem
{
public:
    CoordinateSystem();

    // Рисует оси, деления, подписи, начало координат
    void draw(sf::RenderWindow& window,
              float scale,
              const sf::Vector2f& center);

private:
    sf::Font font;

    sf::Vector2f worldToScreen(const sf::Vector2f& world,
                               float scale,
                               const sf::Vector2f& center,
                               const sf::Vector2u& winSize) const;
};
