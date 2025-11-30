#include "PlaneApp.hpp"
#include <iostream>
#include <sstream>

PlaneApp::PlaneApp()
    : window(
        sf::VideoMode(900, 600),
        "Plane Landing",
        sf::Style::Titlebar | sf::Style::Close,
        // включаем сглаживание: 3-й параметр = antialiasingLevel
        sf::ContextSettings(0, 0, 8))
    , plane(window.getSize())
    , speedFactor(1.f)
    , paused(true)
{
    window.setFramerateLimit(60);

    scene.init(window);
    scene.loadBackground("assets/background.png");

    sceneTexture.create(window.getSize().x, window.getSize().y);

    if (!font.loadFromFile("assets/arial.ttf"))
    {
        std::cerr << "Failed to load assets/arial.ttf\n";
    }

    hudText.setFont(font);
    hudText.setCharacterSize(16);
    hudText.setFillColor(sf::Color::Black);
    hudText.setPosition(10.f, 10.f);
}

void PlaneApp::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void PlaneApp::processEvents()
{
    sf::Event ev;
    while (window.pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (ev.type == sf::Event::KeyPressed)
        {
            // Esc — выход
            if (ev.key.code == sf::Keyboard::Escape)
                window.close();

            // Space — запуск/пауза, если стоим — перезапуск
            if (ev.key.code == sf::Keyboard::Space)
            {
                if (paused && plane.isStopped())
                {
                    plane.reset(window.getSize());
                }
                paused = !paused;
            }

            // + / - — скорость анимации
            if (ev.key.code == sf::Keyboard::Add ||
                ev.key.code == sf::Keyboard::Equal) // Shift + '='
            {
                speedFactor *= 1.2f;
                if (speedFactor > 5.f) speedFactor = 5.f;
            }
            else if (ev.key.code == sf::Keyboard::Subtract ||
                     ev.key.code == sf::Keyboard::Dash)
            {
                speedFactor /= 1.2f;
                if (speedFactor < 0.2f) speedFactor = 0.2f;
            }
        }
    }
}

void PlaneApp::update(float dt)
{
    if (!paused)
    {
        plane.update(dt * speedFactor);
    }

    // HUD — wide-строка, чтобы кириллица работала корректно
    std::wostringstream wss;
    wss.setf(std::ios::fixed);
    wss.precision(1);

    wss << L"[Space] старт / пауза   "
        << L"[+]/[-] скорость x" << speedFactor
        << L"   [Esc] выход";

    if (paused && plane.isStopped())
        wss << L"   (нажмите пробел для старта)";

    hudText.setString(wss.str());
}

void PlaneApp::render()
{
    window.clear(sf::Color::Black);

    // 1. Фон (из файла) — сразу в окно
    scene.drawBackground(window);

    // 2. Все остальные объекты — в render texture
    sceneTexture.clear(sf::Color::Transparent);
    scene.drawEnvironment(sceneTexture, plane);
    plane.draw(sceneTexture);
    sceneTexture.display();

    sf::Sprite sceneSprite(sceneTexture.getTexture());
    window.draw(sceneSprite);

    // 3. HUD
    window.draw(hudText);

    window.display();
}
