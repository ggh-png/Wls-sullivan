#!/usr/bin/env python
import rospy
from ros_MP.msg import state

# ma
def talker():
    pub = rospy.Publisher('custom_chatter', state)
    rospy.init_node('custom_talker', anonymous=True)
    r = rospy.Rate(10) #10hz
    msg = state()
    msg.state_1 = "A"
    msg.state_2 = "B"
    msg.state_3 = "C"
    msg.state_4 = "D"
    msg.state_5 = "E"
	
    while not rospy.is_shutdown():
        rospy.loginfo(msg)
        pub.publish(msg)
        r.sleep()

    if __name__ == '__main__':
 	try:
        	talker()
    	except rospy.ROSInterruptException: pass


