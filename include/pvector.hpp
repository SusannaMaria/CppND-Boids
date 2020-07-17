/**
 * @file pvector.cpp
 * @author Jorge Yanar(https://github.com/jyanar), Susanna Hepp (https://github.com/SusannaMaria)
 * @brief Pvector class implements Euclidian vectors
 * Jorge: Base implementation
 * Susanna: Clean up code, almost_equal function
 * @version 1.0
 * @date 2020-07-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <iostream>
#include <cmath>
#include <limits>
#include <type_traits>
#include <algorithm>
using namespace std;

/**
 * @brief almost_equal template function 
 * 
 * @tparam T 
 * @param x 
 * @param y 
 * @param ulp 
 * @return std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type 
 */
template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    almost_equal(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x-y) <= std::numeric_limits<T>::epsilon() * std::fabs(x+y) * ulp
        // unless the result is subnormal
        || std::fabs(x-y) < std::numeric_limits<T>::min();
}


/**
 * @brief The Pvector class implements Euclidian vectors - that is, each vector has
 * both a magnitude and a direction. We use Pvectors for implementing movement
 * and the three Boid rules -- cohesion, separation, and matching velocity
 * through the use of acceleration, force, and velocity vectors.
 * 
 */
class Pvector {

public:
	float x;
	float y;

	//Constructors
	Pvector() {}

	Pvector(float xComp, float yComp)
	{
		x = xComp;
		y = yComp;
	}

	bool operator==(const Pvector& lhs)
	{
		return (almost_equal(x, lhs.x, 2) && almost_equal(y, lhs.y, 2));
	}

	//Mutator Functions
	void set(float x, float y);

	//Scalar functions scale a vector by a float
	void addVector(Pvector v);
	void addScalar(float x);

	void subVector(Pvector v);
	static Pvector subTwoVector(Pvector v, Pvector v2);
	void subScalar(float x);

	void mulVector(Pvector v);
	void mulScalar(float x);

	void divVector(Pvector v);
	void divScalar(float x);

	void limit(double max);

	//Calculating Functions
	float distance(Pvector v) const;
	float dotProduct(Pvector v) const;
	float magnitude() const;
	void setMagnitude(float x);
	float angleBetween(Pvector v) const;
	void normalize();

    float X() const{ return x;}
    float Y() const{ return y;}
    void X(float my_x){ x=my_x;}
    void Y(float my_y){ y=my_y;}

	static Pvector copy(Pvector v);
};
