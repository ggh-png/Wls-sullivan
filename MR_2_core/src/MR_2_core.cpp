#include "ros/ros.h"                    
#include "MR_2_core.h"

//callback function ----------------------------------------------------------------------------------------------

void sub_MP_state_callback(const std_msgs::String::ConstPtr& msgs){

  string MP_state = msgs->data.c_str();
  string state_1 = "hungry";
  string state_2 = "tirsty";
  string state_3 = "toilet";

  if(MP_start_but&(!robot_is_working)){//bun one crick
     // zziiiiiiing!!!

    pushed_msg.data = true;
    pub_zing.publish(pushed_msg);

    if(state_1 == msgs->data.c_str()){
      count_1 += 1;
      count_2 = 0;
      count_3 = 0;
      ROS_INFO("stat_1 stack %d", count_1);
      if(count_1 == 3){
        ROS_INFO("go waypoint_1");
        TP_msg.data = 1;
        pub_TP_state.publish(TP_msg);
        go_waypoint(waypoint[0]);
        count_1 = 0;
        count_2 = 0;
        count_3 = 0;
        MP_start_but = 0;
      }
    }

    if(state_2 == msgs->data.c_str()){
      count_1 = 0;
      count_2 += 1;
      count_3 = 0;
      ROS_INFO("stat_2 stack %d", count_2);
      if(count_2 == 3){
        ROS_INFO("go waypoint_1");
        // pushed_msg;
        TP_msg.data = 2;
        pub_TP_state.publish(TP_msg);
        go_waypoint(waypoint[1]);
        count_1 = 0;
        count_2 = 0;
        count_3 = 0;
        MP_start_but = 0;
      }
    }

    if(state_3 == msgs->data.c_str()){
      count_1 = 0;
      count_2 = 0;
      count_3 += 1;
      ROS_INFO("stat_3 stack %d", count_3);
      if(count_3 == 3){
        ROS_INFO("go waypoint_1");
        // pushed_msg;
        TP_msg.data = 3;
        pub_TP_state.publish(TP_msg);
        go_waypoint(waypoint[2]);
        count_1 = 0;
        count_2 = 0;
        count_3 = 0;
        MP_start_but = 0;
      }
    }
  }

}


void sub_swich_callback(const std_msgs::Int16::ConstPtr& msgs){

  ROS_INFO(" %d: arduino_swich msg = 1",MP_start_but);
  MP_start_but = msgs->data;
  if(MP_start_but == 4){
    TP_msg.data = 5;
    pub_TP_state.publish(TP_msg);
    pushed_msg.data = 4;
    pub_zing.publish(pushed_msg);
    go_waypoint(waypoint[4]);// 긴급상황 
    

  }
}


void sub_amcl_pose_callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msgAMCL){
    poseAMCL[0] = msgAMCL->pose.pose.position.x;
    poseAMCL[1] = msgAMCL->pose.pose.position.y;
    poseAMCL[2] = msgAMCL->pose.pose.orientation.w;
    ROS_INFO("x : %f, y : %f, a : %f",poseAMCL[0], poseAMCL[1], poseAMCL[2]);  
}



void sub_waypoint_callback(const std_msgs::Int16::ConstPtr& msgs){
  if(msgs->data){
    ROS_INFO("go to waypoint %d", msgs->data-1);
    TP_msg.data = msgs->data;
    pub_TP_state.publish(TP_msg);
    go_waypoint(waypoint[msgs->data-1]);  
  }
}


void sub_set_waypoint_callback(const std_msgs::Int16::ConstPtr& msgs){

  int waypoint_num = msgs->data;
  if(waypoint_num){
    for(int i = 0; i < 3; i++){
      waypoint[waypoint_num-1][i] = poseAMCL[i];
    }
    ROS_INFO("set waypoint %d", waypoint_num);
  }
}

