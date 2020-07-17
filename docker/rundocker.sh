#!/bin/bash
xhost +local:root
pushd ..
docker run -it --rm --privileged --user=$(id -u $USER):$(id -g $USER) -v `pwd`:`pwd` -w `pwd` \
    --env="DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    boids:1.0 /bin/bash
popd
xhost -local:root