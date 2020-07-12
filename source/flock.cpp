#include "boid.hpp"
#include "flock.hpp"
#include "threadpool.hpp"

// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

void Flock::init(int width, int height, std::shared_ptr<BoidConfig> config)
{
	_config = config;
	_window_width = width;
	_window_height = height;

	_desSep = _config->BP("desSep");
	_desAli= _config->BP("desAli");
	_desCoh= _config->BP("desCoh");
	_sepW= _config->BP("sepW");
	_aliW= _config->BP("aliW");
	_cohW= _config->BP("cohW");
	_theta= _config->BP("theta");

	for (int i = 0; i < 12; i++)
	{
		vector<shared_ptr<Boid>> ele;
		sortboids.push_back(ele);
	}
}

int Flock::getSize() const { return _flockvect.size(); }

//Boid Flock::getBoid(int i) { return flock[i]; }

void Flock::addBoid(float x, float y, bool predStatus, int unsigned spritenr)
{
	std::shared_ptr<Boid> bu = std::make_shared<Boid>(x, y, predStatus, spritenr);
	bu->setParent(shared_from_this());
	bu->Theta(Theta());
	_flockvect.push_back(bu);
}

void Flock::sort(int width, int height)
{

	int xs = width / 4;
	int ys = height / 3;

	for (int i = 0; i < 12; i++)
	{
		sortboids[i].clear();
	}

	for (int i = 0; i < _flockvect.size(); i++)
	{

		int segidx = (int)floor(_flockvect[i]->location.x / xs);
		int segidy = (int)floor(_flockvect[i]->location.y / ys);

		if (segidx > 3)
		{
			segidx = 3;
		}
		if (segidy > 2)
		{
			segidy = 2;
		}

		auto duda = _flockvect[i];
		//cout << (segidx + 3 * segidy) << endl;
		sortboids[segidx + 3 * segidy].push_back(duda);
		//cout << "x:" << _flockvect[i]->location.x << "|id:" << segidx << "|y:" << _flockvect[i]->location.y << "|id:" << segidy << "|id:" << (segidx + 3 * segidy) << endl;
	}

	// for (int i=0;i<6;i++){
	// 	cout << sortboids[i].size()<<"|";
	// }
	// cout << endl;
}

void Flock::flockit()
{
	for (int i = 0; i < 12; i++)
	{
		std::function<void()> doThing = std::bind(&Flock::flockingsort, this, i);
		tp.enqueue(doThing);
	}
	tp.waitFinished();
}

void Flock::flockingsortall()
{
	for (int i = 0; i < sortboids.size(); i++)
	{

		for (int j = 0; j < sortboids[i].size(); j++)
		{
			for (int k = 0; k < sortboids[i].size(); k++)
			{
				if (sortboids[i][j]->location.distance(sortboids[i][k]->location) <= abs(20)) // Not sure if distance is 1:1 with SFML window size or if it is even working
				{
					sortboids[i][j]->run(sortboids[i]);
				}
			}
		}
	}
}

void Flock::flockingsort(int i)
{
	for (int j = 0; j < sortboids[i].size(); j++)
	{
		for (int k = 0; k < sortboids[i].size(); k++)
		{
			if (sortboids[i][j]->location.distance(sortboids[i][k]->location) <= abs(20)) // Not sure if distance is 1:1 with SFML window size or if it is even working
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
			if (_flockvect[i]->location.distance(_flockvect[j]->location) <= abs(20)) // Not sure if distance is 1:1 with SFML window size or if it is even working
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
		if (!_flockvect[i]->predatorStatus)
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
