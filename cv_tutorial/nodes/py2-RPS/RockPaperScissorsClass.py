#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Image
from std_msgs.msg import String
import cv2
import numpy as np
import pickle
from hand_tracker import HandTracker
from cv_bridge import CvBridge,  CvBridgeError

DELAY_RATE = 20

class RockPaperScissors:
    def __init__(self):
        rospy.init_node('rgb_object_detection')
        self.fps_reduce = 0
        self.palm_model_path = "/home/ggh/catkin_ws/src/cv_tutorial/nodes/py2-RPS/models/palm_detection.tflite"
        self.landmark_model_path = "/home/ggh/catkin_ws/src/cv_tutorial/nodes/py2-RPS/models/hand_landmark.tflite"
        self.anchors_path = "/home/ggh/catkin_ws/src/cv_tutorial/nodes/py2-RPS/data/anchors.csv" 
        self.estimator_path = "/home/ggh/catkin_ws/src/cv_tutorial/nodes/py2-RPS/logregest_1200.pickle"
        self.bridge = CvBridge()
        self.estimator = self.get_estimator()
        self.detector = HandTracker(self.palm_model_path, self.landmark_model_path, self.anchors_path, box_shift=0.2, box_enlarge=1.3)
        self.start_f = False
        self.under_line = False
        self.end_flag = False
        self.count_moves = 0
        self.delay_counter = 0
        self.end_frame = 0

        self.img_sub = rospy.Subscriber("/usb_cam/image_raw", Image, self.img_to_cv2, queue_size = 1)
        self.res_pub = rospy.Publisher("/RPS_node/result",  String, queue_size = 1)
        self.res_pub.publish("playing a b")
        

    def transform_frame(self, data):
        for i in range(21):
            data[i, 0] = data[i,0]- data[0,0]
            data[i, 1] = data[i,1]- data[0,1]
        data = data.reshape(1, 42)
        return data

    def img_to_cv2(self, arg):
        try:
            self.cv2_frame = self.bridge.imgmsg_to_cv2(arg, "bgr8")
            cv2.namedWindow('image',cv2.WINDOW_NORMAL)
            cv2.resizeWindow('image', 1240,960)
            self.play_loop()
        except CvBridgeError as e:
            print(e)
            
    def get_estimator(self):
        with open(self.estimator_path, 'rb') as f:
            estimator = pickle.load(f)
        return estimator
       
    def get_winner(self,res):
        if(res[0] == res[1]):
            return 2
        if(res[0] == 0 and res[1] == 1):
            return 1
        if(res[1] == 0 and res[0] == 1):
            return 0
        if(res[0] == 1 and res[1] == 2):
            return 1
        if(res[1] == 1 and res[0] == 2):
            return 0
        if(res[0] == 2 and res[1] == 0):
            return 1
        if(res[1] == 2 and res[0] == 0):
            return 0

    def show_res(self):
            cv2.imshow('image',self.end_frame)
            if(cv2.waitKey(1) & 0xFF == ord('y')):
                self.end_flag = False     
                self.res_pub.publish("playing a b")
        
    
    def num_to_gesture(self, n):
        if(n == 0):
            return "Rock"
        if(n == 1):
            return "Paper"
        if(n == 2):
            return "Scissors"
            
    def winner_result(self):
        comp_move = np.random.randint(3)
        kp, box = self.detector(self.cv2_frame[:,:,::-1])
        player_move = self.estimator.predict(self.transform_frame(kp))
        result = self.get_winner([player_move, comp_move])
        cv2.putText(self.cv2_frame, "Your move is "+self.num_to_gesture(player_move), (100, 50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
        cv2.putText(self.cv2_frame, "My move is "+self.num_to_gesture(comp_move), (100, 150), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
        if(result == None):
            cv2.putText(self.cv2_frame, "No winner", (100, 250), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
        elif(result == 0):
            cv2.putText(self.cv2_frame, "You won!", (100, 250), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
        else:
            cv2.putText(self.cv2_frame, "I won!", (100, 250), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
        self.end_frame = self.cv2_frame
        self.res_pub.publish(self.num_to_gesture(comp_move)+" "+ self.num_to_gesture(player_move)+" "+str(result))
        self.end_flag = False
        #cv2.imshow('Webcam', self.cv2_frame)
        
    def play_loop(self):
        kp, box = (0,0)

        try:
            if(self.end_flag):
                self.show_res()
                return
            if(self.fps_reduce == 3):
                kp, box = self.detector(self.cv2_frame[:,:,::-1])
                self.fps_reduce = 0
                print(self.count_moves)
                if(kp[0,1]>self.cv2_frame.shape[0]/2 and not self.under_line):
                    self.count_moves += 1
                    self.under_line = True
                    if(self.count_moves >= 3):
                        self.winner_result()
                        self.count_moves = 0
                        self.end_flag = True
                        cv2.putText(self.cv2_frame, "Again? (y/q)", (100, 450), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)                   
                elif(kp[0,1]<self.cv2_frame.shape[0]/2 and self.under_line):
                    self.under_line = False  
            else:
                    self.fps_reduce+=1
            #cv2.line(self.cv2_frame, (int(0), int(self.cv2_frame.shape[0]/2)), (self.cv2_frame.shape[1], int(self.cv2_frame.shape[0]/2)),(0,255,0), 5)
        except ValueError:
            kp = 0
        cv2.line(self.cv2_frame, (int(0), int(self.cv2_frame.shape[0]/2)), (self.cv2_frame.shape[1], int(self.cv2_frame.shape[0]/2)),(0,255,0), 5)
        cv2.putText(self.cv2_frame, "Moves num {}".format(self.count_moves), (800, 50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
        cv2.imshow('image',self.cv2_frame)
        while(1):    
            if(cv2.waitKey(5) ):
                break
        
def main():
    rps = RockPaperScissors()
    try:
      rospy.spin()
    except KeyboardInterrupt:
      print("Shutting down")

if __name__=='__main__':
    main()
