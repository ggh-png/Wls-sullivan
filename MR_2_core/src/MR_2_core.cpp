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




// ---
void go_waypoint(double wayPoint[]);


//cb 함수들 ----------------------------------------------------------------------------------------------


void sub_waypoint_callback(const std_msgs::Int16::ConstPtr& msg)
{
   ROS_INFO("waypoint msg = %d", msg->data);   // Prints the 'stamp.sec' message
}



int count_1;
int count_2;
int count_3;

bool MP_start_but = 0;


void sub_MP_state_callback(const std_msgs::String::ConstPtr& msg){
  

  string MP_state = msg->data.c_str();
  string state_1 = "hungry";
  string state_2 = "tirsty";
  string state_3 = "toilet";

  zing_function(0)

  if(MP_start_but == 1){//bun one crick
     // zziiiiiiing!!!
    if(state_1 == msg->data.c_str()){
      count_1 += 1;
      count_2 = 0;
      count_3 = 0;
      ROS_INFO("stat_1 stack %d", count_1);
      if(count_1 == 3){
        ROS_INFO("go waypoint_1");
        zing_function(1) //zing X 
        double arr[] = {0,0, 1};
        go_waypoint(arr);
        count_1 = 0;
        count_2 = 0;
        count_3 = 0;
        MP_start_but = 0;
      }
    }

    if(state_2 == msg->data.c_str()){
      count_2 += 1;
      count_1 = 0;
      count_3 = 0;
      ROS_INFO("stat_2 stack %d", count_2);
      if(count_2 == 3){
        ROS_INFO("go waypoint_2");
        double arr[] = {4, 2, 1};
        go_waypoint(arr);
        count_1 = 0;
        count_2 = 0;
        count_3 = 0;
      }
    }

    if(state_3 == msg->data.c_str()){
      count_3 += 1;
      count_1 = 0;
      count_2 = 0;
      ROS_INFO("stat_3 stack %d", count_3);
      if(count_3 == 3){
        ROS_INFO("go waypoint_3");
        double arr[] = {5, 2, 1};
        go_waypoint(arr);
        count_1 = 0;
        count_2 = 0;
        count_3 = 0;
      }
    }
  }
}




void sub_swich_callback(const std_msgs::Bool::ConstPtr& msgs){
  ROS_INFO("arduino_swich msg = %d", msgs->data);
  MP_start_but +=1;
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
    zing_function(2); // zing zing 
    ac.waitForResult(ros::Duration( 80.0 ));
    zing_function(3) // zing zing zing 
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("end");
    else
      ROS_INFO("fail");
}



void zing_function(int num){
  pub ziiiiiiiing(num);//for arduino code 
}




int main(int argc, char **argv)                         // Node Main Function
{
  ros::init(argc, argv, "MR_2_core_node");            // Initializes Node Name
  ROS_INFO("MR_2_core_node ON");
  ros::NodeHandle nh;                                   // Node handle declaration for communication with ROS system


  ros::Subscriber sub_waypoint  = nh.subscribe("/MR_2/waypoint", 1, sub_waypoint_callback); 
  ros::Subscriber sub_state  = nh.subscribe("/MR_2/MP_state", 1, sub_MP_state_callback); 
  ros::Subscriber sub_arduino_swich  = nh.subscribe("/MR_2/arduino/swich", 1, sub_swich_callback); 


  while (ros::ok())
  {
    ros::spinOnce();/* code */
  }
  return 0;
}


