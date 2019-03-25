define ultra_front ranger
(
  sensor
  (
    range_max 10.0
    range_min 0.25
    fov 60.0
    samples 4
  )
  # generic model properties
  color "black"
  size [ 0.06 0.15 0.03 ]
)


define tractor position
(
  odom_error [0.03 0.03 999999 999999 999999 0.02]

  size [ 2.0 0.5 1.0 ] # (x,y,z) - bounding box of the robot
  origin [ 0.2 0.0 0.0 0.0] # correct center of rotation (x,y,z,beta)
  gui_nose 1
  drive "car" # kinematic model of a car-like robot
  wheelbase 0.4 # distance between rear and front axles
  localization "gps"

  pose [ 0.0 0.0 0.0 0.0 ]
  color "gray"

  # sonar( pose [ 0 0 -0.03 0 ] )
  ultra_front (pose [ -0.1 0.0 -0.11 0.0 ])
)