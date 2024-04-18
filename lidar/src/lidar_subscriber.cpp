#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>  // Not used in this subscriber node
#include <std_msgs/Float32.h>

void rangeFrontCallback(const std_msgs::Float32::ConstPtr& range_front) {
//   ROS_INFO_STREAM("Front range: " << msg->data << "m");
  // Implement your logic to process the front range data
  // ...
}

void rangeBehindCallback(const std_msgs::Float32::ConstPtr& range_behind) {
//   ROS_INFO_STREAM("Behind range: " << msg->data << "m");
  // Implement your logic to process the behind range data
  // ...
}

void rangeRightCallback(const std_msgs::Float32::ConstPtr& range_right) {
//   ROS_INFO_STREAM("Right range: " << msg->data << "m");
  // Implement your logic to process the right range data
  // ...
}

void rangeLeftCallback(const std_msgs::Float32::ConstPtr& range_left) {
//   ROS_INFO_STREAM("Left range: " << msg->data << "m");
  // Implement your logic to process the left range data
  // ...
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "lidar_subscriber");
  ros::NodeHandle nh;

  ros::Subscriber sub_front = nh.subscribe("range_front", 10, rangeFrontCallback);
  ros::Subscriber sub_behind = nh.subscribe("range_behind", 10, rangeBehindCallback);
  ros::Subscriber sub_right = nh.subscribe("range_right", 10, rangeRightCallback);
  ros::Subscriber sub_left = nh.subscribe("range_left", 10, rangeLeftCallback);

  ros::spin();  // Blocks until ROS node is shutdown

  return 0;
}
