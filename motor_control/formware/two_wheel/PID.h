#include <TimerFive.h>

#define rotation 3960

//for Encoder pin define
#define ENC1_CHA    18  //INT.5
#define ENC1_CHB    19

#define ENC2_CHA    2  //INT.4
#define ENC2_CHB    3

//for Motor I/O pin define
#define M1_I1       4 //dir 
#define M1_PWM      5

#define M2_I1       6 //dir 
#define M2_PWM      7


#define Kp1 5.// P-gain 
#define Ki1 .5// i-gain  
#define Kd1 3.0// d-gain 

#define Kp2 5.// P-gain 
#define Ki2 .5// i-gain  
#define Kd2 3.// d-gain 

//Variables
//Encoder value
long    e1cnt = 0;
long    e1cnt_k = 0, e1cnt_k_1 = 0, d_e1cnt = 0;
long    e2cnt = 0;
long    e2cnt_k = 0, e2cnt_k_1 = 0, d_e2cnt = 0;

//motor value
float   m1_speed = 0;
float   m1_turn = 0;
float   m2_speed = 0;
float   m2_turn = 0;

//for motor control variable
//motor1
float   m1_ref_spd = 0;
float   m1_err_spd = 0;
float   m1_err_spd_k_1 = 0;
float   m1_derr_spd = 0;
float   m1_err_sum = 0;
float   m1_ctrl_up = 0;
float   m1_ctrl_ui = 0;
float   m1_ctrl_ud = 0;
int     m1_ctrl_u = 0;
int     m1_ipwm_u = 0;
//motor2
float   m2_ref_spd = 0;
float   m2_err_spd = 0;
float   m2_err_spd_k_1 = 0;
float   m2_derr_spd = 0;
float   m2_err_sum = 0;
float   m2_ctrl_up = 0;
float   m2_ctrl_ui = 0;
float   m2_ctrl_ud = 0;
int     m2_ctrl_u = 0;
int     m2_ipwm_u = 0;

//-----------------------------------//
float   M1err_P = 0;
float   M1err_I = 0;
float   M1err_D = 0;
float   M1err_B = 0;
long    M1PID_val = 0;


float   M2err_P = 0;
float   M2err_I = 0;
float   M2err_D = 0;
float   M2err_B = 0;
long    M2PID_val = 0;
//== etr ==//
bool t5_flag = 0;

//------------------------------------'//

void Enc1chA_ISR();
void Enc2chA_ISR();
void Enc1chB_ISR();
void Enc2chB_ISR();


void M1vel_PID(int m1_ref_spd);
void M2vel_PID(int m2_ref_spd);
void RPM();


void M1doMotor(bool dir, long vel);
void M2doMotor(bool dir, long vel);

void T5ISR();

// =============================== ROS ======================================//
#include <ros.h>
#include <std_msgs/Float32.h>
#include <robot_msgs/Motor.h>

void messageCb( const robot_msgs::Motor& msg);

ros::NodeHandle  nh;
robot_msgs::Motor sp_msg;
ros::Publisher pub("/Motor/speed", &sp_msg);

ros::Subscriber<robot_msgs::Motor> sub("/Wheel_chair_robot/speed_set", &messageCb );

float speed_1 = 0;
float speed_2 = 0;

void messageCb(const robot_msgs::Motor& msg){
  speed_2 = msg.left_motor.data;
  speed_1 = msg.right_motor.data; 
}

// ========================================================================//


void setting(){
  // put your setup code here, to run once:
  pinMode(ENC1_CHA, INPUT_PULLUP);
  pinMode(ENC1_CHB, INPUT_PULLUP);
  pinMode(ENC2_CHA, INPUT_PULLUP);
  pinMode(ENC2_CHB, INPUT_PULLUP);

  pinMode(M1_I1, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_I1, OUTPUT);
  pinMode(M2_PWM, OUTPUT);

  //encoder 값을 받기 위한 외부 인터럽트 설정
  attachInterrupt(digitalPinToInterrupt(ENC1_CHA), Enc1chA_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC2_CHA), Enc2chA_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC1_CHB), Enc1chB_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC2_CHB), Enc2chB_ISR, CHANGE);  
  Serial.begin(115200);
  Timer5.initialize(10000); //10msec,
  Timer5.attachInterrupt(T5ISR); //T5ISR
  // ROS 통신 
  nh.getHardware()->setBaud(115200);
  nh.initNode(); 
  nh.subscribe(sub);
  nh.advertise(pub);
}


