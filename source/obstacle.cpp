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

// //steers a flock to avoid an obstacle
// float GLBox::avoidObstacles(int boidNum)
// {
// 	Boid * b = boidList.at(boidNum);

// 	float steerAngle = 0.0;
	
// 	for(int i=0; i<obstacleList.size(); i++)
// 	{
// 		Obstacle obs = obstacleList[i];

// 		//find if boid is near the obstacle
// 		Vector3d vec = obs.center - b->pos;	//vector joining the centers
// 		float distBetweenCenters = vec.length();
// 		if(distBetweenCenters < 2*obs.radius)
// 		{
// 			float dotProduct = dot(vec, b->vel);
// 			//find if boid is movind towards the obstacle
// 			if(dotProduct > 0.0)
// 			{
// 				//angle tangent from boid makes with the line joining the center
// 				//of the obstable
// 				float tangentAngle = asin(obs.radius/distBetweenCenters);
// 				//angle between direction of boid and line joining the center
// 				float directionAngle = acos(dotProduct/(vec.length()*b->vel.length()));

// 				if(directionAngle < tangentAngle)
// 					steerAngle += (tangentAngle - directionAngle);
// 				//printf("obstruction: %f\n", steerAngle * 180/3.14);
// 			}
// 		}
// 	}

// 	return steerAngle;
// }
