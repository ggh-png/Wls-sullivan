#!/usr/bin/env python
import rospy
from ros_MP.msg import state

def callback(data):
rospy.loginfo("%s , %s, %s, %s, %s" % (data.state_1, data.state_2, data.state_3, data.state_4, data.state_5)

def listener():
rospy.init_node('custom_listener', anonymous=True)
rospy.Subscriber("custom_chatter", state, callback)

# spin() simply keeps python from exiting until this node is stopped
rospy.spin()

if name == 'main':
listener()
