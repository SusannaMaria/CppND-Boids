/**
 * @file Boid.cpp
 * @author 	Jorge Yanar(https://github.com/jyanar), Susanna Hepp (https://github.com/SusannaMaria)
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
#include "Boid.h"
#include "SFML/Window.hpp"

// Global Variables for borders()
// desktopTemp gets screen resolution of PC running the program
sf::VideoMode desktopTemp = sf::VideoMode::getDesktopMode();
const int window_height = desktopTemp.height;
const int window_width = desktopTemp.width;

// =============================================== //
// ======== Boid Functions from Boid.h =========== //
// =============================================== //

Boid::Boid(float x, float y): predatorStatus(false)
{
	acceleration = Pvector(0, 0);
	velocity = Pvector(rand() % 3 - 2, rand() % 3 - 2);
	location = Pvector(x, y);
	maxSpeed = 3.5;
	maxForce = 0.5;

	desSep = 20;
	desAli = 70;
	desCoh = 25;
	sepW = 1.5;
	aliW = 1.0;
	cohW = 1.0;
}

/**
 * @brief Construct a new Boid:: Boid object
 * 
 * @param x 
 * @param y 
 * @param predCheck 
 */
Boid::Boid(float x, float y, bool predCheck, int unsigned spritenr, float desSep, float desAli, float desCoh, float sepW, float aliW, float cohW, float theta)
{
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

	this->desSep = desSep;
	this->desAli = desAli;
	this->desCoh = desCoh;
	this->sepW = sepW;
	this->aliW = aliW;
	this->cohW = cohW;
	this->theta = theta;
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
	float desiredseparation = desSep;
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
		if ((d > 0) && (d < desSep) && predatorStatus == true
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

Pvector Boid::Separation(vector<Boid> boids)
{
	// Distance of field of vision for separation between boids
	float desiredseparation = desSep;
	Pvector steer(0, 0);
	int count = 0;
	// For every boid in the system, check if it's too close
	for (int i = 0; i < boids.size(); i++) {
		// Calculate distance from current boid to boid we're looking at
		float d = location.distance(boids[i].location);
		// If this is a fellow boid and it's too close, move away from it
		if ((d > 0) && (d < desiredseparation)) {
			Pvector diff(0, 0);
			diff = diff.subTwoVector(location, boids[i].location);
			diff.normalize();
			diff.divScalar(d);      // Weight by distance
			steer.addVector(diff);
			count++;
		}
		// If current boid is a predator and the boid we're looking at is also
		// a predator, then separate only slightly
		if ((d > 0) && (d < desSep) && predatorStatus == true
			&& boids[i].predatorStatus == true) {
			Pvector pred2pred(0, 0);
			pred2pred = pred2pred.subTwoVector(location, boids[i].location);
			pred2pred.normalize();
			pred2pred.divScalar(d);
			steer.addVector(pred2pred);
			count++;
		}
		// If current boid is not a predator, but the boid we're looking at is
		// a predator, then create a large separation Pvector
		else if ((d > 0) && (d < desiredseparation + 70) && boids[i].predatorStatus == true) {
			Pvector pred(0, 0);
			pred = pred.subTwoVector(location, boids[i].location);
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
	float neighbordist = desAli; // Field of vision

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

Pvector Boid::Alignment(vector<Boid> Boids)
{
	float neighbordist = desAli; // Field of vision

	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < Boids.size(); i++) {
		float d = location.distance(Boids[i].location);

		if ((d > 0) && (d < neighbordist)) { // 0 < d < 50
			sum.addVector(Boids[i].velocity);
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
	float neighbordist = desCoh;
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

Pvector Boid::Cohesion(vector<Boid> Boids)
{
	float neighbordist = desCoh;
	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < Boids.size(); i++) {
		float d = location.distance(Boids[i].location);

		if (Boids[i].predatorStatus) neighbordist = 15;

		if ((d > 0) && (d < neighbordist)) {
			sum.addVector(Boids[i].location);
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


void Boid::flock(vector<shared_ptr<Boid> > const &v)
{
	Pvector sep = Separation(v);
	Pvector ali = Alignment(v);
	Pvector coh = Cohesion(v);
	// Arbitrarily weight these forces
	sep.mulScalar(sepW);
	ali.mulScalar(aliW); // Might need to alter weights for different characteristics
	coh.mulScalar(cohW);
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}


/**
 * @brief Applies the three laws to the flock of boids
 * 
 * @param v 
 */
void Boid::flock(vector<Boid> v)
{
	Pvector sep = Separation(v);
	Pvector ali = Alignment(v);
	Pvector coh = Cohesion(v);
	// Arbitrarily weight these forces
	sep.mulScalar(sepW);
	ali.mulScalar(aliW); // Might need to alter weights for different characteristics
	coh.mulScalar(cohW);
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
	if (location.x < 0)    location.x += window_width;
	if (location.y < 0)    location.y += window_height;
	if (location.x > window_width) location.x -= window_width;
	if (location.y > window_height) location.y -= window_height;
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

unsigned int Boid::Spritenr() const {return spritenr;};

float Boid::DesSep() const { return desSep; }

float Boid::DesAli() const { return desAli; }

float Boid::DesCoh() const { return desCoh; }

float Boid::SepW() const { return sepW; }

float Boid::AliW() const { return aliW; }

float Boid::CohW() const { return cohW; }

float Boid::Theta() const { return this->theta; }

Pvector Boid::Location()const { return location; }

void Boid::DesSep(float x) { desSep += x; }

void Boid::DesAli(float x) { desAli += x; }

void Boid::DesCoh(float x) { desCoh += x; }

void Boid::SepW(float x) { sepW += x; }

void Boid::AliW(float x) { aliW += x; }

void Boid::CohW(float x) { cohW += x; }

void Boid::Theta(float t) { theta = t; }

void Boid::Spritenr(unsigned int n) { spritenr = n; }
