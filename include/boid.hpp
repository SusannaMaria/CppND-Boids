/**
 * @file Boid.h
 * @author 	Jorge Yanar(https://github.com/jyanar), Susanna Hepp (https://github.com/SusannaMaria)
 * @brief  	Boid Class to implement simple entities called boids (birdoids), function through three 
 * Jorge: basic rules - alignment, cohesion, and separation, extended
 * Susanna: refactored to use multi threading, prevent obstacles, using smart pointers and using sfml sprites
 * @version 1.0
 * @date 2020-07-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include "pvector.hpp"
#include <vector>
#include <memory>


using namespace std;

class Flock;

/**
 * Boid Class to implement simple entities called boids
 * 
 */
class Boid
{
public:
	bool predatorStatus;  // flag that specifies whether a given boid is a predator.
	Pvector location;	  // Vector that specifies a boid's location.
	Pvector velocity;	  // Vector that specifies a boid's current velocity.
	Pvector acceleration; // Vector that specifies a boid's current acceleration.
	float maxSpeed;		  // Limits magnitude of velocity vector.
	float maxForce;		  // Limits magnitude of acceleration vector. (F = m*a!)
	float theta;		  // Rotational position in 2-dimensional space

	/**
	 * @brief Equal operator using location of boid
	 * 
	 * @param lhs 
	 * @return true 
	 * @return false 
	 */
	bool operator==(const Boid& lhs){ return (location == lhs.Location());}

	/**
	 * @brief Construct a new Boid object
	 * 
	 * @param x initialize with x-Position
	 * @param y initialize with y-Position
	 */
	Boid(float x, float y, int window_width, int window_height);

	/**
	 * @brief Construct a new Boid object
	 * 
	 * @param x initialize with x-Position
	 * @param y initialize with y-Position
	 * @param predCheck Predator will have higher speeds
	 */
	Boid(float x, float y,int window_width, int window_height,  bool predCheck, int unsigned spritenr,float desSep, float desAli, float desCoh, float sepW, float aliW, float cohW, float theta);
	Boid(float x, float y, bool predCheck, int unsigned spritenr);

	void setParent(shared_ptr<Flock> flockptr){this->myFlock = flockptr;}

	/**
	 * @brief Adds force Pvector to current force Pvector
	 * 
	 * @param force  
	 */
	void applyForce(Pvector force);

	// Three Laws that boids follow
	/**
	 * @brief  Separation computes a a vector that distances the current boid from the boids
	 * 
	 * @param Boids 
	 * @return Pvector 
	 */
	Pvector Separation(vector<shared_ptr<Boid> > const &boids);

	/**
	 * @brief Velocity of the current boid to match that of boids that are nearby
	 * 
	 * @param Boids 
	 * @return Pvector 
	 */
	Pvector Alignment(vector<shared_ptr<Boid> > const &boids);


	/**
	 * @brief  Current boid to seek the center of mass of nearby boids.
	 * 
	 * @param Boids 
	 * @return Pvector 
	 */
	Pvector Cohesion(vector<shared_ptr<Boid> > const &boids);

	///Functions involving SFML and visualisation linking
	Pvector seek(Pvector v);
	void run(vector<Boid> v);
	void run(vector<shared_ptr<Boid> > const &v);

	void update();
	void flock(vector<shared_ptr<Boid> > const &v);
	void borders();
	float getAngle(Pvector v) const;

	Pvector Location() const;
	float Theta() const;
	unsigned int Spritenr() const;
	void Theta(float theta){this->theta = theta;}

	float updateThetaGetDiff();
	void Spritenr(unsigned int n);

private:
	shared_ptr<Flock> myFlock;

	int unsigned spritenr;
};
