FROM ubuntu:20.04
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y build-essential cmake libsfml-dev 
RUN apt-get install -y mesa-utils libgl1-mesa-glx libnvidia-gl-440
RUN useradd -ms /bin/bash boiduser
USER boiduser
WORKDIR /home/boiduser
