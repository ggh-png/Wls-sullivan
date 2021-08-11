#!/usr/bin/env python

import roslib; roslib.load_manifest('cv_tutorial')
import cv2
import numpy as np
import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
from sklearn.linear_model import LogisticRegressionCV
from RPS import *


def callback(img, estimator):
    print("Penis")
    return 0

def preprocessing(estimator, detector):
    rospy.init_node("preprocessing_node")
    img = rospy.Subscriber("/cv_camera/image_raw", Image, callback)
    pub = rospy.Publisher("res_im",Image)
    #pub.publish(img)
    rospy.spin()

if __name__ == '__main__':
    estimator = get_estimator()
    palm_model_path = "./nodes/py2-RPS/models/palm_detection.tflite"
    landmark_model_path = "./nodes/py2-RPS/models/hand_landmark.tflite"
    anchors_path = "./nodes/py2-RPS/data/anchors.csv" 
    estimator = get_estimator()
    detector = HandTracker(palm_model_path, landmark_model_path, anchors_path,
                           box_shift=0.2, box_enlarge=1.3)
    preprocessing(estimator, detector)
    
