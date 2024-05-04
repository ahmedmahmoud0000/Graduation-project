#include <ros/ros.h>
#include<rospy_tutorials/Floats.h>

rospy_tutorials::Floats joint_state;

void jointStateCallback(const rospy_tutorials::FloatsConstPtr& msg) {
  ROS_INFO("Received joint states:");
  


}

int main(int argc, char** argv) {
  ros::init(argc, argv, "encoder_sub");
  ros::NodeHandle nh;

  ros::Subscriber joint_state = nh.subscribe("joint_states_from_arduino", 10, jointStateCallback);

  ros::spin();  // Blocks until ROS node is shutdown

  return 0;
}
