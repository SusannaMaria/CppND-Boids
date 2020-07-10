#define _USE_MATH_DEFINES
#include "obstacle.hpp"
#include <cmath>
#define PI 3.14159265
#include <iostream>
#include "Boid.h"
#include "Pvector.h"
void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.texture = NULL;
    target.draw(m_circle, states);
}

void Obstacle::avoid(Boid &boid){
   float steerAngle = 0.0;
   float ax;
   float ay;
    float theta;

    Pvector obspos{m_circle.getPosition().x,m_circle.getPosition().y};

    float distance = obspos.distance(boid.location);
    
    if(distance < 2*_detectionradius){
       
       Pvector distvec = Pvector::subTwoVector(obspos, boid.location);
       
       float dotproduct = distvec.dotProduct(boid.velocity);
        
       if(dotproduct > 0.0){
           float tangentAngle = asin(_detectionradius/distance);

          
           float directionAngle = acos(dotproduct/(distance*boid.velocity.magnitude()));

				if(directionAngle < tangentAngle)
					steerAngle += (tangentAngle - directionAngle);
       }
    }
    Pvector result;
    Pvector velold = boid.velocity;
    result.x = velold.x * cos(steerAngle)+ velold.y * sin(steerAngle);
	result.y = -1 * velold.x * sin(steerAngle)+ velold.y * cos(steerAngle);

    boid.velocity=result;

}
