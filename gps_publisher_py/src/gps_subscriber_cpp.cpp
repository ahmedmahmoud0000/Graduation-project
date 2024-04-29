#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <vector>

 std::string action ;
 std::string next_action ;
 float feedback= 0;
 std::vector<std::string> action_data_array({"non"});
 std::vector<std::int32_t> distance_data_array;
 int counter = 0;
 int array_length_action=0;
 int array_length_distance =0;
int goal_recived=0;

  float STD_range_front ;
  float STD_range_behind;
  float STD_range_right;
  float STD_range_left;
  float STD_avoid_right;
  float STD_avoid_left;

  // _Float32 range_behind = 0 ;
  // _Float32 range_right = 0 ;
  // _Float32 range_left = 0 ;

void actionCallback(const std_msgs::String::ConstPtr& msg) {
    std::string action_data_str(msg->data.c_str());
    // ROS_INFO("Action data array has %d elements", array_length_action);
    if(action_data_str=="done"){
goal_recived=1;
ROS_INFO("dibe recived");
    }
    else{

    action_data_array.push_back(action_data_str);  // Add message to the array
    // ROS_INFO("Action: %s (added to array)", action_data_str.c_str());
    array_length_action = action_data_array.size();
    }
}

void distanceCallback(const std_msgs::Int32::ConstPtr& msg) {
    std::int32_t distance_data_int (msg->data);
    distance_data_array.push_back(distance_data_int);  // Add message to the array
    // ROS_INFO("distace: %d (added to array)", distance_data_int);
    array_length_distance = distance_data_array.size();
    // ROS_INFO("Action data array has %d elements", array_length_distance);
}

void lidarCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{

//  range_front = scan_msg->ranges[360];
  float sum_range_front = 0 ;
  for( int i=180 ; i<540 ; i++)
  {

    sum_range_front = sum_range_front + scan_msg->ranges[i];
    
  }
    STD_range_front = sum_range_front /360 ;
  
//  range_behind = scan_msg->ranges[900];
  float sum_range_behind = 0 ;
  for( int i=720 ; i<1080 ; i++)
  {

    sum_range_behind = sum_range_behind + scan_msg->ranges[i];
    
  }
    STD_range_behind = sum_range_behind /360 ;

//  range_right = scan_msg->ranges[0];

   float sum_range_right = 0 ;
  for( int i=0 ; i<180 ; i++)
  {
    sum_range_right = sum_range_right + scan_msg->ranges[i];  
  }
    STD_range_right = (sum_range_right + scan_msg->ranges[1080]) /181 ;

//  range_left = scan_msg->ranges[630];
   float sum_range_left = 0 ;
  for( int i=540 ; i<720 ; i++)
  {

    sum_range_left = sum_range_left + scan_msg->ranges[i];
    
  }
    STD_range_left = sum_range_left /360 ;

// range from 0:360 use in avoidance func

    float sum_avoid_right = 0 ;
  for( int i=0 ; i<360 ; i++)
  {

    sum_avoid_right = sum_avoid_right + scan_msg->ranges[i];
    
  }
    STD_avoid_right = sum_avoid_right /296 ;
  
  // range from 360:630 use in avoidance func

    float sum_avoid_left = 0 ;
  for( int i=361 ; i< 630 ; i++)
  {

    sum_avoid_left = sum_avoid_left + scan_msg->ranges[i];
  
  }

    STD_avoid_left = sum_avoid_left /269 ;

 // std::cout<<range_front<<"         "<<range_behind<<"         "<<range_right<<"         "<<range_left<< std::endl; 

}

int avoidance_func (float x , float y)
{
  if (STD_avoid_right >= STD_avoid_left)          //      ممكن نبقي نقلل هنا السرعه 
  {
    return 1  ;    // 1 = turn right 
  }
  else return 0 ;  // 0 = turn left 
  
}

void avoid_left ()
{
  // Turn 90 degree Left 
  while(STD_range_right<1 && STD_range_front>1)
  {
     // move forward
  }
  // Turn 90 degree right
 }

void avoid_right ()
{
  // Turn 90 degree right 

  while(STD_range_left<1 && STD_range_front>1)
  {
     // move forward
  }

  // Turn 90 degree left
}


int main(int argc, char **argv) {
  ros::init(argc, argv, "gps_subscriber_cpp");
  ros::NodeHandle nh;
  ros::Subscriber sub_action = nh.subscribe("gps_action", 10, actionCallback);
  ros::Subscriber sub_distance = nh.subscribe("gps_distance", 10, distanceCallback);
  ros::Subscriber sub = nh.subscribe("scan", 1000, lidarCallback);
  


  while (ros::ok()) {
    ROS_INFO("main is running...");
    // std::cout<<"length_action: "<<array_length_action<<std::endl;
    // std::cout<<"length_distance: "<<array_length_distance<<std::endl;
    ros::spinOnce(); // Check for new messages and call callbacks
    ros::Rate loop_rate(10); 
    loop_rate.sleep();
   
if(goal_recived==1){
  
       for (int i = 0; i <= array_length_action ; i++)
    // for (auto i = action_data_array.begin(); i != action_data_array.end() ; i++)
    {
      ROS_INFO("Goal %d started ", i);
      std::vector<char> goal_action = action_data_array[i];
      //std::string goal_action = action_data_array.begin();//[i];
      ROS_INFO("1");
      float goal_distance = distance_data_array[i];
      ROS_INFO("2");
      std::string next_action = action_data_array[i++];
      ROS_INFO("3");
      feedback = goal_distance;
ROS_INFO("1");
      while (feedback)
      {
      // //  MOVE WITH ACTION & DISTANCE
			// // GET MOVED DISTACE FROM ROTARY ENCODER AND SUBSTRACT IT FROM FEEDBACK

      //   if (STD_range_front <= 1)
      //   {
      //     ROS_INFO("obstacle avoidnce started ");
      //     int x;
      //     int y;
      //       int direction_avoidance = avoidance_func(x,y);   // error to use avoidance function
      //       if (direction_avoidance == 0)
      //       {
      //         avoid_left ;     
      //       }
      //       else if ( direction_avoidance == 1 )
      //       {
      //         avoid_right     ;
      //       }
      //   }

        if (next_action == "turn_left" )
          if (feedback < 2 && STD_range_left > 10 )
          {
            ROS_INFO("Turning left ");
            // Turn left 90 degree
          }
        else if (next_action == "turn_right")
          if (feedback < 2 && STD_range_right > 10)
          {
            ROS_INFO("Turning Right ");
            // Turn right 90 degree 
          }

  

      }      


    }

}
  } 

  return 0;
}
