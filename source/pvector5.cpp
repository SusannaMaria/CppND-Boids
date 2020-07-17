/**
 * @file Pvector.cpp
 * @author Jorge Yanar(https://github.com/jyanar), Susanna Hepp (https://github.com/SusannaMaria)
 * @brief Pvector class implements Euclidian vectors
 * Jorge: Base implementation
 * Susanna: Clean up code, introduce almost_equal function
 * @version 1.0
 * @date 2020-07-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "pvector5.hpp"

namespace ruleof5 {
/**
 * @brief Sets values of x and y for Pvector
 * 
 * @param i 
 * @param o 
 */
void Pvector::set(float i, float o)
{
	p->x = i;
	p->y = o;
}

/**
 * @brief Add Vector to a Pvector
 * 
 * @param v 
 */
void Pvector::addVector(Pvector v)
{
	p->x += v.p->x;
	p->y += v.p->y;
}
 
/**
 * @brief Adds to a Pvector by a constant number
 * 
 * @param s 
 */
void Pvector::addScalar(float s)
{
	p->x += s;
	p->y += s;
}

/**
 * @brief Subtracts 2 vectors
 * 
 * @param v 
 */
void Pvector::subVector(Pvector v)
{
	p->x -= v.p->x;
	p->y -= v.p->y;
}

/**
 * @brief Subtracts two vectors and returns the difference as a vector
 * 
 * @param v 
 * @param v2 
 * @return Pvector 
 */
Pvector Pvector::subTwoVector(Pvector v, Pvector v2)
{
	Pvector tmp;
	v.p->x -= v2.p->x;
	v.p->y -= v2.p->y;
	tmp.set(v.p->x, v.p->y);
	return tmp;
}

/**
 * @brief Adds to a Pvector by a constant number
 * 
 * @param s 
 */
void Pvector::subScalar(float s)
{
	p->x -= s;
	p->y -= s;
}

/**
 * @brief Multiplies 2 vectors
 * 
 * @param v 
 */
void Pvector::mulVector(Pvector v)
{
	p->x *= v.p->x;
	p->y *= v.p->y;
}

/**
 * @brief Adds to a Pvector by a constant number
 * 
 * @param s 
 */
void Pvector::mulScalar(float s)
{
	p->x *= s;
	p->y *= s;
}

/**
 * @brief Divides 2 vectors
 * 
 * @param v 
 */
void Pvector::divVector(Pvector v)
{
	p->x /= v.p->x;
	p->y /= v.p->y;
}

/**
 * @brief Adds to a Pvector by a constant number
 * 
 * @param s 
 */
void Pvector::divScalar(float s)
{
	p->x /= s;
	p->y /= s;
}

/**
 * @brief Limit the Pvector
 * 
 * @param max 
 */
void Pvector::limit(double max)
{
	double size = magnitude();

	if (size > max) {
		set(p->x / size, p->y / size);
	}
}

/**
 * @brief Calculates the distance between the first Pvector and second Pvector
 * 
 * @param v 
 * @return float 
 */
float Pvector::distance(Pvector v) const
{
	float dx = p->x - v.p->x;
	float dy = p->y - v.p->y;
	float dist = sqrt(dx*dx + dy*dy);
	return dist;
}

/**
 * @brief Calculates the dot product of a vector
 * 
 * @param v 
 * @return float 
 */
float Pvector::dotProduct(Pvector v) const
{
	float dot = p->x * v.p->x + p->y * v.p->y;
	return dot;
}

/**
 * @brief Calculates magnitude of referenced object
 * 
 * @return float 
 */
float Pvector::magnitude() const
{
	return sqrt(p->x*p->x + p->y*p->y);
}
/**
 * @brief magnitude of referenced object
 * 
 * @param x 
 */
void Pvector::setMagnitude(float x)
{
	normalize();
	mulScalar(x);
}

/**
 * @brief Calculate the angle between Pvector 1 and Pvector 2
 * 
 * @param v 
 * @return float 
 */
float Pvector::angleBetween(Pvector v) const
{
	if (p->x == 0 && p->y == 0) return 0.0f;
	if (v.p->x == 0 && v.p->y == 0) return 0.0f;

	double dot = p->x * v.p->x + p->y * v.p->y;
	double v1mag = sqrt(p->x * p->x + p->y * p->y);
	double v2mag = sqrt(v.p->x * v.p->x + v.p->y * v.p->y);
	double amt = dot / (v1mag * v2mag); //Based of definition of dot product
	//dot product / product of magnitudes gives amt
	if (amt <= -1) {
		return M_PI;
	}
	else if (amt >= 1) {
		return 0;
	}
	float tmp = acos(amt);
	return tmp;
}

/**
 * @brief normalize divides x and y by magnitude if it has a magnitude.
 * 
 */
void Pvector::normalize()
{
	float m = magnitude();

	if (m > 0) {
		set(p->x / m, p->y / m);
	}
	else {
		set(p->x, p->y);
	}
}

/**
 * @brief Creates and returns a copy of the Pvector used as a parameter
 * 
 * @param v 
 * @return Pvector 
 */
Pvector Pvector::copy(Pvector v)
{
	Pvector copy(v);
	return copy;
}
}