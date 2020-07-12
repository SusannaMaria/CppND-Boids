/**
 * @file obstacle.cpp
 * @author Susanna Hepp (https://github.com/SusannaMaria)
 * @brief Obstacle avoid for boids
 * @version 1.0
 * @date 2020-07-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#define _USE_MATH_DEFINES
#include <cmath>
#define PI 3.14159265
#include <iostream>
#include "pvector.hpp"
#include "boid.hpp"
#include "obstacle.hpp"

/**
 * @brief draw function
 * 
 * @param target 
 * @param states 
 */
void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.texture = NULL;
    target.draw(m_circle, states);
}

/**
 * @brief Avoid obstacle, calculated velcity to prevent crash, based on distance and angle of boid to center of obstacles
 * 
 * @param boid 
 */
void Obstacle::avoid(shared_ptr<Boid> boid)
{
    float steerAngle = 0.0;

    Pvector obspos{m_circle.getPosition().x, m_circle.getPosition().y};

    float distance = obspos.distance(boid->Location());

    if (distance < 2 * _detectionradius)
    {

        Pvector distvec = Pvector::subTwoVector(obspos, boid->Location());

        float dotproduct = distvec.dotProduct(boid->Velocity());

        if (dotproduct > 0.0)
        {
            float tangentAngle = asin(_detectionradius / distance);

            float directionAngle = acos(dotproduct / (distance * boid->Velocity().magnitude()));

            if (directionAngle < tangentAngle)
                steerAngle += (tangentAngle - directionAngle);
        }
    }
    Pvector result;
    Pvector velold = boid->Velocity();
    result.x = velold.x * cos(steerAngle) + velold.y * sin(steerAngle);
    result.y = -1 * velold.x * sin(steerAngle) + velold.y * cos(steerAngle);

    boid->Velocity(result);
}
