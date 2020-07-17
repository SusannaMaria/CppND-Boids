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

namespace ruleof5 {
/**
 * @brief almost_equal template function 
 * 
 * @tparam T 
 * @param x 
 * @param y 
 * @param ulp 
 * @return std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type 
 */
template <class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x - y) <= std::numeric_limits<T>::epsilon() * std::fabs(x + y) * ulp
           // unless the result is subnormal
           || std::fabs(x - y) < std::numeric_limits<T>::min();
}

class BoidPoint
{
public:
    BoidPoint(float x, float y) : x{x}, y{y} {}
    BoidPoint() : x{0.f}, y{0.f} {}
    BoidPoint(BoidPoint const &other) : x{other.x}, y{other.y} {}

    float x = 0.f;
    float y = 0.f;
};

class Pvector
{
public:
    Pvector()
        : p{new BoidPoint{}}
    {
    }

   Pvector(float x, float y){
       p=new BoidPoint(x,y);
   }

    bool operator==(const Pvector &lhs)
    {
        return (almost_equal(p->x, lhs.p->x, 2) && almost_equal(p->y, lhs.p->y, 2));
    }

    // Rule of 5 implementation
    /**
     * @brief #2 Copy Constructor
     * 
     * @param other 
     */
    Pvector(const Pvector &other)
        : p{new BoidPoint{*(other.p)}}
    {
    }

    /**
     * @brief #4 Move Constructor
     * 
     * @param other 
     */
    Pvector(Pvector &&other)
        : p{other.p}
    {
        other.p = nullptr;
    }

    /**
     * @brief #2 Copy assignment constructor
     * 
     * @param other 
     * @return Pvector& 
     */
    Pvector &operator=(const Pvector &other)
    {
        if (&other != this)
        {
            delete p;
            p = nullptr;
            p = new BoidPoint{*(other.p)};
        }

        return *this;
    }
    /**
     * @brief #5 Move assignment operator
     * 
     * @param other 
     * @return Pvector& 
     */
    Pvector &operator=(Pvector &&other)
    {
        if (&other != this)
        {
            delete p;
            p = other.p;
            other.p = nullptr;
        }

        return *this;
    }
    /**
     * @brief #3 Destroy the Pvector object
     * 
     */
    ~Pvector()
    {
        delete p;
    }
    // END Rule of 5 implementation

    float X() const{ return p->x;}
    float Y() const{ return p->y;}

    void X(float x){ p->x=x;}
    void Y(float y){ p->y=y;}

    BoidPoint *P() const { return p; }
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
    Pvector copy(Pvector v);

private:
    BoidPoint *p;
};
}
