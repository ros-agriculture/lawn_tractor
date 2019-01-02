#!/usr/bin/env python
import rospy
# Import geonav tranformation module
import geonav_transform.geonav_conversions as gc
reload(gc)
from nav_msgs.msg import Odometry
from sensor_msgs.msg import NavSatFix


def callback(data):
    #  Set Map Origin
    #  30.174885, -96.512199
    olat = 30.174885
    olon = -96.512199

    # Odom to lat/lon
    xg2, yg2 = gc.xy2ll(data.pose.pose.position.x,
                        data.pose.pose.position.y, olat, olon)

    # build navsat message
    fake_gps = NavSatFix()
    fake_gps.header.frame_id = rospy.get_param('~frame_id', 'gps')
    fake_gps.header.stamp = rospy.Time.now()
    fake_gps.status.status = 1
    fake_gps.status.service = 1
    fake_gps.latitude = xg2
    fake_gps.longitude = yg2
    fake_gps.altitude = 0
    #compass = Float(90.0)

    pub = rospy.Publisher('fake_gps', NavSatFix, queue_size=10)
    pub.publish(fake_gps)

    # Odom to UTM
    utmy, utmx, utmzone = gc.LLtoUTM(xg2, yg2)

    # build navsat message
    fake_UTM = NavSatFix()
    fake_UTM.header.frame_id = rospy.get_param('~frame_id', 'utm')
    fake_UTM.header.stamp = rospy.Time.now()
    fake_UTM.status.status = 1
    fake_UTM.status.service = 1
    fake_UTM.latitude = utmy
    fake_UTM.longitude = utmx
    fake_UTM.altitude = 0
    #compass = Float(90.0)

    pub2 = rospy.Publisher('fake_utm', NavSatFix, queue_size=10)
    pub2.publish(fake_UTM)


def odom2lla():

    # Subscribe to Stage Odom
    rospy.init_node('odom_to_lla', anonymous=True)
    rospy.Subscriber("odom", Odometry, callback)

    rospy.spin()


if __name__ == '__main__':
    try:
        odom2lla()
    except rospy.ROSInterruptException:
        pass
