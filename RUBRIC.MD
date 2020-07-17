## A README with instructions is included with the project 
| Specification | Defense from Susanna|
| -------------|-------------|
| The README is included with the project and has instructions for building/running the project. | Instructions for installation in an Ubuntu based system are available. It describes how to build and use the application via a docker image. Explanation which general dependencies are present in the Readme.
| The README describes the project you have built.| A general explanation of the function of the application is given.|

## The submission must compile and run.
| Specification | Defense from Susanna|
| -------------|-------------|
| The submission must compile and run.|As recommended, the project uses cmake and make as build systems. The application was developed and tested exclusively on Ubuntu based Linux systems, but it is explained how a docker image can be used to achieve independence from other distributions.

## Loops, Functions, I/O
| Specification | Defense from Susanna|
| -------------|-------------|
|The project demonstrates an understanding of C++ functions and control structures.| Only classes and their methods are used as Mutator, Accessor, Constructor functions. If/else conditions, while- and for-loops are used. e.g. [Game::Run](source/game.cpp#L91), [Boid::Alignment](source/boid.cpp#L125)|
|The project reads data from a file and process the data, or the program writes data to a file.| A configuration file in TOML format was used for the application. The reading, processing and writing is implemented in the class [BoidConfig::BoidConfig](source/boidconfig.cpp#L24) |
|The project accepts user input and processes the input.|In the Game class user input is processed which influences the simulation. see [Game::_HandleInput](source/game.cpp#L149)|
