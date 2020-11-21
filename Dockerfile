FROM osrf/ros:kinetic-desktop
MAINTAINER Matt Droter matt@rosagriculture.org

# metadata
LABEL version="0.1"
LABEL description="ROS Agriculture tractor_sim."

ENV CATKIN_WS=/root/tractor_ws
RUN mkdir -p $CATKIN_WS/src
WORKDIR $CATKIN_WS/src

# update apt-get because osrf image clears this cache and download deps
RUN apt-get -qq update && \
    apt-get -qq install -y \
	apt-utils \
	libeigen3-dev \
    python-catkin-tools  \
    less \
    ssh \
	vim \
	terminator \
    git-core \
    bash-completion \
    wget \
    qtbase5-dev \ 
    libqt5svg5-dev \ 
    libzmq3-dev \ 
    libdw-dev

# HACK, replacing shell with bash for later docker build commands
RUN mv /bin/sh /bin/sh-old && \
    ln -s /bin/bash /bin/sh

# get source
COPY . .

RUN echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
RUN echo "source $CATKIN_WS/devel/setup.bash" >> ~/.bashrc

RUN rosdep update && \
    rosdep install -y --from-paths . --ignore-src --rosdistro ${ROS_DISTRO} --as-root=apt:false && \
    apt-get -qq upgrade && \
    rm -rf /var/lib/apt/lists/*

# build repo
WORKDIR $CATKIN_WS
ENV TERM xterm
ENV PYTHONIOENCODING UTF-8 
RUN git clone https://github.com/BehaviorTree/Groot.git && \
   cd Groot && \
   git submodule update --init --recursive && \
   mkdir build; cd build && \
   cmake .. && \
   make && \
   cd ..
RUN source /ros_entrypoint.sh && \
    catkin build --no-status && \
    source $CATKIN_WS/devel/setup.bash


    