void sub_teleopkey_callback(const std_msgs::Int16::ConstPtr& msgs){

   int  telep_state = msgs->data;
   if(telep_state){
      if(telep_state == 1){ // go 
        motor_msgs.right_motor.data = 20;
        motor_msgs.left_motor.data = -20;
        pub_cmd_vel.publish(motor_msgs);
        ROS_INFO("gogogogogo");
      }
        if(telep_state == 2){ // back 
        motor_msgs.right_motor.data = 0;
        motor_msgs.left_motor.data = 0;
        pub_cmd_vel.publish(motor_msgs);
        ROS_INFO("stop");      
      }

        if(telep_state == 3){ // left 
        motor_msgs.right_motor.data = 10;
        motor_msgs.left_motor.data = 10;
        pub_cmd_vel.publish(motor_msgs);
        ROS_INFO("left");
      }

      if(telep_state == 4){ // right 
        motor_msgs.right_motor.data = -10;
        motor_msgs.left_motor.data = -10;
        pub_cmd_vel.publish(motor_msgs);
        ROS_INFO("right");
      }
      if(telep_state == 5){ // right 
        motor_msgs.right_motor.data = -20;
        motor_msgs.left_motor.data = 20;
        pub_cmd_vel.publish(motor_msgs);
        ROS_INFO("back");
      }
    }
}



 //실 사용 함수들 -----------------------------------------------------------------------------------------


void go_waypoint(double target_wayPoint[]){
  int be_waypoint[3] = {0,};
  int count = 0;

	MoveBaseClient ac("move_base", true);
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

    try{
        goal.target_pose.pose.position.x = target_wayPoint[0];
        goal.target_pose.pose.position.y = target_wayPoint[1];
        goal.target_pose.pose.orientation.w = target_wayPoint[2];
       }
    catch(int e){
      goal.target_pose.pose.position.x = 1.0;
      goal.target_pose.pose.position.y = 1.0;
      goal.target_pose.pose.orientation.w = 1.0;
    }
    ac.sendGoal(goal);
    pushed_msg.data = 2;
    pub_zing.publish(pushed_msg);
    //ac.waitForResult(ros::Duration( 120.0 ));

    ros::Rate loop_rate(1);
    robot_is_working = true;

    while(1){
      ROS_INFO("\nposeAMCL[%f,%f,%f] \t target_waypoint[%f,%f,%f]\nposeAMCL[%d,%d,%d] \t target_waypoint[%d,%d,%d]"
        ,poseAMCL[0],poseAMCL[1],poseAMCL[2]
        ,target_wayPoint[0],target_wayPoint[1],target_wayPoint[2]
        ,int(poseAMCL[0]+0.4),int(poseAMCL[1]+0.4),int(poseAMCL[2]+0.1)
        ,int(target_wayPoint[0]+0.4),int(target_wayPoint[1]+0.4),int(target_wayPoint[2]+0.1));

      if(poseAMCL[0]==be_waypoint[0]
        &poseAMCL[1]==be_waypoint[1]
        &poseAMCL[2]==be_waypoint[2]){
        ROS_INFO("not working");
        break;
      }
      for (int i =0;i<3;i++)be_waypoint[i] = poseAMCL[i];
      if(int(poseAMCL[0]+0.4)== int(target_wayPoint[0]+0.4)
        &int(poseAMCL[1]+0.4)== int(target_wayPoint[1]+0.4)
        &int(poseAMCL[2]+0.1)== int(target_wayPoint[2]+0.1)){
        ROS_INFO("succeeded");
        break;
      }
      ros::spinOnce();/* code */
      loop_rate.sleep();
      count++;
      if(count >=300){
        ROS_INFO("time over ....");
        break;
      }
    }

    robot_is_working = false;
    pushed_msg.data = 3;
    pub_zing.publish(pushed_msg);
    
}

//------------------------------------------------------------------------------------------------------



int main(int argc, char **argv)                         
{
  ros::init(argc, argv, "MR_2_core_node");           
  ROS_INFO("MR_2_core_node ON");
  ros::NodeHandle nh;                                   

  pub_zing = nh.advertise<std_msgs::Int16>("/MR_2/arduino/zing",10 );
  pub_cmd_vel = nh.advertise<robot_msgs::Motor>("/MR_2/speed_set",1);
  pub_TP_state = nh.advertise<std_msgs::Int16>("/MR_2/TP_state",1);

  sub_state  = nh.subscribe("/MR_2/MP_state", 10, sub_MP_state_callback); 
  sub_arduino_swich  = nh.subscribe("/MR_2/arduino/swich", 10, sub_swich_callback); 
  sub_amcl_pose = nh.subscribe("/amcl_pose", 10, sub_amcl_pose_callback);

  sub_waypoint = nh.subscribe("/MR_2/waypoint", 10, sub_waypoint_callback);
  sub_set_waypoint = nh.subscribe("/MR_2/set_waypoint", 10, sub_set_waypoint_callback);
  sub_teleop_key = nh.subscribe("/MR_2/teleopkey", 10, sub_teleopkey_callback);

  while (ros::ok())
  {
    ros::spinOnce();/* code */

  }
  return 0;
}
