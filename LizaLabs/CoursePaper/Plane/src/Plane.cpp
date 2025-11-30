#include "Plane.hpp"
#include <algorithm>
#include <vector>

// КОНСТРУКТОР / СБРОС
Plane::Plane(const sf::Vector2u& winSize)
{
    reset(winSize);
}

void Plane::reset(const sf::Vector2u& winSize)
{
    float W = static_cast<float>(winSize.x);
    float H = static_cast<float>(winSize.y);

    groundY = H * 0.75f;
    cruiseY = groundY - 180.f;

    descentStartX = W * 0.25f;
    descentEndX   = W * 0.60f;

    position.x = -300.f;
    position.y = cruiseY;

    vx    = 220.f;
    decel = 95.f;

    phase = PlanePhase::Cruise;
}

// ОБНОВЛЕНИЕ
void Plane::update(float dt)
{
    switch (phase)
    {
        case PlanePhase::Cruise:
            position.x += vx * dt;
            if (position.x > descentStartX)
                phase = PlanePhase::Descent;
            break;

        case PlanePhase::Descent:
        {
            position.x += vx * dt;

            float t = (position.x - descentStartX) /
                      (descentEndX - descentStartX);
            t = std::clamp(t, 0.f, 1.f);

            float targetY = groundY - 40.f;
            position.y = cruiseY + (targetY - cruiseY) * t;

            if (t >= 1.f)
            {
                position.y = targetY;
                phase = PlanePhase::Rollout;
            }
            break;
        }

        case PlanePhase::Rollout:
            position.x += vx * dt;
            vx -= decel * dt;
            if (vx <= 0.f)
            {
                vx = 0.f;
                phase = PlanePhase::Stopped;
            }
            break;

        case PlanePhase::Stopped:
            break;
    }
}

