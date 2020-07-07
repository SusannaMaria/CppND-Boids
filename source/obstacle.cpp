#include "obstacle.hpp"
#include <cmath>
#define PI 3.14159265
#include <iostream>
void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    states.texture = NULL;
    target.draw(m_circle, states);
}

float Obstacle::getDistance(float ax, float ay, float theta){
        //sf::Vector2f duda;

    float ay_cor = _window_height-ay;

    float bx;
    float by;

    sf::Vector2f m = m_circle.getPosition();
    
    if (theta==90.f){
        return abs(ax-m.x);
    }

    float m1 = tan(theta* PI / 180.0 );

    float b1 = ay_cor - (m1 * ax);

       if (m1==0.f){
        return abs(b1-m.y);
    } 
    float m2 = -1.0 / m1;

    float b2 = m.y - (m2 * m.x);

    float xs = (b2 - b1) / (m1 - m2);
    float ys = m1 * xs + b1;

    float c1 = m.x - xs;
    float c2 = m.y - ys;
    float distance = sqrt(c1 * c1 + c2 * c2);
    return distance;
}

bool Obstacle::doCollide(float distance){

    if (distance < m_circle.getRadius())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Obstacle::doCollide(float ax, float ay, float theta)
{
    float distance = getDistance(ax, ay, theta);

    if (distance < m_circle.getRadius())
    {
        return true;
    }
    else
    {
        return false;
    }
}
