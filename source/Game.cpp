#include "Flock.h"
#include "Game.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "obstacle.hpp"
#include <iostream>

#define BOID_AMOUNT 400
#include <unistd.h>
#define GetCurrentDir getcwd
using namespace std;

float Pi{3.141529};

std::string get_current_dir()
{
	char buff[FILENAME_MAX]; //create string buffer to hold path
	GetCurrentDir(buff, FILENAME_MAX);
	string current_working_dir(buff);
	return current_working_dir;
}

// Construct window using SFML
Game::Game()
{
	//this->boidsSize = rand() % 10 - 3;
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	this->_window_height = desktop.height;
	this->_window_width = desktop.width;
	this->_window.create(sf::VideoMode(_window_width, _window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);

	printInstructions();
}

Game::~Game()
{
	delete ASH;
	delete RED;
	delete M;
	delete M_red;
	delete obstacle;
	delete obstacle2;
}

// Run the simulation. Run creates the boids that we'll display, checks for user
// input, and updates the view
void Game::Run()
{

	for (int i = 0; i < BOID_AMOUNT; i++)
	{
		createBoid(_window_width / 2, _window_height / 2, false);
	}

	ASH = new AltSpriteHolder(BOID_AMOUNT);
	RED = new AltSpriteHolder(BOID_AMOUNT);

	if (!T.loadFromFile(get_current_dir() + "/../assets/fly16x16.png")) ///Change the path as needed.
		exit(1);
	if (!T_red.loadFromFile(get_current_dir() + "/../assets/fly16x16_red.png")) ///Change the path as needed.
		exit(1);

	M = new sf::Sprite(T);
	ASH->setTexture(T);

	M_red = new sf::Sprite(T_red);
	RED->setTexture(T_red);

	obstacle = new Obstacle(800, 500, 10);
	obstacle2 = new Obstacle(200, 200, 10);

	obstacle->_window_height = _window_height;
	obstacle->_window_width = _window_width;

	//Whole block of text can probably simplified in a function as well in order to remove redundancy
	sf::Font font;
	cout << get_current_dir() << endl;
	font.loadFromFile(get_current_dir() + "/../assets/consola.ttf");

	sf::Text fpsText("Frames per Second: ", font);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setCharacterSize(12);
	fpsText.setPosition(_window_width - 162, 0);

	sf::Text preyText("Total Prey Count: " + to_string(flock.preyCount()), font);
	preyText.setFillColor(sf::Color::White);
	preyText.setCharacterSize(12);
	preyText.setPosition(_window_width - 155, 12);

	sf::Text predText("Total Predator Count: " + to_string(flock.predCount()), font);
	predText.setFillColor(sf::Color::White);
	predText.setCharacterSize(12);
	predText.setPosition(_window_width - 183, 24);

	sf::Text boidText("Total Boid Count: " + to_string(flock.getSize()), font);
	boidText.setFillColor(sf::Color::White);
	boidText.setCharacterSize(12);
	boidText.setPosition(_window_width - 155, 36);

	sf::Text dSepText("Separation Amount: " + to_string(flock.getBoid(0).DesSep()), font);
	dSepText.setFillColor(sf::Color::White);
	dSepText.setCharacterSize(12);
	dSepText.setPosition(_window_width - 162, 60);

	sf::Text dAliText("Alignment Amount: " + to_string(flock.getBoid(0).DesAli()), font);
	dAliText.setFillColor(sf::Color::White);
	dAliText.setCharacterSize(12);
	dAliText.setPosition(_window_width - 155, 72);

	sf::Text dCohText("Cohesion Amount: " + to_string(flock.getBoid(0).DesCoh()), font);
	dCohText.setFillColor(sf::Color::White);
	dCohText.setCharacterSize(12);
	dCohText.setPosition(_window_width - 148, 84);

	sf::Text dSepWText("Separation Weight: " + to_string(flock.getBoid(0).SepW()), font);
	dSepWText.setFillColor(sf::Color::White);
	dSepWText.setCharacterSize(12);
	dSepWText.setPosition(_window_width - 162, 108);

	sf::Text dAliWText("Alignment Weight: " + to_string(flock.getBoid(0).AliW()), font);
	dAliWText.setFillColor(sf::Color::White);
	dAliWText.setCharacterSize(12);
	dAliWText.setPosition(_window_width - 155, 120);

	sf::Text dCohWText("Cohesion Weight: " + to_string(flock.getBoid(0).CohW()), font);
	dCohWText.setFillColor(sf::Color::White);
	dCohWText.setCharacterSize(12);
	dCohWText.setPosition(_window_width - 148, 132);

	// Clock added to calculate frame rate, may cause a small amount of slowdown?
	sf::Clock clock;
	_window.setFramerateLimit(120); //

	while (_window.isOpen())
	{
		float currentTime = clock.restart().asSeconds();
		float fps = 1 / currentTime; // 1 / refresh time = estimate of fps
		HandleInput();
		Render(fpsText, fps, preyText, predText, boidText,
			   dSepText, dAliText, dCohText, dSepWText, dAliWText, dCohWText);
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
			createBoid(rand() % _window_width, rand() % _window_height, false);
		}

		//Events for modifying the values in Boids, possibly can be refactored?
		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Q)
		{
			flock.addDesSep();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::A)
		{
			flock.subDesSep();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::W)
		{
			flock.addDesAli();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::S)
		{
			flock.subDesAli();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::E)
		{
			flock.addDesCoh();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::D)
		{
			flock.subDesCoh();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::I)
		{
			flock.addSepW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::J)
		{
			flock.subSepW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::O)
		{
			flock.addAliW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::K)
		{
			flock.subAliW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::P)
		{
			flock.addCohW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::L)
		{
			flock.subCohW();
		}

		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::F5)
		{
			_window.close();
			Game temp;
			;
			temp.Run();
		}
	}

	// Check for mouse click, draws and adds boid to flock if so.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// Gets mouse coordinates, sets that as the location of the boid and the shape
		sf::Vector2i mouseCoords = sf::Mouse::getPosition(_window);
		createBoid(mouseCoords.x, mouseCoords.y, true);
	}
}

