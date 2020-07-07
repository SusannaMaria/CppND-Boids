#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>


class Obstacle : public sf::Drawable
{
public:
    Obstacle(float ax=0.f, float ay=0.f, float radius=100.f, size_t pointcloud=30):m_circle(radius, pointcloud ){
        m_circle.setPosition(ax, ay);
    }

    bool doCollide(float distance);
    bool doCollide(float ax, float ay, float theta);
    float getDistance(float ax, float ay, float theta);
    sf::CircleShape m_circle;
	int _window_width;
	int _window_height;

private:
 virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


};