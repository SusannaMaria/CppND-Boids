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

// Construct window using SFML
	Game::Game()
{
	_config = std::make_shared<BoidConfig>();

	_multithreaded = _config->Multithreaded();
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

	this->_window_height = desktop.height;
	this->_window_width = desktop.width;
	this->_window.create(sf::VideoMode(_window_width, _window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);

	printInstructions();
	srand((int)time(0));

	// Flocking object
	flock = std::make_shared<Flock>();
	flock->init(_window_width, _window_height,_config);

	f_uistatsfont.loadFromFile(_config->FontLocation());
}

Game::~Game()
{
}

void Game::addUiStat(int xpos, string text)
{

	int nr = _uistats.size();
	std::shared_ptr<sf::Text> eleText = std::make_shared<sf::Text>(text, f_uistatsfont);

	eleText->setFillColor(sf::Color::White);
	eleText->setCharacterSize(12);
	eleText->setPosition(_window_width - xpos, nr * 12);

	_uistatstext.push_back(text);
	_uistats.push_back(eleText);
}

/**
 * @brief Run the simulation. Run creates the boids that we'll display, checks for user input, and updates the view
 * 
 */
void Game::Run()
{

	ASH = std::make_shared<AltSpriteHolder>();
	RED = std::make_shared<AltSpriteHolder>();

	if (!T.loadFromFile(_config->PreySprite()))
		exit(1);
	if (!T_red.loadFromFile(_config->PredSprite()))
		exit(1);

	M = std::make_shared<sf::Sprite>(T);
	ASH->setTexture(T);

	M_red = std::make_shared<sf::Sprite>(T_red);
	RED->setTexture(T_red);

	for (int i = 0; i < _config->AmountPrey(); i++)
	{
		unsigned int spritenr = ASH->addSprite();
		createBoid(_window_width / 2, _window_height / 2, false, spritenr);
	}

	obstacles = std::make_shared<ObstaclesContainer>(_window_width, _window_height, 50);

	addUiStat(162, "Frames per Second: ");
	addUiStat(155, "Total Prey Count: ");
	addUiStat(183, "Total Predator Count: ");
	addUiStat(155, "Total Boid Count: ");
	addUiStat(162, "Separation Amount: ");
	addUiStat(155, "Alignment Amount: ");
	addUiStat(148, "Cohesion Amount: ");
	addUiStat(162, "Separation Weight: ");
	addUiStat(155, "Alignment Weight: ");
	addUiStat(148, "Cohesion Weight: ");
	addUiStat(148, "Flocking(ms): ");

	// Clock added to calculate frame rate, may cause a small amount of slowdown?
	sf::Clock clock;
	_window.setFramerateLimit(120); // Limit the framerate to 120 fps

	unsigned int counter = 0;
	while (_window.isOpen())
	{
		float currentTime = clock.restart().asSeconds();
		float fps = 1 / currentTime; // 1 / refresh time = estimate of fps
		HandleInput();
		counter++;
		Render(fps, counter);
	}
}

void Game::HandleInput()
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
			createBoid(rand() % _window_width, rand() % _window_height, false, spritenr);
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
		createBoid(mouseCoords.x, mouseCoords.y, true, spritenr);
	}
}

void Game::createBoid(float x, float y, bool predStatus, int unsigned spritenr)
{
	flock->addBoid(x, y, predStatus, spritenr);

	// Boid b(x, y, predStatus);
	// flock->addBoid(b);
}

void Game::updateUiStat(int id, float value)
{
	_uistats[id]->setString(_uistatstext[id] + to_string(int(value)));
	_window.draw(*_uistats[id]);
}

//Method of passing text needs refactoring
void Game::Render(float fps, unsigned int counter)
{
	_window.clear();

	updateUiStat(0, fps + 0.5);
	updateUiStat(1, flock->preyCount());
	updateUiStat(2, flock->predCount());
	updateUiStat(3, flock->getSize());
	updateUiStat(4, flock->DesSep() + 0.5);
	updateUiStat(5, flock->DesAli() + 0.5);
	updateUiStat(6, flock->DesCoh() + 0.5);
	updateUiStat(7, flock->SepW());
	updateUiStat(8, flock->AliW());
	updateUiStat(9, flock->CohW());
	updateUiStat(10, _durationofflocking / 1000);

	// Draws all of the Boids out, and applies functions that are needed to update.
	for (int i = 0; i < flock->getSize(); i++)
	{

		// Applies the three rules to each boid in the flock and changes them accordingly.

		obstacles->avoid(flock->getBoidPtr(i));

		if (flock->getBoidPtr(i)->PredatorStatus())
		{
			RED->setPosition(flock->getBoidPtr(i)->Spritenr(), flock->getBoidPtr(i)->Location().x, flock->getBoidPtr(i)->Location().y);

			// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
			float diff = -flock->getBoidPtr(i)->updateThetaGetDiff();

			RED->rotateAroundSelf(flock->getBoidPtr(i)->Spritenr(), diff, true);
		}
		else
		{
			ASH->setPosition(flock->getBoidPtr(i)->Spritenr(), flock->getBoidPtr(i)->Location().x, flock->getBoidPtr(i)->Location().y);

			// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
			float diff = -flock->getBoidPtr(i)->updateThetaGetDiff();

			ASH->rotateAroundSelf(flock->getBoidPtr(i)->Spritenr(), diff, true);
		}
	}
	auto t1 = std::chrono::high_resolution_clock::now();

	if (_multithreaded)
	{
		flock->sort(_window_width, _window_height);
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