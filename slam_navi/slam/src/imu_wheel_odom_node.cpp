/*
wheel odometry vs imu + whell odometry
wheel odometry so weak about slip
in this case, I'll compare with wheel odom and imu + wheel odometry 
i checked imu acceleration have so much drift 
so, in my case, imu only correct orientation information (wheel linear velocity + imu angular velocity)
and IMU orientation have a little dritf bcuz integral calculation (In my opinion..)
so, if IMU have a little error , took only wheel odometry ! 
*/


#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>
#include <sensor_msgs/Imu.h>


#define DRIFT_IMU_ERROR 0.03


bool wheel_cal = false, imu_cal = false;
double vx , vy = 0;
double vth_wheel, vth_imu;


void wheel_Info(const geometry_msgs::Twist &msg){
    vx = msg.linear.x;
    vth_wheel = msg.angular.z;
    wheel_cal = true;
}

void imu_Info(const sensor_msgs::Imu &msg){

    vth_imu = msg.angular_velocity.z;
    imu_cal = true;

}






int main(int argc, char **argv){
    ros::init(argc, argv, "imu_wheel_odom_node");
    ros::NodeHandle n;
    ros::Subscriber wheel_sub = n.subscribe("Wheel_chair_robot/cmd_vel", 10, wheel_Info);
    ros::Subscriber imu_sub = n.subscribe("imu/data", 10, imu_Info);
    tf2_ros::TransformBroadcaster br;
    ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("wheel_chair_robot/imu/odom", 10);
    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now();

    double x = 0, y = 0,th = 0;
    double vth = 0;


    while (n.ok()){

        ros::spinOnce();

        if ( wheel_cal && imu_cal ){
            imu_cal = wheel_cal = false;
            current_time = ros::Time::now();

            double dt = (current_time - last_time).toSec();

            if( abs(vth_imu) > DRIFT_IMU_ERROR ) vth = vth_imu;
            else vth = vth_wheel;

            double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
            double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
            double delta_th = vth * dt;


            x += delta_x;
            y += delta_y;
            th += delta_th;

            geometry_msgs::TransformStamped transformStamped;


            transformStamped.header.stamp = ros::Time::now();//we need to give the transform being published a timestamp, in this case current time
            transformStamped.header.frame_id = "odom";
            transformStamped.child_frame_id = "base_footprint";
            transformStamped.transform.translation.x = x;
            transformStamped.transform.translation.y = y;
            transformStamped.transform.translation.z = 0; 

            //since all odometry is 6DOF we'll need a quaternion created from yaw
            geometry_msgs::Quaternion quat = tf::createQuaternionMsgFromYaw(th);

            transformStamped.transform.rotation = quat;
            // tf2::Quaternion q;
            // q.setRPY(0,0,th);
            // transformStamped.transform.rotation.x = q.x();
            // transformStamped.transform.rotation.y = q.y();
            // transformStamped.transform.rotation.z = q.z();
            // transformStamped.transform.rotation.w = q.w();

            br.sendTransform(transformStamped); // this is where real work is done


	    //next, we'll publish the odometry message over ROS
            nav_msgs::Odometry odom;
            odom.header.stamp = current_time;
            odom.header.frame_id = "odom";

            //set the position
            odom.pose.pose.position.x = x;
            odom.pose.pose.position.y = y;
            odom.pose.pose.position.z = 0.0;
            odom.pose.pose.orientation = tf::createQuaternionMsgFromYaw(th);

            //set the velocity
            odom.child_frame_id = "base_footprint";
            odom.twist.twist.linear.x = vx;
            odom.twist.twist.linear.y = vy;
            odom.twist.twist.angular.z = vth;

            //publish the message
            odom_pub.publish(odom);


            last_time = current_time;

        }



    }



    return 0;
}


