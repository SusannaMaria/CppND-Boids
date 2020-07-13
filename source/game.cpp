/**
 * @file game.cpp
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
#include <iostream>
#include <memory>
#include <fstream>
#include <unistd.h>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "obstaclescontainer.hpp"
#include "flock.hpp"
#include "game.hpp"

#define GetCurrentDir getcwd
using namespace std;

float Pi{3.141529};

/**
 * @brief Construct a new Game object using SFML 
 * 
 */
Game::Game()
{
	srand((int)time(0));

	// Load configuration
	_config = std::make_shared<BoidConfig>();
	_multithreaded = _config->Multithreaded();

	// Create Window based on Desktop resolution
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	this->_window_height = desktop.height;
	this->_window_width = desktop.width;
	this->_window.create(sf::VideoMode(_window_width, _window_height, desktop.bitsPerPixel), "Boids", sf::Style::Default);

	// Print intstruction how to control Boids with curser keys
	printInstructions();

	// Flocking object
	flock = std::make_shared<Flock>();
	flock->init(_window_width, _window_height, _config);

	// Load Font from file
	_uistatsfont.loadFromFile(_config->FontLocation());
}

/**
 * @brief Destroy the Game object
 * 
 */
Game::~Game()
{
}

/**
 * @brief Create entry in UIStat panel
 * 
 * @param xpos 
 * @param text 
 */
void Game::_AddUiStat(int xpos, string text)
{
	int fontsize = _config->FontSize();
	int nr = _uistats.size();
	std::shared_ptr<sf::Text> eleText = std::make_shared<sf::Text>(text, _uistatsfont);

	eleText->setFillColor(sf::Color::White);
	eleText->setCharacterSize(fontsize);
	eleText->setPosition(_window_width - xpos, nr * fontsize);

	_uistatstext.push_back(text);
	_uistats.push_back(eleText);
}

/**
 * @brief Run the simulation. Run creates the boids that we'll display, checks for user input, and updates the view
 * 
 */
void Game::Run()
{
	// Creation of Sprite Container and Obstacles Container
	ASH = std::make_shared<AltSpriteHolder>();
	RED = std::make_shared<AltSpriteHolder>();
	obstacles = std::make_shared<ObstaclesContainer>(flock, _window_width, _window_height, 50);
	M_red = std::make_shared<sf::Sprite>(T_red);
	M = std::make_shared<sf::Sprite>(T);

	if (!T.loadFromFile(_config->PreySprite()))
		exit(1);
	if (!T_red.loadFromFile(_config->PredSprite()))
		exit(1);

	ASH->setTexture(T);
	RED->setTexture(T_red);

	// Create prey boids population
	for (int i = 0; i < _config->AmountPrey(); i++)
	{
		unsigned int spritenr = ASH->addSprite();
		_CreateBoid(_window_width / 2, _window_height / 2, false, spritenr);
	}

	// TODO: This can be improved that the xpos is calculated based on textsize and fontsize
	_AddUiStat(162, "Frames per Second: ");
	_AddUiStat(155, "Total Prey Count: ");
	_AddUiStat(183, "Total Predator Count: ");
	_AddUiStat(155, "Total Boid Count: ");
	_AddUiStat(162, "Separation Amount: ");
	_AddUiStat(155, "Alignment Amount: ");
	_AddUiStat(148, "Cohesion Amount: ");
	_AddUiStat(162, "Separation Weight: ");
	_AddUiStat(155, "Alignment Weight: ");
	_AddUiStat(148, "Cohesion Weight: ");
	_AddUiStat(148, "Flocking(ms): ");

	// Clock added to calculate frame rate, may cause a small amount of slowdown?
	sf::Clock clock;
	_window.setFramerateLimit(120); // Limit the framerate to 120 fps

	unsigned int counter = 0;

	// Now lets run the simulation
	while (_window.isOpen())
	{
		float currentTime = clock.restart().asSeconds();
		float fps = 1 / currentTime; // 1 / refresh time = estimate of fps
		_HandleInput();
		counter++;
		_Render(fps, counter);
	}
}

/**
 * @brief Handle the user input and change the simulation based on it
 * 
 */
