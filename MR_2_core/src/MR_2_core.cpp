#include "ros/ros.h"                          // ROS Default Header File

#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <tf/transform_broadcaster.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

#include <sstream>
#include <iostream>
#include <string> 
using namespace std;

#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>

std_msgs::Int16 pushed_msg;

int num;
// ---
void go_waypoint(double wayPoint[]);
void zing_function(int num);

//cb 함수들 ----------------------------------------------------------------------------------------------


int count_1=0;
int count_2=0;
int count_3=0;

int MP_start_but = 0;


void sub_MP_state_callback(const std_msgs::String::ConstPtr& msg){

  string MP_state = msg->data.c_str();
  string state_1 = "hungry";
  string state_2 = "tirsty";
  string state_3 = "toilet";


  if(MP_start_but == 1){//bun one crick
     // zziiiiiiing!!!
    num =1;
    if(state_1 == msg->data.c_str()){
      count_1 += 1;
      count_2 = 0;
      count_3 = 0;
      ROS_INFO("stat_1 stack %d", count_1);
      if(count_1 == 3){
        ROS_INFO("go waypoint_1");
        double arr[] = {0,0, 1};
        go_waypoint(arr);
        count_1 = 0;
        count_2 = 0;
        count_3 = 0;
        MP_start_but = 0;
      }
    }

    if(state_2 == msg->data.c_str()){
      count_1 = 0;
      count_2 += 1;
      count_3 = 0;
      ROS_INFO("stat_2 stack %d", count_2);
      if(count_2 == 3){
        ROS_INFO("go waypoint_1");
        // pushed_msg;
        double arr[] = {2,0, 1};
        go_waypoint(arr);
        count_1 = 0;
        count_2 = 0;
        count_3 = 0;
        MP_start_but = 0;
      }
    }

    if(state_3 == msg->data.c_str()){
      count_1 = 0;
      count_2 = 0;
      count_3 += 1;
      ROS_INFO("stat_3 stack %d", count_3);
      if(count_3 == 3){
        ROS_INFO("go waypoint_1");
        // pushed_msg;
        double arr[] = {3,0, 1};
        go_waypoint(arr);
        count_1 = 0;
        count_2 = 0;
        count_3 = 0;
        MP_start_but = 0;
      }
    }
  }

}




void sub_swich_callback(const std_msgs::Int16::ConstPtr& msgs){

  ROS_INFO("arduino_swich msg = %d", msgs->data);
  MP_start_but +=msgs->data;
}


 //실 사용 함수들 -----------------------------------------------------------------------------------------

void go_waypoint(double wayPoint[]){

	MoveBaseClient ac("move_base", true);
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

    try{
        goal.target_pose.pose.position.x = wayPoint[0];
        goal.target_pose.pose.position.y = wayPoint[1];
        goal.target_pose.pose.orientation.w = wayPoint[2];
       }
    catch(int e){
      goal.target_pose.pose.position.x = 1.0;
      goal.target_pose.pose.position.y = 1.0;
      goal.target_pose.pose.orientation.w = 1.0;
    }
    ROS_INFO("start");
    ac.sendGoal(goal);
    num=2;
    ac.waitForResult(ros::Duration( 80.0 ));
    num=3;
    
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("end");
    else
      ROS_INFO("fail");
}





int main(int argc, char **argv)                         
{
  ros::init(argc, argv, "MR_2_core_node");           
  ROS_INFO("MR_2_core_node ON");
  ros::NodeHandle nh;                                   

  ros::Publisher pub_zing = nh.advertise<std_msgs::Int16>("/MR_2/arduino/zing",1);
 
  ros::Subscriber sub_state  = nh.subscribe("/MR_2/MP_state", 1, sub_MP_state_callback); 
  ros::Subscriber sub_arduino_swich  = nh.subscribe("/MR_2/arduino/swich", 1, sub_swich_callback); 



  while (ros::ok())
  {
    ros::spinOnce();/* code */
    // pushed_msg.data = num;
    // pub_zing.publish(pushed_msg);
  }
  return 0;
}
