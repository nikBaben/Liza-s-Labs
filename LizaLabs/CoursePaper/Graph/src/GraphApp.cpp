#include "GraphApp.hpp"
#include <cmath>

GraphApp::GraphApp()
    : window(sf::VideoMode(900, 600), "Graph Plot")
    , scale(40.f)          // 40 пикселей на единицу — комфортный стартовый масштаб
    , center(4.f, 15.f)    // центрируем график более «спокойно»
{
    window.setFramerateLimit(60);
}

void GraphApp::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void GraphApp::processEvents()
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
            // ВЫХОД 
            if (ev.key.code == sf::Keyboard::Escape)
                window.close();

            // МАСШТАБ 
            // NumPad: + и -
            if (ev.key.code == sf::Keyboard::Add ||
                ev.key.code == sf::Keyboard::Equal)   // основная клавиатура: Shift + =
            {
                scale *= 1.1f;
            }
            else if (ev.key.code == sf::Keyboard::Subtract ||
                     ev.key.code == sf::Keyboard::Dash) // основная клавиатура: -
            {
                scale /= 1.1f;
            }

            if (scale < 5.f)   scale = 5.f;
            if (scale > 200.f) scale = 200.f;

            // ПЕРЕМЕЩЕНИЕ ТОЛЬКО WASD 
            float step = 0.5f; // шаг в мировых единицах

            switch (ev.key.code)
            {
            case sf::Keyboard::A: // влево
                center.x -= step;
                break;
            case sf::Keyboard::D: // вправо
                center.x += step;
                break;
            case sf::Keyboard::W: // вверх (y растёт)
                center.y += step;
                break;
            case sf::Keyboard::S: // вниз (y уменьшается)
                center.y -= step;
                break;
            default:
                break;
            }
        }
    }
}

void GraphApp::update(){}

void GraphApp::render()
{
    window.clear(sf::Color(245, 245, 245));

    coords.draw(window, scale, center);
    plot.draw(window, scale, center);

    window.display();
}
