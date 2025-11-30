#include "Scene.hpp"
#include <iostream>

Scene::Scene() = default;

void Scene::init(const sf::RenderWindow& window)
{
    resize(window);
}

bool Scene::loadBackground(const std::string& path)
{
    if (!bgTexture.loadFromFile(path))
    {
        std::cerr << "Failed to load background: " << path << '\n';
        return false;
    }

    bgSprite.setTexture(bgTexture);
    return true;
}

void Scene::resize(const sf::RenderWindow& window)
{
    if (bgTexture.getSize().x == 0)
        return;

    sf::Vector2u ws = window.getSize();
    sf::Vector2u ts = bgTexture.getSize();

    bgSprite.setScale(
        static_cast<float>(ws.x) / ts.x,
        static_cast<float>(ws.y) / ts.y
    );
}

void Scene::drawBackground(sf::RenderWindow& window) const
{
    if (bgTexture.getSize().x == 0)
        return;

    window.draw(bgSprite);
}

void Scene::drawEnvironment(sf::RenderTarget& target,
                            const Plane& plane) const
{
    sf::Vector2u ws = target.getSize();
    float groundY = plane.getGroundY();

    const float w = static_cast<float>(ws.x);

    // Зелёная зона (трава за полосой)
    sf::RectangleShape grass(sf::Vector2f(w, ws.y - groundY));
    grass.setPosition(0.f, groundY);
    grass.setFillColor(sf::Color(80, 134, 23));
    target.draw(grass);

    // Асфальт ВПП
    const float runwayHeight = 70.f;
    sf::RectangleShape runway(sf::Vector2f(w, runwayHeight));
    runway.setFillColor(sf::Color(40, 42, 50));
    runway.setPosition(0.f, groundY - runwayHeight / 2.f);
    target.draw(runway);

    // Боковые белые линии
    sf::RectangleShape sideLine(sf::Vector2f(w, 3.f));
    sideLine.setFillColor(sf::Color(230, 230, 235));

    sideLine.setPosition(0.f, groundY - runwayHeight / 2.f + 6.f);
    target.draw(sideLine);

    sideLine.setPosition(0.f, groundY + runwayHeight / 2.f - 9.f);
    target.draw(sideLine);

    // Центральная пунктирная линия
    float dashLength = 40.f;
    float gapLength  = 30.f;
    float yCenter = groundY;

    sf::RectangleShape dash(sf::Vector2f(dashLength, 4.f));
    dash.setFillColor(sf::Color(245, 245, 250));
    dash.setOrigin(0.f, 2.f);
    dash.setPosition(0.f, yCenter);

    for (float x = 0.f; x < w; x += dashLength + gapLength)
    {
        dash.setPosition(x, yCenter);
        target.draw(dash);
    }

    // Огни по бокам полосы
    sf::CircleShape light(3.f);
    light.setOrigin(3.f, 3.f);
    light.setFillColor(sf::Color(255, 220, 120));

    float leftY  = groundY - runwayHeight / 2.f + 3.f;
    float rightY = groundY + runwayHeight / 2.f - 3.f;

    for (float x = 20.f; x < w; x += 55.f)
    {
        light.setPosition(x, leftY);
        target.draw(light);
        light.setPosition(x, rightY);
        target.draw(light);
    }
}
