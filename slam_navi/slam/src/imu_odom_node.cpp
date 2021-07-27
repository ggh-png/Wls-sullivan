#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>
#include <geometry_msgs/Twist.h>


double quaternion_x,quaternion_y,quaternion_z,quaternion_w;
double ax,ay; // acceleration
bool odom_cal = false;


void imu_2D_Odom(const sensor_msgs::Imu &msg){
	quaternion_x = msg.orientation.x;
	quaternion_y = msg.orientation.y;
	quaternion_z = msg.orientation.z;
	quaternion_w = msg.orientation.w;

	ax = msg.linear_acceleration.x;
	ay = msg.linear_acceleration.y;

	odom_cal = true;
}



int main(int argc, char** argv){
	ros::init(argc, argv, "imu_odom_node");
    ros::NodeHandle nh;
    ros::Subscriber imu_data_sub = nh.subscribe("imu/data", 10, imu_2D_Odom);
    tf2_ros::TransformBroadcaster br;

    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now();
 

    double x = 0 , y = 0;
    double vx = 0 , vy = 0;
    while(nh.ok()){
    	ros::spinOnce(); // check for incoming messages


    	if(odom_cal){
    		odom_cal = false;
    		current_time = ros::Time::now();
    		double dt = (current_time - last_time).toSec();
    		double delta_vx = ax * dt;
    		double delta_vy = ay * dt;

    		vx += delta_vx;
    		vy += delta_vy;

    		x += vx*dt;
    		y += vy*dt;

            geometry_msgs::TransformStamped transformStamped;

    		transformStamped.header.stamp = ros::Time::now();//we need to give the transform being published a timestamp, in this case current time
			transformStamped.header.frame_id = "odom";
			transformStamped.child_frame_id = "base_footprint";
			transformStamped.transform.translation.x = vx;
			transformStamped.transform.translation.y = vy;
			transformStamped.transform.translation.z = 0; 

    		transformStamped.transform.rotation.x = quaternion_x;
			transformStamped.transform.rotation.y = quaternion_y;
			transformStamped.transform.rotation.z = quaternion_z;
			transformStamped.transform.rotation.w = quaternion_w;

			br.sendTransform(transformStamped); // this is where real work is done

			last_time = current_time;
    	}
    }


    return 0;


}