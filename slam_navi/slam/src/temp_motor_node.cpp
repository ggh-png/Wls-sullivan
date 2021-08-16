#include <ros/ros.h>
#include <geometry_msgs/Twist.h>


int Control_cycle = 10; // 10hz
bool vel_cal = false;

double vx = 0, vth = 0;

void updateTargetVel(const geometry_msgs::Twist &msg){
    vx = msg.linear.x;
    vth = msg.angular.z;
    vel_cal = true;
}



int main(int argc, char **argv){

	ros::init(argc, argv, "temp_motor_node");
  	ros::NodeHandle nh;

//  	ros::Subscriber temp_vel_sub = nh.subscribe("/donationTF/cmd",10,tfVelCallback);
  	ros::Publisher temp_vel_pub = nh.advertise <geometry_msgs::Twist>("MR_2/odom_vel",10);
    ros::Subscriber sub = nh.subscribe("MR_2/cmd_vel", 10, updateTargetVel);
  	geometry_msgs::Twist temp_odom;
  	ros::Rate loop_rate(Control_cycle);

  	while (nh.ok()){
      ros::spinOnce(); // check for incoming messages


      if(vel_cal){
        vel_cal = false;
        temp_odom.linear.x = vx;
        temp_odom.angular.z = vth;

      }
  		
      printf(" linear Vel : %.3f (m / sec) \n",vx);
      printf(" angular Vel : %.3f (rad / sec)\n",vth);

  		temp_vel_pub.publish(temp_odom);



  		loop_rate.sleep();
  	}



    return 0;

}