# CppND-Boids
This is my final project for the Udacity nano Degree C++ course, which I completed between May and September 2020. It is a reconstruction and extension of an existing project https://github.com/jyanar/Boids, regarding memory management multithreading and object orientation. The choice of the task was based on the following criteria: Graphical development, swarm simulation, investigation of performance improvement through multithreading and intensive use of smart pointers. 

Listing of the things I have introduced based on the project:
* Support of swarm simulation by multithreading, sorting of the single boids and parallel execution of the simulation.
* Introduction of an obstacle class and further development of swarm behaviour to avoid objects.
* Replacing the vector-based representation of the swarm with sprites
* Support for configuration files based on the TOML format
* Optimization of the class structure, e.g.: relocation of class attributes to parent classes
* Unit tests for important functions of the application
...

# Requirements
g++ >= 8.0
sudo apt-get install libsfml-dev

# Install
```
git clone https://github.com/SusannaMaria/CppND-Capstone.git
cd CppND-Capstone/
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
```

# Docker
https://www.nvidia.com/de-de/drivers/unix/
http://de.download.nvidia.com/XFree86/Linux-x86_64/450.57/NVIDIA-Linux-x86_64-450.57.run


# Run
./cppnd-boids

# Control-Keys during run
```
--------------Instructions--------------
Press 'Q' to increase Separation Amount
Press 'A' to decrease Separation Amount
Press 'W' to increase Alignment Amount
Press 'S' to decrease Alignment Amount
Press 'E' to increase Cohesion Amount
Press 'D' to decrease Cohesion Amount
Press 'I' to increase Separation Weight
Press 'J' to decrease Separation Weight
Press 'O' to increase Alignment Weight
Press 'K' to decrease Alignment Weight
Press 'P' to increase Alignment Weight
Press 'L' to decrease Alignment Weight
Press 'M' to switch between Multi und Singlethreaded
Press 'Space' to add a prey Boid in a random spot
Left Click to add a predator Boid where you clicked
Press 'F5' to restart the simulation
Press 'Esc', 'Backspace', or 'X' to Quit
```

# Configuration
Check build folder for ```boids.toml```after first time run.

## Default Config which can be adapted:
```
[boids]
version = 1.0
uistatfont = "assets/consola.ttf"
preysprite = "assets/fly16x16.png"
predsprite = "assets/fly16x16_red.png"
multithreaded = true
amountprey = 1000
desSep = 20.0
desAli = 70.0
desCoh = 25.0
sepW = 1.5
aliW = 1.0
cohW = 1.0
theta = 0.0
amountobstacles = 5
gridx = 4
gridy = 3
fontsize = 12
rootpath = "/home/aosuser/CppND-Capstone/build/.."
```
