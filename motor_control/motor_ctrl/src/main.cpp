#include "ros/ros.h"
#include <cmath>
//#include "my_odom.cpp"
#include "robot_msgs/Motor.h"
#include "geometry_msgs/Twist.h"

#define WHEEL_RADIUS 0.0575
#define ROBOT_RADIUS 0.2
#define RPM_to_RADIAN 3.141592654*2/60
#define RADIAN_to_RPM 60/(3.141592654*2)
#define PI 3.141592654
void CallBack_1(const robot_msgs::Motor &msg);
void CallBack_2(const geometry_msgs::Twist &msg);

geometry_msgs::Twist robot_state;

ros::Publisher *pub1,*pub2;
int main(int argc,char**argv){
	ros::init(argc,argv,"ODOME_NODE");
	ros::NodeHandle nh;
	ros::Subscriber sub1 = nh.subscribe("/Motor/speed",1,CallBack_1);
	ros::Subscriber sub2 = nh.subscribe("/cmd_vel",1,CallBack_2);
	ros::Publisher speed1 = nh.advertise<geometry_msgs::Twist>("/MR_2/cmd_vel",1);
	ros::Publisher speed2 = nh.advertise<robot_msgs::Motor>("/MR_2/speed_set",1);
	pub1 = &speed1;
	pub2 = &speed2;
	while(ros::ok()){
		ros::spinOnce();
	}
	return 0;
}

void CallBack_1(const robot_msgs::Motor &msg){
	double left = msg.left_motor.data*RPM_to_RADIAN;
	double right = msg.right_motor.data*RPM_to_RADIAN;
	robot_state.linear.x = WHEEL_RADIUS*left/2 + WHEEL_RADIUS*right/2;
	robot_state.linear.y = 0;
	robot_state.linear.z = 0;
	robot_state.angular.x = 0;
	robot_state.angular.y = 0;
	robot_state.angular.z = -WHEEL_RADIUS/(2*ROBOT_RADIUS)*left + WHEEL_RADIUS/(2*ROBOT_RADIUS)*right;
	pub1->publish(robot_state);
}

// void CallBack_2(const geometry_msgs::Twist &msg){
// 	robot_msgs::Motor motor_msgs;
// 	double right = (ROBOT_RADIUS*msg.angular.z + msg.linear.x)/WHEEL_RADIUS;
// 	double left = right - 2*ROBOT_RADIUS/WHEEL_RADIUS*msg.angular.z;
// 	motor_msgs.right.data = right*RADIAN_to_RPM*4;
// 	motor_msgs.left.data = left*RADIAN_to_RPM*4;
// 	ROS_INFO("MOTOR SPEED \tLEFT : %f, RIGHT : %f",motor_msgs.left.data,motor_msgs.right.data);
// 	pub2->publish(motor_msgs);
// }


void CallBack_2(const geometry_msgs::Twist &msg){
	robot_msgs::Motor motor_msgs;

	double linear_left_RPM,linear_right_RPM;
	linear_left_RPM =linear_right_RPM= msg.linear.x/(2*PI*WHEEL_RADIUS)*60;

	double angular_left_RPM, angular_right_RPM;
	angular_right_RPM = msg.angular.z * (ROBOT_RADIUS/WHEEL_RADIUS) * 60 / 2 / PI;
	
	angular_left_RPM = -angular_right_RPM;

	double left_target_RPM = linear_left_RPM + angular_left_RPM;
	double right_target_RPM = linear_right_RPM + angular_right_RPM;

	motor_msgs.right_motor.data = right_target_RPM;
	motor_msgs.left_motor.data = left_target_RPM;
	// ROS_INFO("linear_vel : %f(m/s)",msg.linear.x);
	// ROS_INFO("angular_vel : %f(rad/s)",msg.angular.z);
	// ROS_INFO("MOTOR TARGET RPM  \t: %f",angular_right_RPM);
	// ROS_INFO("WHEEL_RADIUS : %.3f",WHEEL_RADIUS);
	// ROS_INFO("ROBOT_RADIUS : %.3F",ROBOT_RADIUS);
	
	// ROS_INFO("MOTOR TARGET RPM \tLEFT : %f, RIGHT : %f",motor_msgs.left.data,motor_msgs.right.data);
	pub2->publish(motor_msgs);
}
