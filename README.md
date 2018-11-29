# ros_lawn_tractor
Software for self driving lawn tractor.

![alt text](https://github.com/ros-agriculture/ros_lawn_tractor/blob/master/lawn_tractor.png)

https://www.youtube.com/watch?v=-RF8hOKg6WU

# Install
<pre>

prompt$ cd catkin_ws/src
prompt/catkin_ws/src$ git clone https://github.com/ros-agriculture/ros_lawn_tractor.git 
prompt/catkin_ws/src$ git clone https://github.com/bsb808/geonav_transform.git
prompt/catkin_ws/src$ cd ..
prompt/catkin_ws$ rosdep update
prompt/catkin_ws$ rosdep install -y --from-paths . --ignore-src --rosdistro ${ROS_DISTRO}
prompt/catkin_ws$ catkin build
prompt/catkin_ws$ source devel/setup.bash
prompt/catkin_ws$ roslaunch lawn_tractor_sim lawn_tractor_sim.launch
</pre>

# Docker
If you have docker installed skip to Download Start File.<br />
Install Docker <br />
Docker install instructions - https://docs.docker.com/install/ <br />
If you use Ubuntu Trusty, Wily, or Xenial, install the linux-image-extra kernel package:

<pre>
prompt$ sudo apt-get update -y && sudo apt-get install -y linux-image-extra-$(uname -r)
</pre>

Install Docker:
<pre>
prompt$ sudo apt-get update
prompt$ sudo apt-get install apt-transport-https ca-certificates curl software-properties-common
prompt$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
prompt$ sudo add-apt-repository \
   "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
   $(lsb_release -cs) \
   stable"
prompt$ sudo apt-get install docker-ce -y
</pre>
Start Docker:
<pre>
prompt$ sudo service docker start
</pre>
Verify Docker:
<pre>
prompt$ sudo docker run hello-world
</pre>

Download Start File
<pre>
prompt$ wget https://github.com/ros-agriculture/ros_lawn_tractor/blob/master/docker/start.sh
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
