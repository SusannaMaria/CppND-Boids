#include <iostream>
#include <cmath>
#include <limits>
#include <type_traits>
#include <algorithm>
using namespace std;

#ifndef PVECTOR_H_
#define PVECTOR_H_


// if(almost_equal(d1, d2, 2))
//     std::cout << "d1 almost equals d2\n";
// else
//     std::cout << "d1 does not almost equal d2\n";
// https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
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

// The Pvector class implements Euclidian vectors -- that is, each vector has
// both a magnitude and a direction. We use Pvectors for implementing movement
// and the three Boid rules -- cohesion, separation, and matching velocity
// through the use of acceleration, force, and velocity vectors.
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

	static Pvector copy(Pvector v);
};

#endif
