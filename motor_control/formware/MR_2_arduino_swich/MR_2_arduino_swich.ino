/* 
 * Button Example for Rosserial
 */

#include <ros.h>
#include <std_msgs/Int16.h>


ros::NodeHandle nh;

std_msgs::Int16 pushed_msg;


const int button_pin = 2;
const int zing_pin = 3;

bool last_reading;
long last_debounce_time=0;
long debounce_delay=50;
bool published = true;
int zing_state=0;

void messageCb( const std_msgs::Int16& msg){
  zing_state = msg.data;
  if(zing_state==0){
    digitalWrite(3, LOW);   // zing OFF   
  }
  if(zing_state==1){
    digitalWrite(3, HIGH);   // zing ON   
  }
  if(zing_state==2){
    digitalWrite(3, HIGH);   // zing zing
    delay(500);
    digitalWrite(3, LOW);   // zing zing
    delay(500);
    digitalWrite(3, HIGH);   // zing zing
    delay(500);
    digitalWrite(3, LOW);   // zing zing
    delay(500);
  }
  if(zing_state==3){
    digitalWrite(3, HIGH);   // zing zing
    delay(500);
    digitalWrite(3, LOW);   // zing zing
    delay(500);
    digitalWrite(3, HIGH);   // zing zing
    delay(500);
    digitalWrite(3, LOW);   // zing zing
    delay(500);
  }
}

ros::Subscriber<std_msgs::Int16> sub_MP("/MR_2/arduino/zing", &messageCb);
ros::Publisher pub_button("/MR_2/arduino/swich", &pushed_msg);

void setup()
{
  nh.initNode();
  nh.advertise(pub_button);
  nh.subscribe(sub_MP);

  
  
  //initialize an LED output pin 
  //and a input pin for our push button
  pinMode(zing_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  
  //Enable the pullup resistor on the button
  digitalWrite(button_pin, HIGH);
  attachInterrupt(digitalPinToInterrupt(button_pin), but_ISR, LOW);

  
  //The button is a normally button
  last_reading = ! digitalRead(button_pin);
 
}
int state=0;
void loop()
{

  bool reading = ! digitalRead(button_pin);

  if (last_reading!= reading){
      last_debounce_time = millis();
      published = false;
  }
  
  //if the button value has not changed for the debounce delay, we know its stable
  if ( !published && (millis() - last_debounce_time)  > debounce_delay) {
    
    state++;
    pushed_msg.data = state;
    pub_button.publish(&pushed_msg);
    published = true;
    if(state == 4){
      state = 0;
      pushed_msg.data = state;
      pub_button.publish(&pushed_msg);
  }
  }
  last_reading = reading;  
  nh.spinOnce();
}



void but_ISR(){


}
