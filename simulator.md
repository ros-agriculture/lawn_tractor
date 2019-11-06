
### Cloud Based Simulation
[Here](https://www.loom.com/share/c9868920819a466d827d522a2aa76c8e) you vill find a tutorial on running the lawn tractor simulator.
ROSJect file with simulator already [here](http://www.rosject.io/l/8e95478/).

### Local Install
If you don't have a Ubuntu 16.04 computer running ROS Kinetic. [This script](https://github.com/linorobot/rosme) provided by [LinoRobot](https://linorobot.org/) will install ROS for you.

This simulator runs on Ubuntu 16.04 and ROS Kinetic.

```
prompt$ cd catkin_ws/src
```

```
prompt/catkin_ws/src$ git clone https://github.com/ros-agriculture/ros_lawn_tractor.git
```

```
prompt/catkin_ws/src$ git clone https://github.com/bsb808/geonav_transform.git
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


### Docker Install
If you have docker installed skip to Download Start File.
**Install Docker**
Docker install instructions - https://docs.docker.com/install/

**Download Start File**
```
prompt$ wget https://raw.githubusercontent.com/ros-agriculture/ros_lawn_tractor/master/docker/start.sh
```
```
prompt$ chmod +x start.sh
```
```
prompt$ ./start.sh
```
..... wait for image to download ......
```
docker/prompt$ roslaunch lawn_tractor_sim lawn_tractor_sim.launch
```

### How to use the simulator?
Simulator uses ROS Navigation and TEB Planner: https://youtu.be/JuZ8gpx9oO4
