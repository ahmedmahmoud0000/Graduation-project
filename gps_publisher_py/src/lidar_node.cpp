#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>

float range_front = 0 ;
float range_behind = 0 ;
float range_right = 0 ;
float range_left = 0 ;

std_msgs::Float32 front_msg ;
std_msgs::Float32 behind_msg ;
std_msgs::Float32 right_msg ;
std_msgs::Float32 left_msg ;

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
 range_front = scan_msg->ranges[0];
}

void chatter_behindCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
 range_behind = scan_msg->ranges[180];
}

void chatter_rightCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
 range_right = scan_msg->ranges[90];
}

void chatter_leftCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
 range_left = scan_msg->ranges[270];
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "lidar_scan");

  ros::NodeHandle n;
  ros::Rate loop_rate(20);  

  ros::Publisher range_pub ;
  ros::Publisher range_behind_pub;
  ros::Publisher range_right_pub;
  ros::Publisher range_left_pub;


  range_pub= n.advertise<std_msgs::Float32>("range_front", 50);
  range_behind_pub= n.advertise<std_msgs::Float32>("range_behind", 50); 
  range_right_pub= n.advertise<std_msgs::Float32>("range_right", 50);
  range_left_pub= n.advertise<std_msgs::Float32>("range_left", 50);



  ros::Subscriber sub = n.subscribe("scan", 1000, chatterCallback);
  ros::Subscriber sub_behind= n.subscribe("scan", 1000, chatter_behindCallback);
  ros::Subscriber sub_right= n.subscribe("scan", 1000, chatter_rightCallback);
  ros::Subscriber sub_left= n.subscribe("scan", 1000, chatter_leftCallback);

 while (ros::ok()) {

    front_msg.data=range_front ;
    behind_msg.data=range_behind ;
    right_msg.data= range_right ;
    left_msg.data= range_left ;



    range_pub.publish(front_msg);
    range_behind_pub.publish(behind_msg);
    range_right_pub.publish(right_msg);
    range_left_pub.publish(left_msg);

    
  std::cout<<range_front<<"         "<<range_behind<<"         "<<range_right<<"         "<<range_left<< std::endl; 
  ros::spinOnce();
  loop_rate.sleep();
 }
  return 0;
}