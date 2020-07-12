/**
 * @file polarvector.hpp
 * @author https://www.sfml-dev.org (https://github.com/SFML/SFML/wiki/Source%3A-High-Performance-Sprite-Container)
 * @brief Polar Vector class uses radians as angles, where r is the radius and t is the angle.
 * @version 1.0
 * @date 2013-01-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <SFML/System/Vector2.hpp>
class PolarVector
{ 
  public:
        float r;
        float t;

        PolarVector();
        PolarVector(float radius, float angle);

        sf::Vector2f TurnToRectangular() const;
  private:
        static const float EPSILON;

        friend bool operator ==(const PolarVector& left, const PolarVector& right);
};

PolarVector TurnToPolar(const sf::Vector2f& point);

bool operator ==(const PolarVector& left, const PolarVector& right);

bool operator !=(const PolarVector& left, const PolarVector& right);

