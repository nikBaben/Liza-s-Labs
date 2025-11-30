#pragma once

#include <SFML/Graphics.hpp>
#include "Plane.hpp"

// Отвечает за фон и стационарные объекты (земля, ВПП)
// Фон рисуется прямо в окно, остальные объекты — в отдельную текстуру.
class Scene
{
public:
    Scene();

    // Инициализация под размер окна
    void init(const sf::RenderWindow& window);

    // Загрузка фоновой картинки
    bool loadBackground(const std::string& path);

    // Пересчёт масштаба фона под окно (если нужно)
    void resize(const sf::RenderWindow& window);

    // Рисует фон напрямую в окно
    void drawBackground(sf::RenderWindow& window) const;

    // Рисует землю/полосу/разметку в RenderTarget (render texture)
    void drawEnvironment(sf::RenderTarget& target,
                         const Plane& plane) const;

private:
    sf::Texture bgTexture;
    sf::Sprite  bgSprite;
};
