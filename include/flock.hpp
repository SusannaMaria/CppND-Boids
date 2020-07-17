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
#include "altspriteholder.hpp"
#include "boidconfig.hpp"
#ifndef FLOCK_H_
#define FLOCK_H_

/**
 * @brief Utilizes boids class and initializes boid flocks with parameters
 * 
 */
class Flock : public std::enable_shared_from_this<Flock>
{
public:
	//Constructors
	Flock(): _window_height(),_window_width(), _grid_x(), _grid_y(), _desSep(0.f), _desAli(0.f), _desCoh(0.f), _sepW(0.f), _aliW(0.f), _cohW(0.f), _theta(){}

	// Accessor functions
	int getSize() const { return _flockvect.size(); }

	void init(int width, int height, std::shared_ptr<BoidConfig> config);

	// Mutator Functions
	void flocking();
	void flockingsort(int i);

	//For accessing values and modifying values in Game.cpp

	void addDesSep() { _desSep += 1; }

	void subDesSep() { _desSep -= 1; }

	void addDesAli() { _desAli += 1; }

	void subDesAli() { _desAli -= 1; }

	void addDesCoh() { _desCoh += 1; }

	void subDesCoh() { _desCoh -= 1; }

	void addSepW() { _sepW += .1; }

	void subSepW() { _sepW -= .1; }

	void addAliW() { _aliW += .1; }

	void subAliW() { _aliW -= .1; }

	void addCohW() { _cohW += .1; }

	void subCohW() { _cohW -= .1; }

	int preyCount();
	int predCount();
	int AmountObstacles() const { return this->_config->AmountObstacles(); }

	float DesSep() const { return this->_desSep; }
	float DesAli() const { return this->_desAli; }
	float DesCoh() const { return this->_desCoh; }
	float SepW() const { return this->_sepW; }
	float AliW() const { return this->_aliW; }
	float CohW() const { return this->_cohW; }
	float Theta() const { return this->_theta; }
	int WindowHeight() const { return this->_window_height; }
	int WindowWidth() const { return this->_window_width; }

	void addBoid(float x, float y, bool predstatus, int unsigned spritenr, std::shared_ptr<AltSpriteHolder> spritecontainer);

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
	vector<shared_ptr<Boid>> _flockvect;
	vector<vector<shared_ptr<Boid>>> sortboids;
	ThreadPool tp;
};

#endif
