#include "obstaclescontainer.hpp"

#define OBSTACLE_AMOUNT 5

ObstaclesContainer::ObstaclesContainer(int width, int height, int maxradius)
{
    for (int i = 0; i < OBSTACLE_AMOUNT; i++)
    {
        std::shared_ptr<Obstacle> obstacle = std::make_shared<Obstacle>(rand() % width, rand() % height, rand() % maxradius);
        obstacles.push_back(obstacle);
    }
}

void ObstaclesContainer::avoid(std::shared_ptr<Boid> boid)
{
    for (int j = 0; j < OBSTACLE_AMOUNT; j++)
    {
        obstacles[j]->avoid(boid);
    }
}
void ObstaclesContainer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(const auto& obj : obstacles){
        target.draw(*obj, states);
    }
}