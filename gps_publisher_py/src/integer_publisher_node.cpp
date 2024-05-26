#include <ros/ros.h>
#include <std_msgs/Int8.h>

int main(int argc, char **argv) {
  // Initialize ROS node
  ros::init(argc, argv, "integer_publisher_node");

  // Create a node handle
  ros::NodeHandle nh;

  // Create a publisher for "integer_topic" with queue size of 10
  ros::Publisher int_pub = nh.advertise<std_msgs::Int8>("integer_topic", 10);

  // Set loop rate to 10 Hz
  ros::Rate loop_rate(10);

  int8_t count = 0;

  while (ros::ok()) {
    // Update the integer value (replace with your logic)
      // Increment for this example

    // Create a message object
    std_msgs::Int8 msg;
    msg.data = count;

    // Publish the message
    int_pub.publish(msg);

    // Process ROS callbacks
    ros::spinOnce();

    // Sleep to maintain loop rate
    loop_rate.sleep();
  }

  return 0;
}
