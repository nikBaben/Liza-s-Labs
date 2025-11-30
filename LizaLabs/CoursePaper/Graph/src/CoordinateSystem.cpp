#include "CoordinateSystem.hpp"
#include <cmath>
#include <iostream>

CoordinateSystem::CoordinateSystem()
{
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        std::cerr << "Failed to load font assets/arial.ttf\n";
    }
}

sf::Vector2f CoordinateSystem::worldToScreen(const sf::Vector2f& world,
                                             float scale,
                                             const sf::Vector2f& center,
                                             const sf::Vector2u& winSize) const
{
    float sx = (world.x - center.x) * scale + winSize.x / 2.f;
    float sy = winSize.y / 2.f - (world.y - center.y) * scale;
    return sf::Vector2f(sx, sy);
}

void CoordinateSystem::draw(sf::RenderWindow& window,
                            float scale,
                            const sf::Vector2f& center)
{
    const sf::Vector2u ws = window.getSize();

    // Видимый диапазон в мировых координатах
    float worldLeft   = center.x - ws.x / (2.f * scale);
    float worldRight  = center.x + ws.x / (2.f * scale);
    float worldBottom = center.y - ws.y / (2.f * scale);
    float worldTop    = center.y + ws.y / (2.f * scale);

    sf::Color axisColor(40, 40, 40);
    sf::Color gridColor(220, 220, 220);
    sf::Color textColor(20, 20, 20);

    sf::Text text;
    text.setFont(font);
    text.setFillColor(textColor);
    text.setCharacterSize(14);

    // СЕТКА (по целым координатам, если масштаб позволяет)
    if (scale >= 15.f)
    {
        sf::VertexArray grid(sf::Lines);

        int startX = static_cast<int>(std::floor(worldLeft));
        int endX   = static_cast<int>(std::ceil(worldRight));
        int startY = static_cast<int>(std::floor(worldBottom));
        int endY   = static_cast<int>(std::ceil(worldTop));

        for (int i = startX; i <= endX; ++i)
        {
            sf::Vector2f p1 = worldToScreen(sf::Vector2f(static_cast<float>(i), worldBottom), scale, center, ws);
            sf::Vector2f p2 = worldToScreen(sf::Vector2f(static_cast<float>(i), worldTop),    scale, center, ws);
            grid.append(sf::Vertex(p1, gridColor));
            grid.append(sf::Vertex(p2, gridColor));
        }

        for (int j = startY; j <= endY; ++j)
        {
            sf::Vector2f p1 = worldToScreen(sf::Vector2f(worldLeft,  static_cast<float>(j)), scale, center, ws);
            sf::Vector2f p2 = worldToScreen(sf::Vector2f(worldRight, static_cast<float>(j)), scale, center, ws);
            grid.append(sf::Vertex(p1, gridColor));
            grid.append(sf::Vertex(p2, gridColor));
        }

        window.draw(grid);
    }

    // ОСИ OX и OY
    sf::VertexArray axes(sf::Lines);

    // OX
    if (worldBottom <= 0.f && worldTop >= 0.f)
    {
        sf::Vector2f p1 = worldToScreen(sf::Vector2f(worldLeft, 0.f), scale, center, ws);
        sf::Vector2f p2 = worldToScreen(sf::Vector2f(worldRight, 0.f), scale, center, ws);
        axes.append(sf::Vertex(p1, axisColor));
        axes.append(sf::Vertex(p2, axisColor));
    }

    // OY
    if (worldLeft <= 0.f && worldRight >= 0.f)
    {
        sf::Vector2f p1 = worldToScreen(sf::Vector2f(0.f, worldBottom), scale, center, ws);
        sf::Vector2f p2 = worldToScreen(sf::Vector2f(0.f, worldTop),    scale, center, ws);
        axes.append(sf::Vertex(p1, axisColor));
        axes.append(sf::Vertex(p2, axisColor));
    }

    window.draw(axes);

    // Начало координат (0,0)
    if (worldLeft <= 0.f && worldRight >= 0.f &&
        worldBottom <= 0.f && worldTop >= 0.f)
    {
        sf::Vector2f origin = worldToScreen(sf::Vector2f(0.f, 0.f), scale, center, ws);

        sf::CircleShape dot(3.f);
        dot.setFillColor(sf::Color::Red);
        dot.setOrigin(3.f, 3.f);
        dot.setPosition(origin);
        window.draw(dot);

        text.setString("0");
        text.setPosition(origin.x + 5.f, origin.y + 5.f);
        window.draw(text);
    }

    // Стрелки и подписи осей
    // OX
    if (worldBottom <= 0.f && worldTop >= 0.f)
    {
        sf::Vector2f endX = worldToScreen(sf::Vector2f(worldRight, 0.f), scale, center, ws);

        sf::VertexArray arrowX(sf::Lines, 4);
        arrowX[0] = sf::Vertex(sf::Vector2f(endX.x, endX.y), axisColor);
        arrowX[1] = sf::Vertex(sf::Vector2f(endX.x - 10.f, endX.y - 5.f), axisColor);
        arrowX[2] = sf::Vertex(sf::Vector2f(endX.x, endX.y), axisColor);
        arrowX[3] = sf::Vertex(sf::Vector2f(endX.x - 10.f, endX.y + 5.f), axisColor);
        window.draw(arrowX);

        text.setString("x");
        text.setPosition(endX.x - 15.f, endX.y + 10.f);
        window.draw(text);
    }

    // OY
    if (worldLeft <= 0.f && worldRight >= 0.f)
    {
        sf::Vector2f endY = worldToScreen(sf::Vector2f(0.f, worldTop), scale, center, ws);

        sf::VertexArray arrowY(sf::Lines, 4);
        arrowY[0] = sf::Vertex(sf::Vector2f(endY.x, endY.y), axisColor);
        arrowY[1] = sf::Vertex(sf::Vector2f(endY.x - 5.f, endY.y + 10.f), axisColor);
        arrowY[2] = sf::Vertex(sf::Vector2f(endY.x, endY.y), axisColor);
        arrowY[3] = sf::Vertex(sf::Vector2f(endY.x + 5.f, endY.y + 10.f), axisColor);
        window.draw(arrowY);

        text.setString("y");
        // чуть сдвигаем вниз, чтобы не упиралось в край окна
        text.setPosition(endY.x + 8.f, endY.y + 5.f);
        window.draw(text);
    }

    // Деления и числовые подписи
    if (scale >= 15.f)
    {
        sf::VertexArray ticks(sf::Lines);

        int startX = static_cast<int>(std::floor(worldLeft));
        int endX   = static_cast<int>(std::ceil(worldRight));
        int startY = static_cast<int>(std::floor(worldBottom));
        int endY   = static_cast<int>(std::ceil(worldTop));

        // по оси X
        for (int i = startX; i <= endX; ++i)
        {
            if (i == 0) continue;

            if (worldBottom <= 0.f && worldTop >= 0.f)
            {
                sf::Vector2f p1 = worldToScreen(sf::Vector2f(static_cast<float>(i), 0.f), scale, center, ws);
                sf::Vector2f p2 = p1;
                p1.y -= 4.f;
                p2.y += 4.f;

                ticks.append(sf::Vertex(p1, axisColor));
                ticks.append(sf::Vertex(p2, axisColor));

                text.setString(std::to_string(i));
                text.setPosition(p2.x - 6.f, p2.y + 4.f);
                window.draw(text);
            }
        }

        // по оси Y
        for (int j = startY; j <= endY; ++j)
        {
            if (j == 0) continue;

            if (worldLeft <= 0.f && worldRight >= 0.f)
            {
                sf::Vector2f p1 = worldToScreen(sf::Vector2f(0.f, static_cast<float>(j)), scale, center, ws);
                sf::Vector2f p2 = p1;
                p1.x -= 4.f;
                p2.x += 4.f;

                ticks.append(sf::Vertex(p1, axisColor));
                ticks.append(sf::Vertex(p2, axisColor));

                text.setString(std::to_string(j));
                text.setPosition(p2.x + 6.f, p2.y - 10.f);
                window.draw(text);
            }
        }

        window.draw(ticks);
    }

    // Обозначение единичного отрезка
    sf::VertexArray unitSeg(sf::Lines, 2);
    unitSeg[0] = sf::Vertex(sf::Vector2f(20.f, ws.y - 30.f), axisColor);
    unitSeg[1] = sf::Vertex(sf::Vector2f(20.f + scale, ws.y - 30.f), axisColor);
    window.draw(unitSeg);

    text.setString("1 unit");
    text.setPosition(25.f + scale, ws.y - 40.f);
    window.draw(text);
}
