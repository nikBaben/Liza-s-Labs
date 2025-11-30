#pragma once

#include <SFML/Graphics.hpp>

enum class PlanePhase
{
    Cruise,   // полёт на высоте
    Descent,  // снижение
    Rollout,  // пробег по полосе
    Stopped   // полная остановка
};

class Plane
{
public:
    explicit Plane(const sf::Vector2u& winSize);

    void reset(const sf::Vector2u& winSize);
    void update(float dt);                  // dt уже с учётом speedFactor
    void draw(sf::RenderTarget& target) const;

    bool isStopped() const { return phase == PlanePhase::Stopped; }

    float getGroundY() const { return groundY; }

private:
    sf::Vector2f position;  // центр самолёта
    float vx;               // текущая горизонтальная скорость (px/s)
    float cruiseY;          // высота полёта
    float groundY;          // уровень земли
    float descentStartX;    // x, где начинаем снижение
    float descentEndX;      // x касания
    float decel;            // замедление на полосе
    PlanePhase phase;
};
