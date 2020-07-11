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
	std::shared_ptr<Boid> bu = std::make_shared<Boid>(x, y, predStatus, spritenr, _config->BP("desSep"), _config->BP("desAli"), _config->BP("desCoh"), _config->BP("sepW"), _config->BP("aliW"), _config->BP("cohW"), _config->BP("theta"));
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
	for (int i = 0; i < _flockvect.size(); i++)
	{
		_flockvect[i]->DesSep(1);
	}
}

void Flock::subDesSep()
{
	for (int i = 0; i < _flockvect.size(); i++)
	{
		_flockvect[i]->DesSep(-1);
	}
}

void Flock::addDesAli()
{
	for (int i = 0; i < _flockvect.size(); i++)
	{
		_flockvect[i]->DesAli(1);
	}
}

void Flock::subDesAli()
{
	for (int i = 0; i < _flockvect.size(); i++)
	{
		_flockvect[i]->DesAli(-1);
	}
}

void Flock::addDesCoh()
{
	for (int i = 0; i < _flockvect.size(); i++)
	{
		_flockvect[i]->DesCoh(1);
	}
}

void Flock::subDesCoh()
{
	for (int i = 0; i < _flockvect.size(); i++)
	{
		_flockvect[i]->DesCoh(-1);
	}
}

void Flock::addSepW()
{
	for (int i = 0; i < _flockvect.size(); i++)
	{
		_flockvect[i]->SepW(.1);
	}
}

void Flock::subSepW()
{
	for (int i = 0; i < _flockvect.size(); i++)
	{
		_flockvect[i]->SepW(-.1);
	}
}

void Flock::addAliW()
{
	for (int i = 0; i < _flockvect.size(); i++)
	{
		_flockvect[i]->AliW(.1);
	}
}

void Flock::subAliW()
{
	for (int i = 0; i < _flockvect.size(); i++)
	{
		_flockvect[i]->AliW(-.1);
	}
}

void Flock::addCohW()
{
	for (int i = 0; i < _flockvect.size(); i++)
	{
		_flockvect[i]->CohW(.1);
	}
}

void Flock::subCohW()
{
	for (int i = 0; i < _flockvect.size(); i++)
	{
		_flockvect[i]->CohW(-.1);
	}
}

shared_ptr<Boid> Flock::getBoidPtr(int id)
{
	if (id >= _flockvect.size())
	{
		return nullptr;
	}
	return _flockvect[id];
}
