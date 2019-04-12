# ros_lawn_tractor
Software for self driving lawn tractor.

![alt text](https://github.com/ros-agriculture/ros_lawn_tractor/blob/master/lawn_tractor.png)

https://www.youtube.com/watch?v=-RF8hOKg6WU

## How to use the simulator?
Simulator uses ROS Navigation and TEB Planner: https://youtu.be/JuZ8gpx9oO4

## What if I don't see a tractor in RVIZ?
When rviz starts it doesn't load the rviz config file.  You will need to go to File and load sim config file.
Sometimes when you press the File tab it just shows black.  You will need to stop rviz and relaunch the sim:
https://youtu.be/yF0pPZHdhtI   There is an open issue if you know the fix...

## Cloud Based Simulation
Tutorial on running the lawn tractor simulator: https://www.loom.com/share/c9868920819a466d827d522a2aa76c8e  
ROSJect file with simulator already loaded:  http://www.rosject.io/l/8e95478/

## Local Install
If you don't have a Ubuntu 16.04 computer running ROS Kinetic.  This script https://github.com/linorobot/rosme provided by LinoRobot (https://linorobot.org/) will install ROS for you.

This simulator runs on Ubuntu 16.04 and ROS Kinetic.

<pre>

prompt$ cd catkin_ws/src
prompt/catkin_ws/src$ git clone https://github.com/ros-agriculture/ros_lawn_tractor.git 
prompt/catkin_ws/src$ git clone https://github.com/bsb808/geonav_transform.git
prompt/catkin_ws/src$ cd ..
prompt/catkin_ws$ rosdep update
prompt/catkin_ws$ rosdep install -y --from-paths . --ignore-src --rosdistro ${ROS_DISTRO}
prompt/catkin_ws$ sudo apt-get install python-catkin-tools
prompt/catkin_ws$ catkin build
prompt/catkin_ws$ source devel/setup.bash
#Add new catkin build source to your startup script.
prompt/catkin_ws$ echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
prompt/catkin_ws$ roslaunch lawn_tractor_sim lawn_tractor_sim.launch
</pre>

## Docker
If you have docker installed skip to Download Start File.<br />
Install Docker <br />
Docker install instructions - https://docs.docker.com/install/ <br />

Download Start File
<pre>
prompt$ wget https://raw.githubusercontent.com/ros-agriculture/ros_lawn_tractor/master/docker/start.sh
prompt$ chmod +x start.sh
prompt$ ./start.sh
</pre>
..... wait for image to download ......
<pre>
docker/prompt$ roslaunch lawn_tractor_sim lawn_tractor_sim.launch
</pre>

When rviz starts it doesn't load the rviz config file.  You will need to go to File and load sim config file.
Sometimes when you press the File tab it just shows black.  You will need to stop rviz and relaunch the sim:
https://youtu.be/yF0pPZHdhtI




## Licensing
ros_lawn_tractor is released under the MIT license. 

Any user of this software shall indemnify and hold harmless ROS Agriculture O&Uuml;. and its directors, officers, employees, agents, stockholders, affiliates, subcontractors and customers from and against all allegations, claims, actions, suits, demands, damages, liabilities, obligations, losses, settlements, judgments, costs and expenses (including without limitation attorneys’ fees and costs) which arise out of, relate to or result from any use of this software by user.

THIS IS ALPHA QUALITY SOFTWARE FOR RESEARCH PURPOSES ONLY. THIS IS NOT A PRODUCT. YOU ARE RESPONSIBLE FOR COMPLYING WITH LOCAL LAWS AND REGULATIONS. NO WARRANTY EXPRESSED OR IMPLIED.
