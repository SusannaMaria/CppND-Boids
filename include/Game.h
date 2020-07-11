#include "Flock.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "AltSpriteHolder.hpp"
#include "PolarVector.hpp"
#include "obstacle.hpp"
#include "ObstaclesContainer.hpp"
#include "config.hpp"
#ifndef GAME_H
#define GAME_H

// Game handles the instantiation of a flock of boids, game input, asks the
// model to compute the next step in the stimulation, and handles all of the
// program's interaction with SFML.



class Game
{
private:

	bool _multithreaded = false;
	int64_t _durationofflocking = 0; 
	sf::RenderWindow _window;
	int _window_width;
	int _window_height;
	std::shared_ptr<BoidConfig> _config;
	shared_ptr<AltSpriteHolder> ASH;
	shared_ptr<AltSpriteHolder> RED;

	shared_ptr<ObstaclesContainer> obstacles;

	sf::Event event;
	sf::Texture T;
	sf::Texture T_red;

	shared_ptr<sf::Sprite> M;
	vector<shared_ptr<sf::Text> > _uistats;
	shared_ptr<sf::Sprite> M_red;

	vector<string> _uistatstext;
	sf::Font f_uistatsfont;
	void updateUiStat(int id,float value);
	std::vector<PolarVector> PolVec;
	Flock flock;
	float boidsSize;

	// Not a very efficient solution to pass the sf::Text objects through to the render function but it's
	// a quick way to do it. Needs fix.
	void Render(float fps, unsigned int counter);

	// Refactored duplicate code in it's own function to simplify the creation of boids
	void createBoid(float x, float y, bool predStatus, int unsigned spritenr);
	void HandleInput();
	
	void addUiStat(int xpos, string text);

public:
	// For console instructions
	static void printInstructions();
	Game();
	void Run();
	~Game();
};

#endif
