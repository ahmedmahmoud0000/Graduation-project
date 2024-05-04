#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <vector>
#include <geometry_msgs/Twist.h>
#include<rospy_tutorials/Floats.h>

 rospy_tutorials::Floats joint_state;

 std::string action ;
 std::string goal_action ;
 std::string next_action ;
 std::vector<std::string> action_data_array_vect;
 std::vector<std::int32_t> distance_data_array_vect;
 std::string action_data_array[10];
 std::int32_t distance_data_array[10];

 int counter = 0;
 int array_length_action=0;
 int array_length_distance =0;
 int data_recived=0;

 float STD_range_front ;
 float STD_range_behind;
 float STD_range_right;
 float STD_range_left;
 float STD_avoid_right;
 float STD_avoid_left;
 uint64_t feedback=0;
 double right_feedback=20;
 double left_feedback=20;
 double old_left_encoder =0 ;
 double old_right_encoder =0 ;

  // _Float32 range_behind = 0 ;
  // _Float32 range_right = 0 ;
  // _Float32 range_left = 0 ;

void actionCallback(const std_msgs::String::ConstPtr& msg) {
  
    std::string action_data_str(msg->data.c_str());
    if(action_data_str!="done"){
    action_data_array[array_length_action]=action_data_str;
    array_length_action++;}
    else{
      data_recived=1;
    }
    //action_data_array.push_back(action_data_str);  // Add message to the array
    // ROS_INFO("Action: %s (added to array)", action_data_str.c_str());
    //array_length_action = action_data_array.size();
    // ROS_INFO("Action data array has %d elements", array_length_action);
}

