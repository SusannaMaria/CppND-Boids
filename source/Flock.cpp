#include "Boid.h"
#include "Flock.h"

// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

int Flock::getSize() const { return _flockvect.size(); }

//Boid Flock::getBoid(int i) { return flock[i]; }

void Flock::addBoid(float x, float y, bool predStatus,int unsigned spritenr){
	std::shared_ptr<Boid> bu = std::make_shared<Boid>(x, y, predStatus, spritenr);
	_flockvect.push_back(bu); 

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

// void Flock::pflocking()
// {
// 	for (int i = 0; i < _flockvect.size(); i++)
// 	{
// 		//Only checks in a certain range instead of checking through the whole flock in an attempt to reduce time complexity
// 		for (int j = 0; j < _flockvect.size(); j++) 
// 		{
// 			if (_flockvect[i]->location.distance(_flockvect[j]->location) <= abs(20))
// 			{
// 				_flockvect[i]->run(flock);
// 			}
// 		}
// 	}
// }

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

shared_ptr<Boid> Flock::getBoidPtr(int id){
	if(id>=_flockvect.size()){
		return nullptr;
	}
	return _flockvect[id];
}
