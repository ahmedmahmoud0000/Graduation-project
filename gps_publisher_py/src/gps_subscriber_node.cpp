#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
 std::string action ;
 float  


void actionCallback(const std_msgs::String::ConstPtr& msg) {
  // Access action data from msg->data
  ROS_INFO("Action: %s", msg->data.c_str());
}

void distanceCallback(const std_msgs::Int32::ConstPtr& msg) {
  // Access distance data from msg->data
  ROS_INFO("Distance: %d", msg->data);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "gps_subscriber_cpp");
  ros::NodeHandle nh;
  ros::Subscriber sub_action = nh.subscribe("gps_action", 10, actionCallback);
  ros::Subscriber sub_distance = nh.subscribe("gps_distance", 10, distanceCallback);
  ros::spin();
  

  return 0;
}
