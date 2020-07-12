/**
 * @file boid.cpp.cpp
 * @author Jorge Yanar(https://github.com/jyanar), Susanna Hepp (https://github.com/SusannaMaria)
 * @brief Boid Functions
 * @version 1.0
 * @date 2020-07-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "SFML/Window.hpp"

#include "flock.hpp"
#include "boid.hpp"

/**
 * @brief Construct a new Boid:: Boid object
 * 
 * @param x 
 * @param y 
 * @param predCheck 
 * @param spritenr
 */

Boid::Boid(float x, float y, bool predCheck, int unsigned spritenr){

	predatorStatus = predCheck;
	if (predCheck == true) {
		maxSpeed = 7.5;
		maxForce = 1.5;
		velocity = Pvector(rand() % 5 - 1, rand() % 5 - 1);
	}
	else {
		maxSpeed = 5.5;
		maxForce = 0.5;
		velocity = Pvector(rand() % 5 - 2, rand() % 5 - 2);
	}
	acceleration = Pvector(0, 0);
	location = Pvector(x, y);
	this->spritenr =spritenr;

}

/**
 * @brief Adds force Pvector to current force Pvector
 * 
 * @param force 
 */
void Boid::applyForce(Pvector force)
{
	acceleration.addVector(force);
}

/**
 * @brief Keeps boids from getting too close to one another
 * 
 * @param boids 
 * @return Pvector 
 */
Pvector Boid::Separation(vector<shared_ptr<Boid> > const &boids)
{
	// Distance of field of vision for separation between boids
	float desiredseparation = myFlock->DesSep();
	Pvector steer(0, 0);
	int count = 0;
	// For every boid in the system, check if it's too close
	for (int i = 0; i < boids.size(); i++) {
		// Calculate distance from current boid to boid we're looking at
		float d = location.distance(boids[i]->location);
		// If this is a fellow boid and it's too close, move away from it
		if ((d > 0) && (d < desiredseparation)) {
			Pvector diff(0, 0);
			diff = diff.subTwoVector(location, boids[i]->location);
			diff.normalize();
			diff.divScalar(d);      // Weight by distance
			steer.addVector(diff);
			count++;
		}
		// If current boid is a predator and the boid we're looking at is also
		// a predator, then separate only slightly
		if ((d > 0) && (d < desiredseparation) && predatorStatus == true
			&& boids[i]->predatorStatus == true) {
			Pvector pred2pred(0, 0);
			pred2pred = pred2pred.subTwoVector(location, boids[i]->location);
			pred2pred.normalize();
			pred2pred.divScalar(d);
			steer.addVector(pred2pred);
			count++;
		}
		// If current boid is not a predator, but the boid we're looking at is
		// a predator, then create a large separation Pvector
		else if ((d > 0) && (d < desiredseparation + 70) && boids[i]->predatorStatus == true) {
			Pvector pred(0, 0);
			pred = pred.subTwoVector(location, boids[i]->location);
			pred.mulScalar(900);
			steer.addVector(pred);
			count++;
		}
	}
	// Adds average difference of location to acceleration
	if (count > 0)
		steer.divScalar(static_cast<float>(count));
	if (steer.magnitude() > 0) {
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}
	return steer;
}


/**
 * @brief Calculates the average velocity of boids in the field of vision and
 * manipulates the velocity of the current boid in order to match it
 * 
 * @param Boids 
 * @return Pvector 
 */