void Game::createBoid(float x, float y, bool predStatus)
{
	Boid b(x, y, predStatus);

	flock.addBoid(b);
}

//Method of passing text needs refactoring
void Game::Render(sf::Text fpsText, float fps, sf::Text preyText, sf::Text predText, sf::Text boidText,
				  sf::Text dSepText, sf::Text dAliText, sf::Text dCohText, sf::Text dSepWText, sf::Text dAliWText, sf::Text dCohWText)
{
	_window.clear();

	//Updating and drawing text can possibly be put in it's own function as well
	fpsText.setString("Frames per Second: " + to_string(int(fps + 0.5)));
	_window.draw(fpsText);

	preyText.setString("Total Prey Count: " + to_string(flock.preyCount()));
	_window.draw(preyText);

	predText.setString("Total Predator Count: " + to_string(flock.predCount()));
	_window.draw(predText);

	boidText.setString("Total Boid Count: " + to_string(flock.getSize()));
	_window.draw(boidText);

	dSepText.setString("Separation Amount: " + to_string(int(flock.getBoid(0).DesSep() + 0.5)));
	_window.draw(dSepText);

	dAliText.setString("Alignment Amount: " + to_string(int(flock.getBoid(0).DesAli() + 0.5)));
	_window.draw(dAliText);

	dCohText.setString("Cohesion Amount: " + to_string(int(flock.getBoid(0).DesCoh() + 0.5)));
	_window.draw(dCohText);

	dSepWText.setString("Separation Weight: " + to_string(flock.getBoid(0).SepW()));
	_window.draw(dSepWText);

	dAliWText.setString("Alignment Weight: " + to_string(flock.getBoid(0).AliW()));
	_window.draw(dAliWText);

	dCohWText.setString("Cohesion Weight: " + to_string(flock.getBoid(0).CohW()));
	_window.draw(dCohWText);

	// Draws all of the Boids out, and applies functions that are needed to update.

	for (int i = 0; i < flock.getSize(); i++)
	{

		// Applies the three rules to each boid in the flock and changes them accordingly.

		obstacle->avoid(flock.flock[i]);
		obstacle2->avoid(flock.flock[i]);

		if (i < BOID_AMOUNT)
		{
			ASH->setPosition(i, flock.getBoid(i).location.x, flock.getBoid(i).location.y);

			// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
			float diff = -flock.flock[i].updateThetaGetDiff();

			ASH->rotateAroundSelf(i, diff, true);
		}
		else
		{
			RED->setPosition(i - BOID_AMOUNT, flock.getBoid(i).location.x, flock.getBoid(i).location.y);

			// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
			float diff = -flock.flock[i].updateThetaGetDiff();

			RED->rotateAroundSelf(i - BOID_AMOUNT, diff, true);
		}
	}

	flock.flocking();

	_window.draw(*ASH);
	_window.draw(*RED);
	_window.draw(*obstacle);
	_window.draw(*obstacle2);
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
	cout << "Press 'Space' to add a prey Boid in a random spot" << endl;
	cout << "Left Click to add a predator Boid where you clicked" << endl;
	cout << "Press 'F5' to restart the simulation" << endl;
	cout << "Press 'Esc', 'Backspace', or 'X' to Quit" << endl;
}