void M1vel_PID(float m1_ref_spd){
    
  RPM();
  m1_err_spd = m1_speed - m1_ref_spd;
  M1err_P = m1_err_spd;
  M1err_I += M1err_P;
  M1err_D = M1err_B - M1err_P;
  M1err_B = M1err_P;

  M1PID_val=((M1err_P * Kp1) + (M1err_I * Ki1) + (M1err_D * Kd1));
  m1_ctrl_u = M1PID_val;
  // 속도 오차가 생기면  
  M1doMotor(m1_ctrl_u >= 0 ? HIGH : LOW, m1_ctrl_u);
  //Serial.print("m1 speed : ");
  //Serial.println(m1_ref_spd);
  //Serial.print(m1_speed);
  //Serial.print(" | ");  
}


void M2vel_PID(float m2_ref_spd){
  
  RPM();
  m2_err_spd = m2_speed - m2_ref_spd;
  M2err_P = m2_err_spd;
  M2err_I += M2err_P;
  M2err_D = M2err_B - M2err_P;
  M2err_B = M2err_P;

  M2PID_val=((M2err_P * Kp2) + (M2err_I * Ki2) + (M2err_D * Kd2));
  m2_ctrl_u = M2PID_val;
  // 속도 오차가 생기면  
  M2doMotor(m2_ctrl_u >= 0 ? HIGH : LOW, m2_ctrl_u);
  //Serial.print("m2 speed : ");
  //Serial.println(m2_speed);
}

void RPM(){
  if(t5_flag){
    t5_flag = false;
    e1cnt_k = e1cnt;
    d_e1cnt = e1cnt_k - e1cnt_k_1;// 엔코더 값
    m1_speed = d_e1cnt * 60000/rotation;
    m1_speed /= (signed long)10;
    m1_turn= (float)e1cnt_k/3960;
    e1cnt_k_1 = e1cnt_k;//엔코더 초기화
  
    e2cnt_k = e2cnt;
    d_e2cnt = e2cnt_k - e2cnt_k_1;// 엔코더 값
    m2_speed = d_e2cnt * 60000/rotation;
    m2_speed /= (signed long)10;
    m2_turn= (float)e2cnt_k/3960;
    e2cnt_k_1 = e2cnt_k;//엔코더 초기화
    
    sp_msg.right_motor.data = m1_speed;
    sp_msg.left_motor.data = m2_speed;
    pub.publish(&sp_msg);    
  }
}


void M1doMotor(bool dir, long vel){
  
  digitalWrite(M1_I1, dir);
  vel = abs(vel);
  m1_ipwm_u = vel > 255 ? 255 : vel; 
  analogWrite(M1_PWM, m1_ipwm_u);
}

void M2doMotor(bool dir, long vel){
  
  digitalWrite(M2_I1, dir);
  vel = abs(vel);
  m2_ipwm_u = vel > 255 ? 255 : vel; 
  analogWrite(M2_PWM, m2_ipwm_u);
}


void T5ISR(){
  t5_flag = true; // dir 토글
  //RPM();
  M2vel_PID(speed_1);
  M1vel_PID(speed_2);   
}


void Enc1chA_ISR(){  e1cnt += (digitalRead(ENC1_CHA)==digitalRead(ENC1_CHB))?1:-1;}
void Enc2chA_ISR(){  e2cnt += (digitalRead(ENC2_CHA)==digitalRead(ENC2_CHB))?1:-1;}
void Enc1chB_ISR(){  e1cnt += (digitalRead(ENC1_CHA)==digitalRead(ENC1_CHB))?-1:1;}
void Enc2chB_ISR(){  e2cnt += (digitalRead(ENC2_CHA)==digitalRead(ENC2_CHB))?-1:1;}
