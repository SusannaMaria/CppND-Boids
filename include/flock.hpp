/**
 * @file flock.hpp
 * @author Susanna Hepp (https://github.com/SusannaMaria)
 * @brief class needed to create a flock of boids.
 * @version 0.1
 * @date 2020-07-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "threadpool.hpp"
#include <vector>
#include "boid.hpp"
#include "SFML/Graphics.hpp"
#include <thread>
#include "boidconfig.hpp"
#ifndef FLOCK_H_
#define FLOCK_H_

/**
 * @brief Utilizes boids class and initializes boid flocks with parameters
 * 
 */
class Flock : public std::enable_shared_from_this<Flock>{
public:

	//Constructors
	Flock(){};

	// Accessor functions
	int getSize() const { return _flockvect.size(); }

	void init(int width, int height,std::shared_ptr<BoidConfig> config);

	// Mutator Functions
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

	int AmountObstacles() const{return this->_config->AmountObstacles();}

	float DesSep() const {return this->_desSep;}
	float DesAli() const {return this->_desAli;}
	float DesCoh() const {return this->_desCoh;}
	float SepW() const {return this->_sepW;}
	float AliW() const {return this->_aliW;}
	float CohW() const {return this->_cohW;}					
	float Theta() const {return this->_theta;}	
	int WindowHeight() const {return this->_window_height;}
	int WindowWidth() const {return this->_window_width;}
	
	void addBoid(float x, float y, bool predStatus, int unsigned spritenr);

	shared_ptr<Boid> getBoidPtr(int id);
	void sort();
	void flockit();

private:
	int _window_height;
	int _window_width;	
	int _grid_x;
	int _grid_y;

	float _desSep;
	float _desAli;
	float _desCoh;
	float _sepW;
	float _aliW;
	float _cohW;	
	float _theta;

	std::shared_ptr<BoidConfig> _config;
	vector<shared_ptr<Boid> > _flockvect;
	vector<vector<shared_ptr<Boid> >> sortboids;
	ThreadPool tp;
};

#endif
