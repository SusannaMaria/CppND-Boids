#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Pvector.h"

class Obstacle : public sf::Drawable
{
public:
    Obstacle(float ax=0.f, float ay=0.f, float radius=100.f, size_t pointcloud=10, float detectionradius=100, float fovdistance=200):m_circle(radius, pointcloud ),_detectionradius{detectionradius},_fovdistance{fovdistance}{
        m_circle.setPosition(ax, ay);
        m_circle.setOrigin(radius,radius);
    }

    bool doCollide(float distance);
    bool doCollide(float ax, float ay, float theta);
    Pvector getDistance(float ax, float ay, float theta);
    sf::CircleShape m_circle;
	int _window_width;
	int _window_height;
    float _detectionradius;
    float _fovdistance;

private:
 virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};