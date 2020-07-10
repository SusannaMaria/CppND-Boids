// #include "function_pool.h"
#include "threadpool.h"
#include <vector>
#include "Boid.h"
#include "SFML/Graphics.hpp"
#include <thread>
#ifndef FLOCK_H_
#define FLOCK_H_

// Brief description of Flock Class:
// This file contains the class needed to create a flock of boids. It 
/**
 * @brief utilizes boids class and initializes boid flocks with parameters
 * 
 */
class Flock {
public:

	//Constructors
	Flock(){};
	

	//vector<Boid> flock;
	// Accessor functions
	int getSize() const;
	Boid getBoid(int i);
	void init(int width, int height);
	// Mutator Functions
	void addBoid(Boid b);
	void flocking();
	void flockingsort(int i);
	void flockingsortall();

	//For accessing values and modifying values in Game.cpp
	int preyCount();
	int predCount();

	void addDesSep();
	void subDesSep();
	void addDesAli();
	void subDesAli();
	void addDesCoh();
	void subDesCoh();

	void addSepW();
	void subSepW();
	void addAliW();
	void subAliW();
	void addCohW();
	void subCohW();
	void addBoid(float x, float y, bool predStatus, int unsigned spritenr);

	shared_ptr<Boid> getBoidPtr(int id);
	void sort(int width, int height);
	void flockit();

private:
	vector<shared_ptr<Boid> > _flockvect;
	vector<vector<shared_ptr<Boid> >> sortboids;
	int _window_width;
	int _window_height;
	// Function_pool *func_pool;
	// std::vector<std::thread> thread_pool;
	ThreadPool tp;
};

#endif
