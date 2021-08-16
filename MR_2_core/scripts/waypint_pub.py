#!/usr/bin/env python
import rospy
from MR_2_core.msg import waypoint

def talker():
    pub = rospy.Publisher('waypoint', waypoint)
    rospy.init_node('waypoint_node', anonymous=True)
    r = rospy.Rate(10) #10hz
    msg = waypoint()
    msg.waypoint = 5

    while not rospy.is_shutdown():
        rospy.loginfo(msg)
        pub.publish(msg)
        r.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass
