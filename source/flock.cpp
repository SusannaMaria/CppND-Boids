/**
 * @file flock.cpp
 * @author Jorge Yanar(https://github.com/jyanar), Susanna Hepp (https://github.com/SusannaMaria)
 * @brief Flocking Functions
 * Jorge: Base implementation
 * Susanna: Introduce Smart Ptr, relocate central attributes of boids into flock, Sorting of boids by location in grid and implementatation of multithreading
 * @version 1.0
 * @date 2020-07-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "boid.hpp"
#include "threadpool.hpp"
#include "flock.hpp"

/**
 * @brief 
 * 
 * @param width 
 * @param height 
 * @param config 
 */
void Flock::init(int width, int height, std::shared_ptr<BoidConfig> config)
{
	_config = config;
	_window_width = width;
	_window_height = height;

	_desSep = _config->BP("desSep");
	_desAli = _config->BP("desAli");
	_desCoh = _config->BP("desCoh");
	_sepW = _config->BP("sepW");
	_aliW = _config->BP("aliW");
	_cohW = _config->BP("cohW");
	_theta = _config->BP("theta");

	_grid_x = _config->GridX();
	_grid_y = _config->GridY();

	for (int i = 0; i < _grid_x*_grid_y; i++)
	{
		vector<shared_ptr<Boid>> ele;
		sortboids.push_back(ele);
	}
}

/**
 * @brief Create new Boid and add to internal vector
 * 
 * @param x 
 * @param y 
 * @param predStatus 
 * @param spritenr 
 */
void Flock::addBoid(float x, float y, bool predStatus, int unsigned spritenr)
{
	std::shared_ptr<Boid> bu = std::make_shared<Boid>(x, y, predStatus, spritenr);
	bu->setParent(shared_from_this());
	bu->Theta(Theta());
	_flockvect.push_back(bu);
}

/**
 * @brief Sort boids in grid, this is single threaded
 * 
 * @param width 
 * @param height 
 */
void Flock::sort()
{

	int xs = _window_width / _grid_x;
	int ys = _window_height / _grid_y;

	for (int i = 0; i < _grid_x * _grid_y; i++)
	{
		sortboids[i].clear();
	}

	for (int i = 0; i < _flockvect.size(); i++)
	{

		int segidx = (int)floor(_flockvect[i]->Location().x / xs);
		int segidy = (int)floor(_flockvect[i]->Location().y / ys);

		if (segidx > _grid_x - 1)
		{
			segidx = _grid_x - 1;
		}
		if (segidy > _grid_y - 1)
		{
			segidy = _grid_y - 1;
		}

		auto duda = _flockvect[i];
		sortboids[segidx + (_grid_x - 1) * segidy].push_back(duda);
	}
}
/**
 * @brief Multithreading of flocking
 * 
 */
void Flock::flockit()
{
	for (int i = 0; i < _grid_x * _grid_y; i++)
	{
		std::function<void()> doThing = std::bind(&Flock::flockingsort, this, i);
		tp.enqueue(doThing);
	}
	tp.waitFinished();
}

// void Flock::flockingsortall()
// {
// 	for (int i = 0; i < sortboids.size(); i++)
// 	{

// 		for (int j = 0; j < sortboids[i].size(); j++)
// 		{
// 			for (int k = 0; k < sortboids[i].size(); k++)
// 			{
// 				if (sortboids[i][j]->Location().distance(sortboids[i][k]->Location()) <= abs(20)) // Not sure if distance is 1:1 with SFML window size or if it is even working
// 				{
// 					sortboids[i][j]->run(sortboids[i]);
// 				}
// 			}
// 		}
// 	}
// }

void Flock::flockingsort(int i)
{
	for (int j = 0; j < sortboids[i].size(); j++)
	{
		for (int k = 0; k < sortboids[i].size(); k++)
		{
			if (sortboids[i][j]->Location().distance(sortboids[i][k]->Location()) <= abs(20)) // Not sure if distance is 1:1 with SFML window size or if it is even working
			{
				sortboids[i][j]->run(sortboids[i]);
			}
		}
	}
}

// Runs the run function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::flocking()
{
	for (int i = 0; i < _flockvect.size(); i++)
	{
		//Only checks in a certain range instead of checking through the whole flock in an attempt to reduce time complexity
		for (int j = 0; j < _flockvect.size(); j++)
		{
			if (_flockvect[i]->Location().distance(_flockvect[j]->Location()) <= abs(20)) // Not sure if distance is 1:1 with SFML window size or if it is even working
			{
				_flockvect[i]->run(_flockvect);
			}
		}
	}
}

int Flock::preyCount()
{
	int count = 0;
	for (int i = 0; i < _flockvect.size(); i++)
	{
		if (!_flockvect[i]->PredatorStatus())
			count++;
	}
	return count;
}

int Flock::predCount()
{
	return _flockvect.size() - preyCount();
}

void Flock::addDesSep()
{
	_desSep += 1;
}

void Flock::subDesSep()
{
	_desSep -= 1;
}

void Flock::addDesAli()
{
	_desAli += 1;
}

void Flock::subDesAli()
{
	_desAli -= 1;
}

void Flock::addDesCoh()
{
	_desCoh += 1;
}

void Flock::subDesCoh()
{
	_desCoh -= 1;
}

void Flock::addSepW()
{
	_sepW += .1;
}

void Flock::subSepW()
{
	_sepW -= .1;
}

void Flock::addAliW()
{
	_aliW += .1;
}

void Flock::subAliW()
{
	_aliW -= .1;
}

void Flock::addCohW()
{
	_cohW += .1;
}

void Flock::subCohW()
{
	_cohW -= .1;
}

shared_ptr<Boid> Flock::getBoidPtr(int id)
{
	if (id >= _flockvect.size())
	{
		return nullptr;
	}
	return _flockvect[id];
}
