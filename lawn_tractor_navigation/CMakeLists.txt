cmake_minimum_required(VERSION 3.0.3)
project(lawn_tractor_navigation)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  tf
  roslib
  roslaunch
  base_local_planner
)

catkin_package()
roslaunch_add_file_check(launch)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

install(DIRECTORY  launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
