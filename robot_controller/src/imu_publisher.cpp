#include <ros/ros.h>
#include "lino_msgs/Imu.h"
#include "sensor_msgs/Imu.h"


ros::Publisher imu_pub;
ros::Subscriber imu_raw_sub;
sensor_msgs::Imu imu_data;
ros::Time current_time,last_time;
void IMUCallback(const lino_msgs::Imu::ConstPtr& raw_imu_msg)
{
  imu_data.header.frame_id="imu_link";  
  imu_data.linear_acceleration.x =raw_imu_msg->linear_acceleration.x;
  imu_data.angular_velocity.z= raw_imu_msg->angular_velocity.z;
}


  int main(int argc, char** argv) {

    ros::init(argc, argv, "imu_publisher");
    ros::NodeHandle nh;

    imu_raw_sub = nh.subscribe("imu_raw", 50,IMUCallback);
    imu_pub = nh.advertise<sensor_msgs::Imu>("imu_data", 50);

    current_time = ros::Time::now();
    last_time = ros::Time::now();
    ros::Rate loop_rate(50);
    while (ros::ok())
    {
    ros::spinOnce();
    current_time = ros::Time::now();
    //publish the message
    imu_data.header.stamp = current_time;
    imu_pub.publish(imu_data);
     last_time = current_time; 
    loop_rate.sleep();
    }


 return 0;
  }