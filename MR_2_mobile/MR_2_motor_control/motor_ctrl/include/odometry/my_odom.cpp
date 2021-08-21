#ifndef H_ODOMETRY
#define H_ODOMETRY
#include <string>
#include <vector>
#include <cmath>
using namespace std;
class odometry
{
public:
	odometry(double dist,double radius,double init_time =0,double init_x=0,double init_y=0,double init_w=1.571);
	void set_velocity(double L ,double R);
	void set_IMU(double x,double y,double z,double r,double p,double w);
	void operate(double operate_time);
	struct
	{
		double x=0;
		double y=0;
		double w=0;
	}pose;
private:
	void find_speed();
	double imu_data[6]; 
	double time;
	double wheel_radius;
	double motor_dist;
	double left_speed;
	double right_speed;
	struct{
		double x =0;
		double y =0;
		double w =0;
	}robot_speed;
};

odometry::odometry(double dist,double radius,double init_time,double init_x ,double init_y,double init_w){
	motor_dist = dist;
	wheel_radius = radius;
	pose.x = init_x;
	pose.y = init_y;
	pose.w = init_w;
	time = init_time;
};

void odometry::set_velocity(double L ,double R){
	left_speed = L;
	right_speed =R;
}

void odometry::set_IMU(double x,double y,double z,double r,double p,double w){
	imu_data[0] = x;
	imu_data[1] = y;
	imu_data[2] = z;
	imu_data[3] = r;
	imu_data[4] = p;
	imu_data[5] = w;
}
void odometry::find_speed(){
	robot_speed.x = wheel_radius/2*cos(pose.w)*(left_speed+right_speed);
	robot_speed.y = wheel_radius/2*sin(pose.w)*(left_speed+right_speed);
	robot_speed.w = (-left_speed + right_speed)*wheel_radius/(2*motor_dist);
}
void odometry::operate(double operate_time){
	double v_x_temp = robot_speed.x;
	double v_y_temp = robot_speed.y;
	double v_w_temp = robot_speed.w;
	find_speed();
	pose.x += (v_x_temp + robot_speed.x)/2*(operate_time-time);
	pose.y += (v_y_temp + robot_speed.y)/2*(operate_time-time);
	pose.w += (v_w_temp + robot_speed.w)/2*(operate_time-time);
	pose.w = pose.w - ((int)(pose.w/3.1415))*3.1415;
	time = operate_time;
}
#endif