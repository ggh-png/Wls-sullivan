#include "ros/ros.h"                          // ROS Default Header File
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <tf/transform_broadcaster.h>

#include <sstream>
#include <iostream>
#include <string> 

#include <std_msgs/Int16.h>
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include <std_msgs/String.h>
#include <robot_msgs/Motor.h>

using namespace std;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

std_msgs::Int16 pushed_msg;
robot_msgs::Motor motor_msgs;
std_msgs::Int16 TP_msg;


ros::Publisher pub_zing;
ros::Publisher pub_cmd_vel;
ros::Publisher pub_TP_state;


ros::Subscriber sub_state;
ros::Subscriber sub_arduino_swich;
ros::Subscriber sub_amcl_pose;
ros::Subscriber sub_waypoint;
ros::Subscriber sub_set_waypoint;
ros::Subscriber sub_teleop_key;

//navi function


void go_waypoint(double wayPoint[]);
void sub_MP_state_callback(const std_msgs::String::ConstPtr& msgs);
void sub_swich_callback(const std_msgs::Int16::ConstPtr& msgs);
void sub_amcl_pose_callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msgAMCL);
void sub_waypoint_callback(const std_msgs::Int16::ConstPtr& msgs);
void sub_set_waypoint_callback(const std_msgs::Int16::ConstPtr& msgs);
void sub_teleopkey_callback(const std_msgs::Int16::ConstPtr& msgs);

//  ----------------------------------------------------------------------------------------------


double waypoint[5][3] = {{0, 0, 1},
                            {-3, 5, 1},
                            {5, 11, 1},
                            {0,0,2},
                            {0,0,3}};

int count_1=0;
int count_2=0;
int count_3=0;

int MP_start_but = 0;

bool robot_is_working = false;
double poseAMCL[3];
