/**
 * @file pvector.cpp
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
#include <future>
#include "pvector.hpp"

/**
 * @brief Sets values of x and y for Pvector
 * 
 * @param i 
 * @param o 
 */
void Pvector::set(float i, float o)
{
	x = i;
	y = o;
}

/**
 * @brief Add Vector to a Pvector
 * 
 * @param v 
 */
void Pvector::addVector(Pvector v)
{
	x += v.x;
	y += v.y;
}
 
/**
 * @brief Adds to a Pvector by a constant number
 * 
 * @param s 
 */
void Pvector::addScalar(float s)
{
	x += s;
	y += s;
}

/**
 * @brief Subtracts 2 vectors
 * 
 * @param v 
 */
void Pvector::subVector(Pvector v)
{
	x -= v.x;
	y -= v.y;
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
	v.x -= v2.x;
	v.y -= v2.y;
	tmp.set(v.x, v.y);
	return tmp;
}

/**
 * @brief Adds to a Pvector by a constant number
 * 
 * @param s 
 */
void Pvector::subScalar(float s)
{
	x -= s;
	y -= s;
}

/**
 * @brief Multiplies 2 vectors
 * 
 * @param v 
 */
void Pvector::mulVector(Pvector v)
{
	x *= v.x;
	y *= v.y;
}

/**
 * @brief Adds to a Pvector by a constant number
 * 
 * @param s 
 */
void Pvector::mulScalar(float s)
{
	x *= s;
	y *= s;
}

/**
 * @brief Divides 2 vectors
 * 
 * @param v 
 */
void Pvector::divVector(Pvector v)
{
	x /= v.x;
	y /= v.y;
}

/**
 * @brief Adds to a Pvector by a constant number
 * 
 * @param s 
 */
void Pvector::divScalar(float s)
{
	x /= s;
	y /= s;
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
		set(x / size, y / size);
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
	float dx = x - v.x;
	float dy = y - v.y;
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
	float dot = x * v.x + y * v.y;
	return dot;
}

/**
 * @brief Calculates magnitude of referenced object
 * 
 * @return float 
 */
float Pvector::magnitude() const
{
	return sqrt(x*x + y*y);
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


void cppnd_sqrt(std::promise<double>&& floatPromise, double a, double b){
  double val = sqrt(a*a + b*b);
  floatPromise.set_value(val);

}
void cppnd_dot(std::promise<double>&& floatPromise, float x1, float x2, float y1, float y2){
  double val = x1 * x2 + y1 * y2;
  floatPromise.set_value(val);

}

/**
 * @brief Calculate the angle between Pvector 1 and Pvector 2
 * 
 * @param v 
 * @return float 
 */
float Pvector::angleBetween(Pvector v) const
{
	if (x == 0 && y == 0) return 0.0f;
	if (v.x == 0 && v.y == 0) return 0.0f;
	
	// define the promises
  	std::promise<double> sqrtv1mag;
  	std::promise<double> sqrtv2mag;
	std::promise<double> dotpromise;

	// get the futures
	std::future<double> v1Result= sqrtv1mag.get_future();
	std::future<double> v2Result= sqrtv2mag.get_future();
	std::future<double> dotResult= dotpromise.get_future();

	std::thread v1Thread(cppnd_sqrt,std::move(sqrtv1mag),x,y);
	std::thread v2Thread(cppnd_sqrt,std::move(sqrtv2mag),v.X(),v.Y());
 	std::thread dotThread(cppnd_dot,std::move(dotpromise),X(),Y(),v.X(),v.Y());

	double dot = dotResult.get();
	double v1mag = v1Result.get();
	double v2mag = v2Result.get();
	v1Thread.join();
	v2Thread.join();
	dotThread.join();

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
		set(x / m, y / m);
	}
	else {
		set(x, y);
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
	Pvector copy(v.x, v.y);
	return copy;
}
