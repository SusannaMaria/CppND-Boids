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
#include "polarvector.hpp"
#include <cmath>

const float PolarVector::EPSILON = 0.0001;

PolarVector::PolarVector()
  :r(0.0), t(0.0)
{}

PolarVector::PolarVector(float radius, float angle)
  :r(radius), t(angle)
{}

sf::Vector2f PolarVector::TurnToRectangular() const
{
  sf::Vector2f Rect;
  Rect.x = static_cast<float>(r*std::cos(t)); Rect.y = static_cast<float>(r*std::sin(t));
  return Rect;
}

bool operator ==(const PolarVector& left, const PolarVector& right)
{
  float diffR = left.r - right.r;
  float diffA = left.t - right.t;
  return ((diffR <= PolarVector::EPSILON) && (diffA <= PolarVector::EPSILON));
}

bool operator !=(const PolarVector& left, const PolarVector& right)
{ return !(left == right); }

PolarVector TurnToPolar(const sf::Vector2f& point)
{
    PolarVector PV;
    PV.r = sqrt((point.x * point.x) + (point.y * point.y));
    PV.t = std::atan2(point.y, point.x);
    return PV;
}

