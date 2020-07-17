# Docker
You can build and run cppnd-boids in the docker container. First you need to create the docker image and then the docker image can be instantiated as a container and cppnd-boid can be built and executed in it.

# Requirements
Install the Docker environment on your operating system. Directly supported are CentOS, Debian, Fedora, Ubuntu. Follow the instructions on  https://docs.docker.com/engine/install/ubuntu/

# Building the docker image
It should be enough to execute the ```./builddocker.sh``` script. It is important that you have network access and I recommend that your normal user has access to the docker environment. e.g.:
```
sudo usermod -aG docker <your-user>
```
I use an Ubuntu:20.04 Docker image as a basis. And install dependencies to NVIDIA drivers as well, otherwise the execution of cppnd-boids will not work in a system with Nvidia graphics card.

# Execution of the docker
It should be sufficient to execute the ```./rundocker``` script. The script allows you to start the docker gui applications and must be executed with privileged rights. 
