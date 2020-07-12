/**
 * @file game.hpp
 * @author Jorge Yanar(https://github.com/jyanar), Susanna Hepp (https://github.com/SusannaMaria)
 * @brief Central Class of boid application to control graphics (using sfml) and user interface
 * Jorge: Base implementation
 * Susanna: Clean up code, optimize drawing, Introduce Smart Ptr, introduce central configuration
 * @version 1.0
 * @date 2020-07-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "flock.hpp"
#include "altspriteholder.hpp"
#include "polarvector.hpp"
#include "obstacle.hpp"
#include "obstaclescontainer.hpp"
#include "boidconfig.hpp"

/**
 * @brief Game handles the instantiation of a flock of boids, game input, asks the
 * model to compute the next step in the stimulation, and handles all of the
 * program's interaction with SFML.
 * 
 */
class Game
{
public:
	// For console instructions
	static void printInstructions();
	Game();
	void Run();
	~Game();

private:
	shared_ptr<BoidConfig> _config;
	shared_ptr<AltSpriteHolder> ASH;
	shared_ptr<AltSpriteHolder> RED;
	shared_ptr<ObstaclesContainer> obstacles;
	shared_ptr<sf::Sprite> M;
	vector<shared_ptr<sf::Text>> _uistats;
	shared_ptr<sf::Sprite> M_red;
	shared_ptr<Flock> flock;

	sf::Event event;
	sf::Texture T;
	sf::Texture T_red;
	sf::RenderWindow _window;
	sf::Font _uistatsfont;

	vector<string> _uistatstext;
	bool _multithreaded = false;
	int64_t _durationofflocking = 0;
	int _window_width;
	int _window_height;

	void _UpdateUiStat(int id, float value);
	void _Render(float fps, unsigned int counter);
	void _CreateBoid(float x, float y, bool predStatus, int unsigned spritenr);
	void _HandleInput();
	void _AddUiStat(int xpos, string text);

};
