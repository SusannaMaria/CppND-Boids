#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Pvector.h"
#include <memory>
class Boid;
class Obstacle : public sf::Drawable
{
public:
    Obstacle(float ax=0.f, float ay=0.f, float radius=100.f, size_t pointcloud=10):m_circle(radius, pointcloud ),_detectionradius{radius*2}{
        m_circle.setPosition(ax, ay);
        m_circle.setOrigin(radius,radius);
    }
    void avoid(shared_ptr<Boid> boid);
    void avoid(Boid &boid);
    bool doCollide(float distance);
    bool doCollide(float ax, float ay, float theta);
    float getDistance(float ax, float ay, float theta);
    sf::CircleShape m_circle;
    float _detectionradius;
    float _fovdistance;

private:
 virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};