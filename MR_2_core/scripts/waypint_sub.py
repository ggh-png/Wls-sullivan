#!/usr/bin/env python
import rospy
from MR_2_core.msg import waypoint

def callback(data):
	rospy.loginfo("%s" % (data.waypoint))

def listener():
	rospy.init_node('waypoint_node', anonymous=True)
	rospy.Subscriber("waypoint", waypoint, callback)

# spin() simply keeps python from exiting until this node is stopped
	rospy.spin()

if name == 'main':
	listener()