void distanceCallback(const std_msgs::Int32::ConstPtr& msg) {
    std::int32_t distance_data_int (msg->data);
    distance_data_array[array_length_distance]=distance_data_int;
    array_length_distance++;
    //distance_data_array.push_back(distance_data_int);  // Add message to the array
    // ROS_INFO("distace: %d (added to array)", distance_data_int);
    //array_length_distance = distance_data_array.size();
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

void jointStateCallback(const rospy_tutorials::FloatsConstPtr& msg) {
  ROS_INFO("Received joint states:");


  double current_left_encoder = msg->data[0];
  double current_right_encoder  = msg->data[1];
  double buff_right = (current_right_encoder-old_right_encoder)*65 ;
  double buff_left =(current_left_encoder-old_right_encoder)*65;
  old_left_encoder=current_left_encoder;
  old_right_encoder=current_right_encoder;

  if (goal_action=="straight")
  {
    if (feedback>=buff_left)
    {
      feedback-=buff_left;
    }
    else feedback=0;
  }
  else if (goal_action == "turn right") right_feedback += buff_right;
  else if (goal_action == "turn left") left_feedback += buff_left;

}



int main(int argc, char **argv) {

  ros::init(argc, argv, "gps_subscriber_cpp");

  ros::NodeHandle nh;
  
  ros::Subscriber sub_action = nh.subscribe("gps_action", 10, actionCallback);
  ros::Subscriber sub_distance = nh.subscribe("gps_distance", 10, distanceCallback);
  ros::Subscriber sub = nh.subscribe("scan", 1000, lidarCallback);
  ros::Subscriber joint_state = nh.subscribe("joint_states_from_arduino", 10, jointStateCallback);
  
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);


  while (ros::ok()) {
    
    geometry_msgs::Twist msg;
    ROS_INFO("main is running...");
    // std::cout<<"length_action: "<<array_length_action<<std::endl;
    // std::cout<<"length_distance: "<<array_length_distance<<std::endl;
    ros::spinOnce(); // Check for new messages and call callbacks
    ros::Rate loop_rate(10); 
   
   if(data_recived==1){

   for (int i = 0; i <= array_length_action ; i++)
    {
    
      ROS_INFO("Goal %d started ", i);
      
      goal_action = action_data_array[i];
      feedback = distance_data_array[i]*1000;
      if(i<= array_length_action )
      {
        int d=i;
        d++;
        std::string next_action = action_data_array[d];
      }
      else
      {
        continue;
      }

      // if (goal_action=="straight")
      // {
      //    int new_feedback = goal_distance;
   
      // }

      if (goal_action == "turn right") 
      {
        right_feedback = 0 ;
     
      }

      else if (goal_action == "turn left")
      {
        left_feedback = 0 ;
         
      }

    while (right_feedback < 20)
          {
            msg.linear.x = 0;
            msg.linear.y = 0;
            msg.linear.z = 0;

            msg.angular.x = 0;
            msg.angular.y = 0;
            msg.angular.z = 20;

            //   if (STD_range_front <= 1)
            //   {
            //     ROS_INFO("obstacle avoidnce started ");
            //       int x,y;
            //       int direction_avoidance = avoidance_func(x,y);   // error to use avoidance function
            //       if (direction_avoidance == 0)
            //       {
            //         avoid_left      ;
            //       }
            //       else if ( direction_avoidance == 1 )
            //       {
            //         avoid_right   ;  
            //       }
            //   }

          //   if (next_action == "turn_left  ")
          //     if (feedback < 2000 && STD_range_left > 10 )
          //     {
          //       ROS_INFO("Turning left ");
          //       feedback = 0 ;
          //     }
          //   else if (next_action == "turn_right")
          //     if (feedback < 2000 && STD_range_right > 10)
          //     {
          //       ROS_INFO("Turning Right ");
          //       feedback = 0 ; 
          //     }
          }
         while (left_feedback < 20)
          {
            msg.linear.x = 0;
            msg.linear.y = 0;
            msg.linear.z = 0;

            msg.angular.x = 0;
            msg.angular.y = 0;
            msg.angular.z = -20;

          //   if (STD_range_front <= 1)
          //   {
          //     ROS_INFO("obstacle avoidnce started ");
          //       int x,y;
          //       int direction_avoidance = avoidance_func(x,y);   // error to use avoidance function
          //       if (direction_avoidance == 0)
          //       {
          //         avoid_left ;
          //       }
          //       else if ( direction_avoidance == 1 )
          //       {
          //         avoid_right ;  
          //       }
          //   }

          //   if (next_action == "turn_left  ")
          //     if (feedback < 2 && STD_range_left > 10 )
          //     {
          //       ROS_INFO("Turning left ");
          //       // Turn left 90 degree
          //     }
          //   else if (next_action == "turn_right")
          //     if (feedback < 2 && STD_range_right > 10)
          //     {
          //       ROS_INFO("Turning Right ");
          //       // Turn right 90 degree 
          //     }
          } 
    while (feedback)
      {
        msg.linear.x = 20;
        msg.linear.y = 0;
        msg.linear.z = 0;

        msg.angular.x = 0;
        msg.angular.y = 0;
        msg.angular.z = 0;

      //   if (STD_range_front <= 1)
      //   {
      //     ROS_INFO("obstacle avoidnce started ");
      //       int x,y;
      //       int direction_avoidance = avoidance_func(x,y);   // error to use avoidance function
      //       if (direction_avoidance == 0)
      //       {
      //         avoid_left      ;
      //       }
      //       else if ( direction_avoidance == 1 )
      //       {
      //         avoid_right   ;  
      //       }
      //   }

      //   if (next_action == "turn_left  ")
      //     if (feedback < 2 && STD_range_left > 10 )
      //     {
      //       ROS_INFO("Turning left ");
      //       // Turn left 90 degree
      //     }
      //   else if (next_action == "turn_right")
      //     if (feedback < 2 && STD_range_right > 10)
      //     {
      //       ROS_INFO("Turning Right ");
      //       // Turn right 90 degree 
      //     }
      }   
        
        
          
             
      }
          
    }
     std::string next_action = "none";
     data_recived=0;
    
    pub.publish(msg);
    loop_rate.sleep();
    break;

  }
  return 0;
}