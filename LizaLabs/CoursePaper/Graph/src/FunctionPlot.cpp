#include "FunctionPlot.hpp"
#include <cmath>
#include <iostream>

FunctionPlot::FunctionPlot()
{
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        std::cerr << "Failed to load font assets/arial.ttf\n";
    }
}

float FunctionPlot::f(float x) const
{
    // y = x^2 - 6/(x - 1) + 3
    return x * x - 6.f / (x - 1.f) + 3.f;
}

sf::Vector2f FunctionPlot::worldToScreen(float x, float y,
                                         float scale,
                                         const sf::Vector2f& center,
                                         const sf::Vector2u& winSize) const
{
    float sx = (x - center.x) * scale + winSize.x / 2.f;
    float sy = winSize.y / 2.f - (y - center.y) * scale;
    return sf::Vector2f(sx, sy);
}

void FunctionPlot::draw(sf::RenderWindow& window,
                        float scale,
                        const sf::Vector2f& center)
{
    const sf::Vector2u ws = window.getSize();

    float worldLeft   = center.x - ws.x / (2.f * scale);
    float worldRight  = center.x + ws.x / (2.f * scale);
    float worldBottom = center.y - ws.y / (2.f * scale);
    float worldTop    = center.y + ws.y / (2.f * scale);

    // Цвета: более мягкий синий и приглушённый красный
    sf::Color funcColor(40, 60, 200);
    sf::Color asymColor(200, 60, 60);

    // Шаг по x
    float step = (worldRight - worldLeft) / 1500.f;
    if (step <= 0.f)
        return;

    sf::VertexArray leftPart(sf::LineStrip);
    sf::VertexArray rightPart(sf::LineStrip);

    float eps = step * 2.f;

    for (float x = worldLeft; x <= worldRight; x += step)
    {
        if (std::fabs(x - 1.f) < eps)
            continue; // вокруг асимптоты не рисуем

        float y = f(x);

        // отсекаем слишком большие значения
        if (y < worldBottom - 50.f || y > worldTop + 50.f)
            continue;

        sf::Vector2f p = worldToScreen(x, y, scale, center, ws);

        if (x < 1.f)
            leftPart.append(sf::Vertex(p, funcColor));
        else
            rightPart.append(sf::Vertex(p, funcColor));
    }

    if (leftPart.getVertexCount() > 1)
        window.draw(leftPart);
    if (rightPart.getVertexCount() > 1)
        window.draw(rightPart);

    // Вертикальная асимптота x = 1
    if (worldLeft <= 1.f && worldRight >= 1.f)
    {
        sf::VertexArray asym(sf::Lines, 2);
        asym[0] = sf::Vertex(worldToScreen(1.f, worldBottom, scale, center, ws), asymColor);
        asym[1] = sf::Vertex(worldToScreen(1.f, worldTop,    scale, center, ws), asymColor);
        window.draw(asym);
    }

    // Подпись графика
    sf::Text caption;
    caption.setFont(font);
    caption.setCharacterSize(18);
    caption.setFillColor(sf::Color::Black);
    caption.setString("y = x^2 - 6/(x - 1) + 3");
    caption.setPosition(15.f, 10.f);
    window.draw(caption);
}
