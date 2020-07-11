#pragma once

#include <vector>
#include "obstacle.hpp"
#include "boid.hpp"

#include <SFML/Graphics/Drawable.hpp>

class ObstaclesContainer : public sf::Drawable
{
    public:
        ObstaclesContainer(){}
        ObstaclesContainer(int width, int height, int maxradius);

        void avoid(shared_ptr<Boid> boid);
    private:
	    vector<shared_ptr<Obstacle> > obstacles;

 virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;        
};
