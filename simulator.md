# Simulator
The objective of the simulator is that you can practice ROS in an appropriate environment and acquire the necessary skills to evolve into the physical product. There are several ways to implement it. Possibly the simplest is to use the docker created container for that purpose, although it may be resource demanding, so you may want to use the other options.


## Docker
Follow this steps for getting your docker container working.
#### Install Docker
If you have docker installed skip to Download Start File.

$ sudo curl -sSL https://get.docker.com | sudo sh

#### **Get Start File**

```
$ wget https://raw.githubusercontent.com/ros-agriculture/lawn_tractor/master/docker/start.sh
```
```
$ sudo chmod +x start.sh
```
```
$ ./start.sh
```
The first time it will download the docker container to your machine, depending on your connection this may take a while. In the following occasions this will not happen. After that initial download, the container will automatically start and you will access the simulator container terminal. To load the simulator itself, you must execute:
```
$ roslaunch lawn_tractor_sim lawn_tractor_sim.launch
```
If you are unfamiliar with Docker, it is suggested you learn the basics from a source such as - https://docker-curriculum.com

To use the docker instance in the future please check out the wiki: https://github.com/ros-agriculture/tractor_sim/wiki

## Cloud Based Simulation
[Here](https://www.loom.com/share/c9868920819a466d827d522a2aa76c8e) you vill find a tutorial on running the lawn tractor simulator.
ROSJect file with simulator already [here](http://www.rosject.io/l/8e95478/).

## Local Install
If you don't have a Ubuntu 16.04 computer running ROS Kinetic. [This script](https://github.com/linorobot/rosme) provided by [LinoRobot](https://linorobot.org/) will install ROS for you.

This simulator runs on Ubuntu 16.04 and ROS Kinetic.

```
prompt$ cd catkin_ws/src
```

```
prompt/catkin_ws/src$ git clone https://github.com/ros-agriculture/ros_lawn_tractor.git
```

```
prompt/catkin_ws/src$ git clone https://github.com/ros-agriculture/geonav_transform.git
```

```
prompt/catkin_ws/src$ cd ..

```

```
prompt/catkin_ws$ rosdep update

```

```
prompt/catkin_ws$ rosdep install -y --from-paths . --ignore-src --rosdistro ${ROS_DISTRO}

```

```
prompt/catkin_ws$ sudo apt-get install python-catkin-tools

```

```
prompt/catkin_ws$ catkin build

```

```
prompt/catkin_ws$ source devel/setup.bash
```

```
#Add new catkin build source to your startup script.
prompt/catkin_ws$ echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc

```
```
prompt/catkin_ws$ roslaunch lawn_tractor_sim lawn_tractor_sim.launch
```

## How to use the simulator?
Simulator uses ROS Navigation and TEB Planner: https://youtu.be/JuZ8gpx9oO4
