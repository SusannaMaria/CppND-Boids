#include "Flock.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "AltSpriteHolder.hpp"
#include "PolarVector.hpp"
#include "obstacle.hpp"

#ifndef GAME_H
#define GAME_H

// Game handles the instantiation of a flock of boids, game input, asks the
// model to compute the next step in the stimulation, and handles all of the
// program's interaction with SFML. 

class Game {
private:
	sf::RenderWindow _window;
	int _window_width;
	int _window_height;

	shared_ptr<AltSpriteHolder> ASH;
	shared_ptr<AltSpriteHolder> RED;

	vector<shared_ptr<Obstacle> > obstacles;

    sf::Event event;
    sf::Texture T;
    sf::Texture T_red;	

    shared_ptr<sf::Sprite> M;

	shared_ptr<sf::Sprite> M_red;


    std::vector<PolarVector> PolVec;
	Flock flock;
	float boidsSize;

	// Not a very efficient solution to pass the sf::Text objects through to the render function but it's
	// a quick way to do it. Needs fix.
	void Render(sf::Text text, float fps, sf::Text text2, sf::Text text3, sf::Text text4, 
				sf::Text text5, sf::Text text6, sf::Text text7, sf::Text text8, sf::Text text9, sf::Text text10);

	// Refactored duplicate code in it's own function to simplify the creation of boids
	void createBoid(float x, float y, bool predStatus,int unsigned spritenr);
	void HandleInput();

public:
	// For console instructions
	static void printInstructions();
	Game();
	void Run();
	~Game();
};

#endif
