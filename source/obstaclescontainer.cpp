/**
 * @file obstaclescontainer.cpp
 * @author Susanna Hepp (https://github.com/SusannaMaria)
 * @brief Container to keep obstacles
 * @version 0.1
 * @date 2020-07-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "obstaclescontainer.hpp"

/**
 * @brief Construct a new ObstaclesContainer object
 * 
 * @param flockptr 
 * @param width 
 * @param height 
 * @param maxradius 
 */
ObstaclesContainer::ObstaclesContainer(shared_ptr<Flock> flockptr, int width, int height, int maxradius)
{   
    this->myFlock = flockptr;
    _amountobstacles = myFlock->AmountObstacles();
    for (int i = 0; i < _amountobstacles; i++)
    {
        std::shared_ptr<Obstacle> obstacle = std::make_shared<Obstacle>(rand() % width, rand() % height, rand() % maxradius);
        obstacles.push_back(obstacle);
    }
}

/**
 * @brief Iterate thru the obstacles, every boid is checked against all obstacles, but only if the boid is in a certain range
 * 
 * @param boid 
 */
void ObstaclesContainer::avoid(std::shared_ptr<Boid> boid)
{
    for (int j = 0; j < _amountobstacles; j++)
    {
        obstacles[j]->avoid(boid);
    }
}

/**
 * @brief draw function
 * 
 * @param target 
 * @param states 
 */
void ObstaclesContainer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(const auto& obj : obstacles){
        target.draw(*obj, states);
    }
}