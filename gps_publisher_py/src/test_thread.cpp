#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <vector>
#include <geometry_msgs/Twist.h>
#include<rospy_tutorials/Floats.h>

// Callbacks
void pc_pub_img_callback(const sensor_msgs::Image::ConstPtr& msg){
      ROS_INFO("Img:Callback");
}

void pc_pub_laser_callback(const sensor_msgs::LaserScan::ConstPtr& msg){
      ROS_INFO("Laser:Callback");
}

void pc_pub_twist_callback(const geometry_msgs::TwistStamped::ConstPtr& msg){
      ROS_INFO("Twist:Callback");
}

int main(int argn, char* args[])
{
  ros::init(argn, args, "arm_to_fpga");
  ros::NodeHandle n_img;
  ros::NodeHandle n_laser;
  ros::NodeHandle n_twist;

  ros::CallbackQueue Queue_img;
  ros::CallbackQueue Queue_laser;
  ros::CallbackQueue Queue_twist;

  n_img.setCallbackQueue(&Queue_img);
  n_laser.setCallbackQueue(&Queue_laser);
  n_twist.setCallbackQueue(&Queue_twist);

  ros::Subscriber s_img = n_img.subscribe("/FPGA_ROS_Scheduler/pc_pub_img", 1, pc_pub_img_callback);
  ros::Subscriber s_laser = n_laser.subscribe("/FPGA_ROS_Scheduler/pc_pub_laser", 1, pc_pub_laser_callback);
  ros::Subscriber s_twist = n_twist.subscribe("/FPGA_ROS_Scheduler/pc_pub_twist", 1, pc_pub_twist_callback);

  while(ros::ok())
  {
    if(!Queue_img.isEmpty() && !Queue_laser.isEmpty() && !Queue_twist.isEmpty())
    {
      Queue_img.callOne(ros::WallDuration(1.0));
      Queue_laser.callOne(ros::WallDuration(1.0));
      Queue_twist.callOne(ros::WallDuration(1.0));
    }
    ros::spinOnce();
  }    
  return 0;
}