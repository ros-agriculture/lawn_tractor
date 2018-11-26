#!/usr/bin/env python

'''
Big thanks to Nick Charron and The Construct Sim for making the tutorial.

Original waypoint_nav logging node https://github.com/nickcharron/waypoint_nav
The Construct Sim - http://theconstructsim.com
The Construct Outdoor Navigation Tutorial Part One: https://www.youtube.com/watch?v=ZomR1tVziLM
The Construct Outdoor Navigation Tutorial Part Two: https://www.youtube.com/watch?v=cmOplaq8cHc
'''

import rospy
import roslaunch
import rospkg
import os
from math import sin, cos, sqrt, atan2, radians
from std_msgs.msg import Bool
from sensor_msgs.msg import NavSatFix

'''
TODO: Move variables to launch file.
        location_collect - location of file
        min_coord_change - minumum distance before logging
        duration_min - minumum time before logging
'''


# Initialize variables
location_collect = ""
collect_request = False
lat_point = 0.0
long_point = 0.0
lat_last = 0.0
long_last = 0.0
time_current = 0.0
time_last = 0.0
duration_min = 2.0
min_coord_change = 1.0


def callback(data):
    global lat_point
    global long_point
    global lat_last
    global long_last
    global time_last

    # Start collecting gps points
    if (collect_request):
        lat_point = data.latitude
        long_point = data.longitude

        # Calculate distance between two GPS points
        # https://stackoverflow.com/questions/19412462/getting-distance-between-two-points-based-on-latitude-longitude
        # approximate radius of earth in meter
        R = 6373000.0

        lat1 = radians(lat_point)
        lon1 = radians(long_point)
        lat2 = radians(lat_last)
        lon2 = radians(long_last)

        dlon = lon2 - lon1
        dlat = lat2 - lat1

        a = sin(dlat / 2)**2 + cos(lat1) * cos(lat2) * sin(dlon / 2)**2
        c = 2 * atan2(sqrt(a), sqrt(1 - a))

        # Distance in meters
        distance = R * c

        # Log gps points to file
        if (gps_file.closed == False):
            time_current = rospy.get_time()
            if ((time_current - time_last > duration_min) and (distance > min_coord_change)) :
                rospy.loginfo("logging waypoints...")
                gps_file.write(str(lat_point) + " " + str(long_point) + "\n")
                lat_last = lat_point
                long_last = long_point
                time_last = time_current
            else:
                #rospy.logwarn("New Latitude: " + str(lati_point) + "  Last Latitude: " + str(lati_last) )
                #rospy.logwarn("New Longitude: %f   Last Longitude: %f \n", longi_point, longi_last )
                #rospy.logwarn("Waypoint not saved, you have not moved enough")
                pass


def collection_status_CB(collection_status_msg):
    global collect_request
    collect_request = collection_status_msg.data


def getPaths():
    # looks up gps file logging location
    global location_collect
    rospack = rospkg.RosPack()
    
    location_collect = rospack.get_path('lawn_tractor_navigation') + "/gps_points_file.txt"


def collect_gps():
    global gps_file

    rospy.init_node('collect_gps_points', anonymous=True)
    rospy.Subscriber("/fake_gps", NavSatFix, callback)
    rospy.Subscriber("/status/gps_waypoint_collection",Bool, collection_status_CB )

    try:
        gps_file = open(location_collect, "a")
        rospy.loginfo(gps_file)
    except IOError:
        print "Could not open gps_points_file.txt file."
    
    rospy.spin()


if __name__ == '__main__':
    try:
        getPaths()
        collect_gps()
    except rospy.ROSInterruptException:
        gps_file.close()
        rospy.loginfo("closed file...")
        pass
