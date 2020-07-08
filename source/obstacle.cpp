#include "obstacle.hpp"
#include <cmath>
#define PI 3.14159265
#include <iostream>
void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.texture = NULL;
    target.draw(m_circle, states);
}

Pvector Obstacle::getDistance(float ax, float ay, float theta)
{

    Pvector pv{0, 0};

    float ay_cor = _window_height - ay;

    float bx;
    float by;

    sf::Vector2f m = m_circle.getPosition();

    m.y = _window_height - m.y;

    if (theta == 90.f)
    {
        pv.x = 1 / abs(ax - m.x);
        pv.y = -1 / abs(ax - m.x);
        return pv;
    }

    float m1 = tan(theta * PI / 180.0);

    float b1 = ay_cor - (m1 * ax);

    if (m1 == 0.f)
    {
        pv.x = 1 / abs(b1 - m.y);
        pv.y = -1 / abs(b1 - m.y);
        return pv;
    }
    float m2 = -1.0 / m1;

    float b2 = m.y - (m2 * m.x);

    float xs = (b2 - b1) / (m1 - m2);
    float ys = m1 * xs + b1;

    float c3 = ax - xs;
    float c4 = ay - ys;

    float distancetolot = sqrt(c3 * c3 + c4 * c4);

    if (distancetolot > _fovdistance)
    {
        return pv;
    }

    float c1 = m.x - xs;
    float c2 = m.y - ys;

    float distance = sqrt(c1 * c1 + c2 * c2);



    if (ys > m1 * m.x + b1)
    {
        distance = -distance;
    }
    cout << distance  << endl;
    pv.x = 1 / distance;
    pv.y = -1 / distance;
    return pv;
}

bool Obstacle::doCollide(float distance)
{

    if (distance > _detectionradius)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// bool Obstacle::doCollide(float ax, float ay, float theta)
// {
//     float distance = getDistance(ax, ay, theta);

//     if (abs(distance) > _detectionradius)
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }
