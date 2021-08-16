#include "ros/ros.h"                          // ROS Default Header File
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_broadcaster.h>
#include <sstream>
#include <iostream>


#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>



double wayPoint[3][3] = { 
  {0, -2, 1}, //way1 
  {1, -2.5, 1}, //way2
  {0, 0, 1} //way3
};  

//cb 함수들 ----------------------------------------------------------------------------------------------

void sub_waypoint_callback(const std_msgs::Int16::ConstPtr& msg)
{
  ROS_INFO("waypoint msg = %d", msg->Int16);   // Prints the 'stamp.sec' message
}

void sub_state_callback(const std_msgs::String::ConstPtr& msg){
  ROS_INFO("ros_mp msg = %d", msg->String);
}

void sub_swich_callback(const std_msgs::Bool::ConstPtr& msgs){
  ROS_INFO("arduino_swich msg = %d", msgs->Bool)
}

void sub_odometry_callback(const nav_msgs::Odometry &msg);
 
 //실 사용 함수들 -----------------------------------------------------------------------------------------

void bada_go_destination_blocking(double duration, double x, double y, double orien_z, double orien_w);






void navigation(){

  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

    try{
        goal.target_pose.pose.position.x = wayPoint[i][0];
        goal.target_pose.pose.position.y = wayPoint[i][1];
        goal.target_pose.pose.orientation.w = wayPoint[i][2];
       }
    catch(int e){

      goal.target_pose.pose.position.x = 1.0;
      goal.target_pose.pose.position.y = 1.0;
      goal.target_pose.pose.orientation.w = 1.0;
    }
    ROS_INFO("Sending move base goal");
    ac.sendGoal(goal);
    ac.waitForResult();
  }



int main(int argc, char **argv)                         // Node Main Function
{
  ros::init(argc, argv, "MR_2_core_node");            // Initializes Node Name
  ROS_INFO("MR_2_core_node ON");
  ros::NodeHandle nh;                                   // Node handle declaration for communication with ROS system


  ros::Subscriber sub_waypoint  = nh.subscribe("/MR_2/waypoint", 1, sub_waypoint_callback); //TODO: FIX CALLBACK FUNCTION
  ros::Subscriber sub_state  = nh.subscribe("/MR_2/state", 1, sub_state_callback); //TODO: FIX CALLBACK FUNCTION  
  ros::Subscriber sub_arduino_swich  = nh.subscribe("/MR_2/arduino/swich", 1, sub_swich_callback); //TODO: FIX CALLBACK FUNCTION
  ros::Subscriber sub_odom  = nh.subscribe("/MR_2/odom", 1, sub_odometry_callback); //TODO: FIX CALLBACK FUNCTION
    
  actionClient    = new MoveBaseClient("move_base", true); //move_base client 선언  


  ros::Subscriber ros_tutorial_sub = nh.subscribe("waypoint", 100, msgCallback);

  ros::spin();

  return 0;
}
