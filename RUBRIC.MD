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

## Object Oriented Programming
| Specification | Defense from Susanna|
| -------------|-------------|
| The project uses Object Oriented Programming techniques.| [ Class Diagram of project](doc/class_relation_full.svg)|
| Classes use appropriate access specifiers for class members.| see [Flock](include/flock.hpp#L27)|
| Class constructors utilize member initialization lists.| see [Obstacle](include/obstacle.hpp#L17)||
| Classes abstract implementation details from their interfaces.| Each class function header was documented with doxygen tags, e.g. [Boid](source/boid.cpp#L19)|
| Classes encapsulate behavior.|[Class Diagram of project](doc/class_relation_full.svg)|
| Classes follow an appropriate inheritance hierarchy.| Container classes were used to encapsulate elements e.g. ObstacleContainer. Classes were defined which are a derivative of sf::drawable e.g. For the representation of the sprites wurden beide Ansätze kombiniert: ([AltSpriteHolder]include/altspriteholder.hpp#L25)|
| Overloaded functions allow the same function to operate on different parameters.|[BoidConfig](include/boidconfig.hpp#L35) provides overloaded printValue function. To demonstrate that it is working, I introduced a [unittest](test/test_overloadfunction.cpp) |
| Derived class functions override virtual base class functions.|The following classes are derived from the sf::Drawable: [AltSpriteHolder](include/altspriteholder.hpp#L25), [Obstacle](include/obstacle.hpp#L14), [ObstaclesContainer](include/obstaclecontainer.hpp#21) they each implement the virtual function ```virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const``` |
| Templates generalize functions in the project.|A function was defined using a template to efficiently compare float or double [almost_equal](include/pvector.hpp#L33)|

## Memory Management
| Specification | Defense from Susanna|
| -------------|-------------|
|The project makes use of references in function declarations.| #1: reference of function is handover in another function to be added in vector: [ThreadPool::enqueue](source/threadpool.cpp#L94)|
|The project uses destructors appropriately.||
|The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.|Using ofstream in BoidConfig Class makes use of RAII: [BoidConfig]source/boidconfig.cpp#L55|
|The project follows the Rule of 5.||
|The project uses move semantics to move data, instead of copying it, where possible.||
|The project uses smart pointers instead of raw pointers.||

## Concurrency
| Specification | Defense from Susanna|
| -------------|-------------|
|The project uses multithreading.||
|A promise and future is used in the project.||
|A mutex or lock is used in the project.||
|A condition variable is used in the project.||
