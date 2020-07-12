#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "pvector.hpp"
#include <memory>
class Boid;
class Obstacle : public sf::Drawable
{
public:
    Obstacle(float ax = 0.f, float ay = 0.f, float radius = 100.f, size_t pointcloud = 20) : m_circle(radius, pointcloud), _detectionradius{radius * 3}
    {
        m_circle.setPosition(ax, ay);
        m_circle.setOrigin(radius, radius);
        m_circle.setFillColor(sf::Color(150, 50, 250));
        m_circle.setOutlineThickness(3);
        m_circle.setOutlineColor(sf::Color(250, 150, 100));
    }
    void avoid(shared_ptr<Boid> boid);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::CircleShape m_circle;
    float _detectionradius;
};