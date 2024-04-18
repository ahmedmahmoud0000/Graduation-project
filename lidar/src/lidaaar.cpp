#include "ros/ros.h"
#include <sensor_msgs/LaserScan.h> 
#include <std_msgs/Float32.h>
float range_behind = 0 ;

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
range_behind = scan_msg->ranges[180];

std::cout<<"         "<<range_behind<<std::endl; 

}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "lidaaar");

  ros::NodeHandle n;


  ros::Subscriber sub = n.subscribe("scan", 1000, chatterCallback);

  ros::spin();

  return 0;
}