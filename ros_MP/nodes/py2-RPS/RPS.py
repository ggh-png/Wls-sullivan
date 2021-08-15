from hand_tracker import HandTracker
import cv2
import numpy as np
import pickle
from  sklearn.linear_model import LogisticRegressionCV

    
def transform_frame(data):
    for i in range(21):
        data[i, 0] = data[i,0]- data[0,0]
        data[i, 1] = data[i,1]- data[0,1]
    data = data.reshape(1, 42)
    return data

def get_estimator():
    with open('./nodes/py2-RPS/logregest_1200.pickle', 'rb') as f:
        estimator = pickle.load(f)
    return estimator

def get_winner(res):
    if(res[0] == res[1]):
        return None
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

def num_to_gesture(n):
    if(n == 0):
        return "Rock"
    if(n == 1):
        return "Paper"
    if(n == 2):
        return "Scissors"
    
def winner_result(frame, estimator):
    comp_move = np.random.randint(3)
    kp, box = detector(frame[:,:,::-1])
    player_move = estimator.predict(transform_frame(kp))
    result = get_winner([player_move, comp_move])
    cv2.putText(frame, "Your move is "+num_to_gesture(player_move), (100, 50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
    cv2.putText(frame, "My move is "+num_to_gesture(comp_move), (100, 150), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
    if(result == None):
        cv2.putText(frame, "No winner", (100, 250), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
    elif(result == 0):
        cv2.putText(frame, "You won!", (100, 250), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
    else:
        cv2.putText(frame, "I won!", (100, 250), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
    cv2.imshow('Webcam', frame)  
    
def play_loop(detector, estimator):
    palm_model_path = "./models/palm_detection.tflite"
    landmark_model_path = "./models/hand_landmark.tflite"
    anchors_path = "./data/anchors.csv" 
    cap = cv2.VideoCapture(0)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 960)
    #cap.set(cv2.CAP_PROP_FPS, 30)
    under_line = False
    count_moves = 0
    fps_reduce = 0
    kp, box = (0,0)
    while(1):  
        ret, frame = cap.read()
        try:
            if(fps_reduce == 3):
                kp, box = detector(frame[:,:,::-1])
                #cv2.circle(frame, (int(kp[0,0]), int(kp[0,1])), 10, (0,0,255))
                fps_reduce = 0
                cv2.putText(frame, "Moves num {}".format(count_moves), (300, 50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
                if(kp[0,1]>frame.shape[0]/2 and not under_line):
                    under_line = True
                    count_moves += 1
                    if(count_moves >= 3):
                        ret, frame = cap.read()
                        winner_result(frame, estimator)
                        count_moves = 0
                        cv2.putText(frame, "Again? (y/q)", (100, 450), cv2.FONT_HERSHEY_SIMPLEX, 2, (0,0,0),5)
                        while(1):
                            cv2.imshow('Webcam',frame)
                            if(cv2.waitKey(1) & 0xFF == ord('y')):
                                break
                elif(kp[0,1]<frame.shape[0]/2 and under_line):
                    under_line = False  
            else:
                    fps_reduce+=1
            cv2.line(frame, (int(0), int(frame.shape[0]/2)), (frame.shape[1], int(frame.shape[0]/2)),(0,255,0), 5)
            cv2.imshow('Webcam',frame)
        except ValueError:
            kp = 0
            cv2.line(frame, (int(0), int(frame.shape[0]/2)), (frame.shape[1], int(frame.shape[0]/2)),(0,255,0), 5)
            cv2.imshow('Webcam',frame)
        if cv2.waitKey(20) & 0xFF == ord('q'):
            break
    cap.release()
    cv2.destroyAllWindows()

#palm_model_path = "./nodes/py2-RPS/models/palm_detection.tflite"
#landmark_model_path = "./nodes/py2-RPS/models/hand_landmark.tflite"
#anchors_path = "./nodes/py2-RPS/data/anchors.csv" 
#estimator = get_estimator()
#detector = HandTracker(palm_model_path, landmark_model_path, anchors_path,
#                          box_shift=0.2, box_enlarge=1.3)
#play_loop(detector, estimator)