Pvector Boid::Alignment(vector<shared_ptr<Boid> > const &boids)
{
	float neighbordist = myFlock->DesAli(); // Field of vision

	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < boids.size(); i++) {
		float d = location.distance(boids[i]->location);

		if ((d > 0) && (d < neighbordist)) { // 0 < d < 50
			sum.addVector(boids[i]->velocity);
			count++;
		}
	}
	// If there are boids close enough for alignment...
	if (count > 0) {
		sum.divScalar(static_cast<float>(count));// Divide sum by the number of close boids (average of velocity)
		sum.normalize();            // Turn sum into a unit vector, and
		sum.mulScalar(maxSpeed);    // Multiply by maxSpeed
		// Steer = Desired - Velocity
		Pvector steer;
		steer = steer.subTwoVector(sum, velocity); //sum = desired(average)
		steer.limit(maxForce);
		return steer;
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}
/**
 * @brief Finds the average location of nearby boids and manipulates the
 * steering force to move in that direction.
 * 
 * @param Boids 
 * @return Pvector 
 */
Pvector Boid::Cohesion(vector<shared_ptr<Boid> > const &boids)
{
	float neighbordist = myFlock->DesCoh();
	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < boids.size(); i++) {
		float d = location.distance(boids[i]->location);

		if (boids[i]->predatorStatus) neighbordist = 15;

		if ((d > 0) && (d < neighbordist)) {
			sum.addVector(boids[i]->location);
			count++;
		}
	}
	if (count > 0) {
		sum.divScalar(count);
		return seek(sum);
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}

/**
 * @brief Limits the maxSpeed, finds necessary steering force and normalizes vectors
 * 
 * @param v 
 * @return Pvector 
 */
Pvector Boid::seek(Pvector v)
{
	Pvector desired;
	desired.subVector(v);  // A vector pointing from the location to the target
	// Normalize desired and scale to maximum speed
	desired.normalize();
	desired.mulScalar(maxSpeed);
	// Steering = Desired minus Velocity
	acceleration.subTwoVector(desired, velocity);
	acceleration.limit(maxForce);  // Limit to maximum steering force
	return acceleration;
}

/**
 * @brief Modifies velocity, location, and resets acceleration with values that are given by the three laws.
 * 
 */
void Boid::update()
{
	//To make the slow down not as abrupt
	acceleration.mulScalar(.35);
	// Update velocity
	velocity.addVector(acceleration);
	// Limit speed
	velocity.limit(maxSpeed);
	location.addVector(velocity);
	// Reset accelertion to 0 each cycle
	acceleration.mulScalar(0);
}

/**
 * @brief Applies the three rules, modifies velocities accordingly, updates data,
 * and corrects boids which are sitting outside of the SFML window
 * 
 * @param v 
 */
void Boid::run(vector<shared_ptr<Boid> > const &v){
	flock(v);
	update();
	borders();
}

/**
 * @brief Perform flocking of subset of boids sorted before
 * 
 * @param v 
 */
void Boid::flock(vector<shared_ptr<Boid> > const &v)
{
	Pvector sep = Separation(v);
	Pvector ali = Alignment(v);
	Pvector coh = Cohesion(v);
	// Arbitrarily weight these forces
	sep.mulScalar(myFlock->SepW());
	ali.mulScalar(myFlock->AliW()); // Might need to alter weights for different characteristics
	coh.mulScalar(myFlock->CohW());
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}


/**
 * @brief Checks if boids go out of the window and if so, wraps them around to the other side.
 * 
 */
void Boid::borders()
{
	int wh = myFlock->WindowHeight();
	int ww = myFlock->WindowWidth();

	if (location.x < 0)    location.x += ww;
	if (location.y < 0)    location.y += wh;
	if (location.x > ww) location.x -= ww;
	if (location.y > wh) location.y -= wh;
}

/**
 * @brief Calculates the angle for the velocity of a boid which allows the visual image to rotate in the direction that it is going in.
 * 
 * @param v 
 * @return float 
 */
float Boid::getAngle(Pvector v) const
{
	// From the definition of the dot product
	float angle = static_cast<float>(atan2(v.x, -v.y) * 180 / M_PI);
	return angle;
}

/**
 * @brief Get difference of theta which will be applied to rotate the sprite
 * 
 * @return float 
 */
float Boid::updateThetaGetDiff(){
	float t = getAngle(this->velocity);
	float diff = theta-t;
	theta = t;
	return diff;
}

