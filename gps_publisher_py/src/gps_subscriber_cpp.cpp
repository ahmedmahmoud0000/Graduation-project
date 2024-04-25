#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <vector>

 std::string action ;
 std::string next_action ;
 int distance=0 ;
 int feedback= 0;
 std::vector<std::string> action_data_array;
 std::vector<std::int32_t> distance_data_array;
 int counter = 0;
 int array_length_action=0;
 int array_length_distance =0;

void actionCallback(const std_msgs::String::ConstPtr& msg) {
    std::string action_data_str(msg->data.c_str());
    action_data_array.push_back(action_data_str);  // Add message to the array
    ROS_INFO("Action: %s (added to array)", action_data_str.c_str());
    array_length_action = action_data_array.size();
    ROS_INFO("Action data array has %d elements", array_length_action);
}

void distanceCallback(const std_msgs::Int32::ConstPtr& msg) {
    std::int32_t distance_data_int (msg->data);
    distance_data_array.push_back(distance_data_int);  // Add message to the array
    ROS_INFO("distace: %d (added to array)", distance_data_int);
    array_length_distance = distance_data_array.size();
    ROS_INFO("Action data array has %d elements", array_length_distance);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "gps_subscriber_cpp");
  ros::NodeHandle nh;
  ros::Subscriber sub_action = nh.subscribe("gps_action", 10, actionCallback);
  ros::Subscriber sub_distance = nh.subscribe("gps_distance", 10, distanceCallback);
  


  while (ros::ok()) {
    ROS_INFO("main is running...");
    std::cout<<"length_action: "<<array_length_action<<std::endl;
    std::cout<<"length_distance: "<<array_length_distance<<std::endl;
    ros::spinOnce(); // Check for new messages and call callbacks
    ros::Rate loop_rate(10); 
    loop_rate.sleep();
   

    // for (int32_t i = 0; i <= array_length_action ; i++)
    // {
    //   ROS_INFO("Action: %s (added to array)", action_data_array[1]);  
    
    // }
    











  } 
  
  
  // for ( int i=0 ; i<=3 ; i++)
  // {
  //   action = 

  // }

  return 0;
}
