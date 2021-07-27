#include <ros.h>
#include <std_msgs/Float32.h>
#include <robot_msgs/Motor.h>
#include <TimerOne.h>

#define ENC1_CHA    2  //INT.4
#define ENC1_CHB    3
#define rotation 3960

long    e1cnt = 0;
long    e1cnt_k = 0, e1cnt_k_1 = 0, d_e1cnt = 0;

float   m1_speed = 0;
float   m1_turn = 0;

bool t5_flag = 0;

void Enc1chA_ISR();
void Enc1chB_ISR();
void RPM();
void T5ISR();


ros::NodeHandle  nh;
robot_msgs::Motor sp_msg;
ros::Publisher pub("/Motor/speed", &sp_msg);



void setup() {
  pinMode(ENC1_CHA, INPUT_PULLUP);
  pinMode(ENC1_CHB, INPUT_PULLUP);

  //encoder 값을 받기 위한 외부 인터럽트 설정
  attachInterrupt(digitalPinToInterrupt(ENC1_CHA), Enc1chA_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC1_CHB), Enc1chB_ISR, CHANGE);
  Serial.begin(57600); 
  Timer1.initialize(10000); 

  nh.initNode();
  nh.advertise(pub);
  Timer1.attachInterrupt( T5ISR ); // enable the timer
}

void loop() 
{  
    nh.spinOnce();  
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
    sp_msg.right_motor.data = m1_speed;
    pub.publish(&sp_msg);
    Serial.println(m1_speed);    
  }
}


void T5ISR(){
  t5_flag = true;
  
}



void Enc1chA_ISR(){  e1cnt += (digitalRead(ENC1_CHA)==digitalRead(ENC1_CHB))?1:-1;}
void Enc1chB_ISR(){  e1cnt += (digitalRead(ENC1_CHA)==digitalRead(ENC1_CHB))?-1:1;}
