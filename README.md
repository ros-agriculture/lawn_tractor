# ros_lawn_tractor
Software for self driving lawn tractor.

![Foto Matt](https://lh3.googleusercontent.com/fTaDVuOLLdnxALxxXZmdqxHzTtC0EKzNXzy3jcWOWNoNlAX-m1M9URiD9IABtjC8Se8V4jBieDTCXtoDVbzQBO0D88ygz5vbCTbUdQbwyRxgyai9iPZPSZQLVdbvPU0uiYLkNv0FSi2fQMzmgIwPZWIWe7Vzuwb3TllN16e9ZSV7SDvLe-l3H1xDfc5wzULhObR3kFBgxlkZVWMzIT_DkWyBIHNnBDrEaFNuyiaAT5c1iJ5WjzdCYbOXhXEYVZTiz1jRwTlDoaIwbIT0xw4zAzEv1z19rshk7V4rs5nPqCsWYhy8znP8vQNAeLdwcnZbkF6GSjjN7kk3La_IxX-FckfNwMPM_dNeW2K3OaQ1RCQo6m0DpSBzG3cVcMoCmRIThZei3CoxFbJOF-mp5cToEpJrO0gd9pFaTSrJRL-oJsHd5E0gfvEt9nVmkVkjwBoXcwvg80NQi-DTuFjvi2-DVAeS_N_oP-boCSa1NB1X0s1QkRqcUDn2UUsOUXw8OCu_sKr2dm_pG1y-6yZF_jbWl3-DF0DvwGwUwfCFcYTXFxXG_YCZ-HIP0SlwzhVnGPtDRcwrIYujg7ocHkrBR10Gmwpqk1yyDY4X1HKKAG-TWE5yXCENIO4CARVqA8vrIHD10cY-YKlrbZXxiMwCuf1hMVsGUjeVD-xcxogLQzlM0c6QkQH3ggvTB283_OxDF4-VNglSSafwSmN8Qt1ustLoKOHvwg=w860-h645-no)

## How to use the simulator?
Simulator uses ROS Navigation and TEB Planner: https://youtu.be/JuZ8gpx9oO4

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


## Docker Install
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
## Join us.
This is an open project and you are invited to work in it with the team. Present yourself on one of the following platforms: [the SLACK group](http://rosagriculture.slack.com/), [the facebook page](https://facebook.com/ROSAgriculture), [twitt us](https://twitter.com/ROSAgriculture) or [a Whatsapp](https://wa.me/+12142933679) to the coordinator.

## Licensing.
ros_lawn_tractor is released under the MIT license.

Any user of this software shall indemnify and hold harmless ROS Agriculture O&Uuml;. and its directors, officers, employees, agents, stockholders, affiliates, subcontractors and customers from and against all allegations, claims, actions, suits, demands, damages, liabilities, obligations, losses, settlements, judgments, costs and expenses (including without limitation attorneys’ fees and costs) which arise out of, relate to or result from any use of this software by user.

THIS IS ALPHA QUALITY SOFTWARE FOR RESEARCH PURPOSES ONLY. THIS IS NOT A PRODUCT. YOU ARE RESPONSIBLE FOR COMPLYING WITH LOCAL LAWS AND REGULATIONS. NO WARRANTY EXPRESSED OR IMPLIED.
