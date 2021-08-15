#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Image
from std_msgs.msg import String
import cv2
from cv_bridge import CvBridge,  CvBridgeError
import  os
class ImagePublisher:
    def __init__(self):
        self.res_pub = rospy.Publisher("/image_out_node/result",  Image, queue_size = 1)
        rospy.init_node('image_publisher')
        self.rock_pic_path = "./images/rock.jpg"
        self.paper_pic_path = "./images/paper.jpg"
        self.scissors_pic_path = "./images/scissors.jpg"
        self.all_pic_path = "./images/all.jpg"
        
        self.rock_pic = cv2.resize(cv2.imread(self.rock_pic_path), (640,640))
        self.paper_pic = self.rock_pic = cv2.resize(cv2.imread(self.paper_pic_path), (640,640))
        self.scissors_pic = self.rock_pic = cv2.resize(cv2.imread(self.scissors_pic_path), (640,640))
        self.all_pic = self.rock_pic = cv2.resize(cv2.imread(self.all_pic_path), (640,640))
        cv2.putText(self.all_pic, "Playing...", (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
 
        self.curr_pic = self.all_pic
        self.state = ""
        self.bridge = CvBridge()
        self.sub  = rospy.Subscriber("/RPS_node/result", String, self.set_state)
        
     
    def set_state(self, st):
        if(st.data.split()[0] == "Rock"):
            self.curr_pic = self.rock_pic
            self.add_label(st.data.split()[1], st.data.split()[2])
        if(st.data.split()[0] == "Paper"):
            self.curr_pic = self.paper_pic
            self.add_label(st.data.split()[1], st.data.split()[2])
        if(st.data.split()[0] == "Scissors"):
            self.curr_pic = self.scissors_pic
            self.add_label(st.data.split()[1], st.data.split()[2])
        #if(st.data.split()[0] == "playing"):
         #   self.curr_pic = self.all_pic
            
        msg = self.bridge.cv2_to_imgmsg(self.curr_pic, encoding = "bgr8")
        self.res_pub.publish(msg)
            
            
    def add_label(self, res, winner):
        cv2.putText(self.curr_pic, "Your move is "+res, (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
        if(winner == "2"):
            cv2.putText(self.curr_pic, "No winner", (10,self.curr_pic.shape[1]-50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
        elif(winner == "0"):
            cv2.putText(self.curr_pic, "You won!", (10, self.curr_pic.shape[1]-50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
        elif(winner == "1"):
            cv2.putText(self.curr_pic, "I won!", (10, self.curr_pic.shape[1]-50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
        
        
def main():
    print(os.getcwd())
    im_out = ImagePublisher()
    try:
      rospy.spin()
    except KeyboardInterrupt:
      print("Shutting down")

if __name__=='__main__':
    main()

        