// РИСОВАНИЕ 
void Plane::draw(sf::RenderTarget& target) const
{
    // Наклон в зависимости от фазы
    float angle = 0.f;
    if (phase == PlanePhase::Cruise)  angle = -3.f;
    if (phase == PlanePhase::Descent) angle = -6.f;

    sf::Transform T;
    T.translate(position);
    T.rotate(angle);

    auto drawWithT = [&](const sf::Shape& s)
    {
        sf::RenderStates st;
        st.transform = T;
        target.draw(s, st);
    };

    // Базовые размеры 
    const float BODY_LEN = 150.f;
    const float BODY_H   = 26.f;
    const float halfL    = BODY_LEN * 0.5f;
    const float halfH    = BODY_H   * 0.5f;

    float frontX =  halfL;
    float backX  = -halfL;

    // Цвета
    sf::Color bodyColor   (240, 240, 245);
    sf::Color outline     (60, 60, 90);
    sf::Color wingColor   (205, 215, 235);
    sf::Color glassColor  (135, 175, 225);
    sf::Color windowColor (120, 160, 210);
    sf::Color wheelColor  (35, 35, 35);

    // Фюзеляж (прямоугольник-основа)
    sf::RectangleShape body(sf::Vector2f(BODY_LEN, BODY_H));
    body.setFillColor(bodyColor);
    body.setOutlineThickness(1.f);
    body.setOutlineColor(outline);
    body.setOrigin(halfL, halfH);
    body.setPosition(0.f, 0.f);

    // Обтекаемый нос
    sf::ConvexShape nose;
    nose.setPointCount(5);
    nose.setPoint(0, sf::Vector2f(frontX,      -halfH));         // верх корпуса
    nose.setPoint(1, sf::Vector2f(frontX + 16, -halfH * 0.7f));  // верхняя кромка
    nose.setPoint(2, sf::Vector2f(frontX + 24,  0.f));           // острый нос
    nose.setPoint(3, sf::Vector2f(frontX + 16,  halfH * 0.7f));  // нижняя кромка
    nose.setPoint(4, sf::Vector2f(frontX,       halfH));         // низ корпуса
    nose.setFillColor(bodyColor);
    nose.setOutlineThickness(1.f);
    nose.setOutlineColor(outline);

    // Обтекаемый хвост
    sf::ConvexShape tailCone;
    tailCone.setPointCount(4);
    tailCone.setPoint(0, sf::Vector2f(backX,      -halfH));        // верх корпуса
    tailCone.setPoint(1, sf::Vector2f(backX - 22, -halfH * 0.3f)); // верхняя кромка
    tailCone.setPoint(2, sf::Vector2f(backX - 22,  halfH * 0.3f)); // нижняя кромка
    tailCone.setPoint(3, sf::Vector2f(backX,       halfH));        // низ корпуса
    tailCone.setFillColor(bodyColor);
    tailCone.setOutlineThickness(1.f);
    tailCone.setOutlineColor(outline);

    // Крыло
    sf::ConvexShape wing;
    wing.setPointCount(4);

    wing.setPoint(0, sf::Vector2f(-27.f,  2.f));   // у корпуса спереди (левее)
    wing.setPoint(1, sf::Vector2f(-70.f, 22.f));   // задняя внутренняя
    wing.setPoint(2, sf::Vector2f(  5.f, 18.f));   // внешняя кромка
    wing.setPoint(3, sf::Vector2f( 30.f,  2.f));   // назад к корпусу

    wing.setFillColor(wingColor);
    wing.setOutlineThickness(1.f);
    wing.setOutlineColor(outline);
    wing.setPosition(0.f, 4.f);

    // Киль
    sf::ConvexShape fin;
    fin.setPointCount(3);
    fin.setPoint(0, sf::Vector2f(backX + 14.f, -halfH));         // основание у корпуса
    fin.setPoint(1, sf::Vector2f(backX -  8.f, -halfH - 30.f));  // вершина
    fin.setPoint(2, sf::Vector2f(backX + 32.f, -halfH));         // основание сзади
    fin.setFillColor(wingColor);
    fin.setOutlineThickness(1.f);
    fin.setOutlineColor(outline);

    // Кабина 
    sf::ConvexShape cockpit;
    cockpit.setPointCount(4);
    cockpit.setPoint(0, sf::Vector2f(frontX - 26.f, -halfH * 0.9f));
    cockpit.setPoint(1, sf::Vector2f(frontX -  4.f, -halfH * 0.7f));
    cockpit.setPoint(2, sf::Vector2f(frontX - 10.f, -halfH * 0.25f));
    cockpit.setPoint(3, sf::Vector2f(frontX - 34.f, -halfH * 0.4f));
    cockpit.setFillColor(glassColor);
    cockpit.setOutlineThickness(1.f);
    cockpit.setOutlineColor(outline);

    // Иллюминаторы
    std::vector<sf::Vector2f> windowLocalPos;
    float startX = backX + 35.f;
    float stepX  = 20.f;
    float winY   = -halfH * 0.10f;   // ниже, чтобы не пересекаться с кабиной

    for (int i = 0; i < 4; ++i)
        windowLocalPos.emplace_back(startX + i * stepX, winY);

    sf::CircleShape windowCircle(3.5f);
    windowCircle.setOrigin(3.5f, 3.5f);
    windowCircle.setFillColor(windowColor);
    windowCircle.setOutlineThickness(0.f);

    // Шасси
    bool wheelsOut = (phase == PlanePhase::Rollout ||
                      phase == PlanePhase::Stopped);

    sf::CircleShape wheel(5.f);
    wheel.setOrigin(5.f, 5.f);
    wheel.setFillColor(wheelColor);

    std::vector<sf::Vector2f> wheelLocalPos;
    if (wheelsOut)
    {
        wheelLocalPos.emplace_back(-20.f, halfH + 18.f);
        wheelLocalPos.emplace_back( 15.f, halfH + 18.f);
    }

    // ЗАКРЫЛКИ
    bool flapsOut = (phase == PlanePhase::Descent ||
                     phase == PlanePhase::Rollout ||
                     phase == PlanePhase::Stopped);

    // чуть темнее крыла, чтобы видно было
    sf::Color flapColor(
        static_cast<sf::Uint8>(wingColor.r - 10),
        static_cast<sf::Uint8>(wingColor.g - 10),
        static_cast<sf::Uint8>(wingColor.b - 10)
    );

    // Основной закрылок ближе к фюзеляжу
    sf::RectangleShape flap1(sf::Vector2f(26.f, 4.f));
    flap1.setFillColor(flapColor);
    flap1.setOutlineThickness(0.8f);
    flap1.setOutlineColor(outline);
    flap1.setOrigin(0.f, 2.f);
    // задняя кромка крыла 
    flap1.setPosition(-48.f, 20.f);
    flap1.setRotation(6.f);  

    // Внешний закрылок поменьше
    sf::RectangleShape flap2(sf::Vector2f(20.f, 4.f));
    flap2.setFillColor(flapColor);
    flap2.setOutlineThickness(0.8f);
    flap2.setOutlineColor(outline);
    flap2.setOrigin(0.f, 2.f);
    flap2.setPosition(-15.f, 19.f);
    flap2.setRotation(5.f);

    // РИСОВАНИЕ

    drawWithT(body);
    drawWithT(nose);
    drawWithT(tailCone);
    drawWithT(wing);
    drawWithT(fin);
    drawWithT(cockpit);

    // Закрылки — поверх крыла, только если выпущены
    if (flapsOut)
    {
        drawWithT(flap1);
        drawWithT(flap2);
    }

    // окна
    for (auto p : windowLocalPos)
    {
        windowCircle.setPosition(p);
        drawWithT(windowCircle);
    }

    // шасси
    if (wheelsOut)
    {
        for (auto p : wheelLocalPos)
        {
            wheel.setPosition(p);
            drawWithT(wheel);
        }
    }
}