void Game::_HandleInput()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		// "close requested" event: we close the window
		// Implemented alternate ways to close the window. (Pressing the escape, X, and BackSpace key also close the program.)
		if ((event.type == sf::Event::Closed) ||
			(event.type == sf::Event::KeyPressed &&
			 event.key.code == sf::Keyboard::Escape) ||
			(event.type == sf::Event::KeyPressed &&
			 event.key.code == sf::Keyboard::BackSpace) ||
			(event.type == sf::Event::KeyPressed &&
			 event.key.code == sf::Keyboard::X))
		{
			_window.close();
		}

		// Event to create new "prey" boids
		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Space)
		{
			unsigned int spritenr = ASH->addSprite();
			_CreateBoid(rand() % _window_width, rand() % _window_height, false, spritenr);
		}

		//Events for modifying the values in Boids, possibly can be refactored?
		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Q)
		{
			flock->addDesSep();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::A)
		{
			flock->subDesSep();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::W)
		{
			flock->addDesAli();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::S)
		{
			flock->subDesAli();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::E)
		{
			flock->addDesCoh();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::D)
		{
			flock->subDesCoh();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::I)
		{
			flock->addSepW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::J)
		{
			flock->subSepW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::O)
		{
			flock->addAliW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::K)
		{
			flock->subAliW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::P)
		{
			flock->addCohW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::L)
		{
			flock->subCohW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::M)
		{
			_multithreaded = !_multithreaded;
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::F5)
		{
			_window.close();
			Game temp = Game();
			;
			temp.Run();
		}
	}

	// Check for mouse click, draws and adds boid to flock if so.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// Gets mouse coordinates, sets that as the location of the boid and the shape
		sf::Vector2i mouseCoords = sf::Mouse::getPosition(_window);
		unsigned int spritenr = RED->addSprite();
		_CreateBoid(mouseCoords.x, mouseCoords.y, true, spritenr);
	}
}

/**
 * @brief Create Boids
 * 
 * @param x 
 * @param y 
 * @param predStatus 
 * @param spritenr 
 */
void Game::_CreateBoid(float x, float y, bool predStatus, int unsigned spritenr)
{
	if (predStatus){
		flock->addBoid(x, y, predStatus, spritenr,RED);
	}else{
		flock->addBoid(x, y, predStatus, spritenr,ASH);
	}
	
}

/**
 * @brief Helper function to update the UI Stats
 * 
 * @param id 
 * @param value 
 */
void Game::_UpdateUiStat(int id, float value)
{
	_uistats[id]->setString(_uistatstext[id] + to_string(int(value)));
	_window.draw(*_uistats[id]);
}

/**
 * @brief Central render function
 * 
 * @param fps 
 * @param counter 
 */
void Game::_Render(float fps, unsigned int counter)
{
	_window.clear();

	// Update the UI Stats
	_UpdateUiStat(0, fps + 0.5);
	_UpdateUiStat(1, flock->preyCount());
	_UpdateUiStat(2, flock->predCount());
	_UpdateUiStat(3, flock->getSize());
	_UpdateUiStat(4, flock->DesSep() + 0.5);
	_UpdateUiStat(5, flock->DesAli() + 0.5);
	_UpdateUiStat(6, flock->DesCoh() + 0.5);
	_UpdateUiStat(7, flock->SepW());
	_UpdateUiStat(8, flock->AliW());
	_UpdateUiStat(9, flock->CohW());
	_UpdateUiStat(10, _durationofflocking / 1000);

	// Draws all of the Sprites out, and applies functions that are needed to update.
	for (int i = 0; i < flock->getSize(); i++)
	{
		auto boid = flock->getBoidPtr(i);
		obstacles->avoid(boid);
		float diff = -boid->updateThetaGetDiff();

		// Update the sprizes
		boid->SpriteContainer()->setPosition(boid->Spritenr(), boid->Location().x, boid->Location().y);
		// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
		boid->SpriteContainer()->rotateAroundSelf(boid->Spritenr(), diff, true);
	}
	
	auto t1 = std::chrono::high_resolution_clock::now();

	// Applies the flocking, three rules to each boid in the flock and changes them accordingly.
	if (_multithreaded)
	{
		flock->sort();
		flock->flockit();
	}
	else
	{
		flock->flocking();
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	_durationofflocking = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	_window.draw(*ASH);
	_window.draw(*RED);
	_window.draw(*obstacles);
	_window.display();
}

void Game::printInstructions()
{
	cout << string(100, '\n');
	cout << "--------------Instructions--------------" << endl;
	cout << "Press 'Q' to increase Separation Amount" << endl;
	cout << "Press 'A' to decrease Separation Amount" << endl;
	cout << "Press 'W' to increase Alignment Amount" << endl;
	cout << "Press 'S' to decrease Alignment Amount" << endl;
	cout << "Press 'E' to increase Cohesion Amount" << endl;
	cout << "Press 'D' to decrease Cohesion Amount" << endl;
	cout << "Press 'I' to increase Separation Weight" << endl;
	cout << "Press 'J' to decrease Separation Weight" << endl;
	cout << "Press 'O' to increase Alignment Weight" << endl;
	cout << "Press 'K' to decrease Alignment Weight" << endl;
	cout << "Press 'P' to increase Alignment Weight" << endl;
	cout << "Press 'L' to decrease Alignment Weight" << endl;
	cout << "Press 'M' to switch between Multi und Singlethreaded" << endl;
	cout << "Press 'Space' to add a prey Boid in a random spot" << endl;
	cout << "Left Click to add a predator Boid where you clicked" << endl;
	cout << "Press 'F5' to restart the simulation" << endl;
	cout << "Press 'Esc', 'Backspace', or 'X' to Quit" << endl;
}