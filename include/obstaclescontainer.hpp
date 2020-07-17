/**
 * @file obstaclescontainer.hpp
 * @author Susanna Hepp (https://github.com/SusannaMaria)
 * @brief Container to keep obstacles
 * @version 0.1
 * @date 2020-07-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once

#include <vector>

#include <SFML/Graphics/Drawable.hpp>

#include "flock.hpp"
#include "obstacle.hpp"
#include "boid.hpp"

class ObstaclesContainer : public sf::Drawable
{
public:
    ObstaclesContainer(shared_ptr<Flock> flockptr, int width, int height, int maxradius);
    void avoid(shared_ptr<Boid> boid);

private:
    vector<shared_ptr<Obstacle> > obstacles;
    shared_ptr<Flock> myFlock;
    int _amountobstacles;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
