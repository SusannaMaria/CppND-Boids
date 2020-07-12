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

#include <vector>
#include <memory>

#include "pvector.hpp"

using namespace std;

class PVector;

class Flock;

/**
 * Boid Class to implement simple entities called boids
 * 
 */
class Boid
{
public:
	/**
	 * @brief Equal operator using location of boid
	 * 
	 * @param lhs 
	 * @return true 
	 * @return false 
	 */
	bool operator==(const Boid &lhs) { return (location == lhs.Location()); }

	/**
	 * @brief Construct a new Boid object
	 * 
	 * @param x initialize with x-Position
	 * @param y initialize with y-Position
	 * @param predCheck Predator will have higher speeds
	 * @param spritenr Number of sprite refering to SpriteContainer
	 */
	Boid(float x, float y, bool predCheck, int unsigned spritenr);

	void setParent(shared_ptr<Flock> flockptr) { this->myFlock = flockptr; }

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
	Pvector Separation(vector<shared_ptr<Boid>> const &boids);

	/**
	 * @brief Velocity of the current boid to match that of boids that are nearby
	 * 
	 * @param Boids 
	 * @return Pvector 
	 */
	Pvector Alignment(vector<shared_ptr<Boid>> const &boids);

	/**
	 * @brief  Current boid to seek the center of mass of nearby boids.
	 * 
	 * @param Boids 
	 * @return Pvector 
	 */
	Pvector Cohesion(vector<shared_ptr<Boid>> const &boids);

	Pvector seek(Pvector v);

	void run(vector<shared_ptr<Boid>> const &v);

	void update();
	void flock(vector<shared_ptr<Boid>> const &v);
	void borders();
	float getAngle(Pvector v) const;
	bool PredatorStatus() const{ return predatorStatus;}
	float Theta() const;
	void Theta(float theta) { this->theta = theta; }

	float updateThetaGetDiff();
	unsigned int Spritenr() const { return spritenr; };

	Pvector Location() const { return location; }
	Pvector Velocity() const { return velocity; }
	Pvector Acceleration() const { return acceleration; }

	void Velocity(Pvector pv){this->velocity = pv;}
	void Acceleration(Pvector pv){this->acceleration = pv;}

	void Spritenr(unsigned int n) { spritenr = n; }

private:
	bool predatorStatus;  // flag that specifies whether a given boid is a predator.
	Pvector location;	  // Vector that specifies a boid's location.
	Pvector velocity;	  // Vector that specifies a boid's current velocity.
	Pvector acceleration; // Vector that specifies a boid's current acceleration.
	float maxSpeed;		  // Limits magnitude of velocity vector.
	float maxForce;		  // Limits magnitude of acceleration vector. (F = m*a!)
	float theta;		  // Rotational position in 2-dimensional space
	shared_ptr<Flock> myFlock;
	int unsigned spritenr;
};
