#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int8.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <vector>
#include <geometry_msgs/Twist.h>
#include<rospy_tutorials/Floats.h>
#include <std_msgs/ByteMultiArray.h>
#include <sstream>



 rospy_tutorials::Floats joint_state;

 std::string action ;
 std::string goal_action ;
 std::string next_action ;
 std::vector<std::string> action_data_array_vect;
 std::vector<std::int32_t> distance_data_array_vect;
 std::string action_data_array[10];
 std::int32_t distance_data_array[10];

 std::string recieved_encoder_data;

 int counter = 0;
 int array_length_action=0;
 int array_length_distance =0;
 int data_recived=0;
int flag_i=0;
int flag_turn=0;
int stop_flag=0;

 float STD_range_front ;
 float STD_range_behind;
 float STD_range_right;
 float STD_range_left;
 float STD_avoid_right;
 float STD_avoid_left;
 long feedback=0;
 int turn_limit=20;
 double right_feedback=21;
 double left_feedback=21;
 double old_left_encoder =0 ;
 double old_right_encoder =0 ;



 int i=0;

  // _Float32 range_behind = 0 ;
  // _Float32 range_right = 0 ;
  // _Float32 range_left = 0 ;

void encodercallback(const std_msgs::String& encoder_msg) {

  recieved_encoder_data=encoder_msg.data;

  std::istringstream iss(recieved_encoder_data);
  int Left_Encoder, Right_Encoder;

  if (iss >> Left_Encoder >> Right_Encoder) {
    std::cout << "Left Encoder: " << Left_Encoder << std::endl;
    std::cout << "Right Encoder: " << Right_Encoder << std::endl;
  } 
  if(Right_Encoder<0){
  Right_Encoder*=-1;
  }

  //ROS_INFO_STREAM(current_right_encoder);

    if(Left_Encoder<0){
    Left_Encoder*=-1;
  }

  // double buff_right = (current_right_encoder-old_right_encoder)*65 ;
  // double buff_left =(current_left_encoder-old_right_encoder)*65;

  Right_Encoder  *= 1;
  Left_Encoder *=1;
  old_left_encoder=Left_Encoder;
  old_right_encoder=Right_Encoder;

  // ROS_INFO_STREAM("buff_right= "<<"  " <<current_right_encoder<<"buff_left =  "<<current_left_encoder);
  // int counter =0;

  if (goal_action=="straight")
  {
    if (feedback>=Right_Encoder)
    {
      feedback-=Right_Encoder;
      //ROS_INFO_STREAM(feedback);
    }
    else {feedback=0;
    ROS_INFO("nnjn");
  ROS_INFO_STREAM(i);
    }
    if((feedback==0)&&(flag_i==1)){
      i++;
      flag_i=0;
    }
  }
  else if (goal_action == "turn-right") {
    
    right_feedback += Right_Encoder;
        if((right_feedback>turn_limit)&&(flag_i==1)){
      i++;
      flag_i=0;
    }
  }
  else if (goal_action == "turn-left") {
    left_feedback += Left_Encoder;
    if((left_feedback>turn_limit)&&(flag_i==1)){
      i++;
      flag_i=0;
    }
  }
  // ROS_INFO_STREAM("counter= "<<"  " <<counter);

 counter++;
}

void actionCallback(const std_msgs::String::ConstPtr& msg) {
  
    std::string action_data_str(msg->data.c_str());
    if(action_data_str!="done"){
    action_data_array[array_length_action]=action_data_str;
    array_length_action++;}
    else{
      data_recived=1;
      // goal_action = action_data_array[i];
      // feedback = distance_data_array[i]*1000;
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
  if(STD_range_front>100){

    stop_flag=0;
  }
  else{
    stop_flag=1;
  }
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

// void jointStateCallback(const rospy_tutorials::FloatsConstPtr& msg) {
//   //ROS_INFO("Received joint states:");


//   double current_left_encoder = msg->data[1];
//   double current_right_encoder  = msg->data[0];
//   if(current_right_encoder<0){
//     current_right_encoder*=-1;
//   }
//   //ROS_INFO_STREAM(current_right_encoder);
//     if(current_left_encoder<0){
//     current_left_encoder*=-1;
//   }
//   // double buff_right = (current_right_encoder-old_right_encoder)*65 ;
//   // double buff_left =(current_left_encoder-old_right_encoder)*65;
//  current_right_encoder  *= 1;
//  current_left_encoder *=1;
//   old_left_encoder=current_left_encoder;
//   old_right_encoder=current_right_encoder;
//   // ROS_INFO_STREAM("buff_right= "<<"  " <<current_right_encoder<<"buff_left =  "<<current_left_encoder);
//     // int counter =0;

//   if (goal_action=="straight")
//   {
//     if (feedback>=current_right_encoder)
//     {
//       feedback-=current_right_encoder;
//        //ROS_INFO_STREAM(feedback);
//     }
//     else {feedback=0;
//     ROS_INFO("nnjn");
//   ROS_INFO_STREAM(i);
//     }
//     if((feedback==0)&&(flag_i==1)){
//       i++;
//       flag_i=0;
//     }
//   }
//   else if (goal_action == "turn-right") {
    
//     right_feedback += current_right_encoder;
//         if((right_feedback>turn_limit)&&(flag_i==1)){
//       i++;
//       flag_i=0;
//     }
//   }
//   else if (goal_action == "turn-left") {
//     left_feedback += current_left_encoder;
//     if((left_feedback>turn_limit)&&(flag_i==1)){
//       i++;
//       flag_i=0;
//     }
//   }
//     // ROS_INFO_STREAM("counter= "<<"  " <<counter);

//  counter++;
// }



int main(int argc, char **argv) {

  ros::init(argc, argv, "gps_subscriber_cpp");

  ros::NodeHandle nh;
  
    ros::Subscriber encoder_data = nh.subscribe("encoder_data", 10, encodercallback);
  ros::Subscriber sub_action = nh.subscribe("gps_action", 10, actionCallback);
  ros::Subscriber sub_distance = nh.subscribe("gps_distance", 10, distanceCallback);
  ros::Subscriber sub = nh.subscribe("scan", 1000, lidarCallback);
  // ros::Subscriber joint_state = nh.subscribe("joint_states_from_arduino", 10, jointStateCallback);
  
  // ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::Publisher action_pub = nh.advertise<std_msgs::Int8>("/integer_topic", 10);
    
  while (ros::ok()) {

unsigned int microsecond = 10000;
usleep(15 * microsecond);
    geometry_msgs::Twist msg;
        std_msgs::Int8 action_msg;
    ///ROS_INFO("main is running...");
    // std::cout<<"length_action: "<<array_length_action<<std::endl;
    // std::cout<<"length_distance: "<<array_length_distance<<std::endl;
    ros::spinOnce(); // Check for new messages and call callbacks
    ros::Rate loop_rate(10); 
   
   if(data_recived==1){

   //for ( i = 0; i <= array_length_action ; )
    //{
    
      // ROS_INFO("Goal %d started ", i);
      

      // ROS_INFO("ddis %d",distance_data_array[i]);
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


    if(right_feedback<turn_limit)

   // while (right_feedback < 20)
          {
            ROS_INFO_STREAM(right_feedback);
             //ROS_INFO_STREAM(goal_action);
            msg.linear.x = 8;
            msg.linear.y = 0;
            msg.linear.z = 0;

            msg.angular.x = 0;
            msg.angular.y = 0;
            msg.angular.z = -1000;

            action_msg.data=4;
            action_pub.publish(action_msg);
            ROS_INFO_STREAM("go LEFT");
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
              //  pub.publish(msg);

          }
          else if((left_feedback>=turn_limit)&&(right_feedback>=turn_limit)&&(flag_turn==1)){
            flag_turn=0;
            goal_action="straight";
            ROS_INFO_STREAM("edit here");
          }
          if (left_feedback<turn_limit)
        /// while (left_feedback < 20)
          {
            ROS_INFO_STREAM(left_feedback);
             ROS_INFO_STREAM(goal_action);
            msg.linear.x = 15;
            msg.linear.y = 0;
            msg.linear.z = 0;

            msg.angular.x = 0;
            msg.angular.y = 0;
            msg.angular.z = 1000;

            action_msg.data=3;
            action_pub.publish(action_msg);
            ROS_INFO_STREAM("go RIGHT");



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
          //  pub.publish(msg);
          } 
                    else if((left_feedback>=turn_limit)&&(right_feedback>=turn_limit)&&(flag_turn==1)){
            flag_turn=0;
            goal_action="straight";
            ROS_INFO_STREAM("or here");
          }
          if ((feedback>0)&&(right_feedback>turn_limit) && (left_feedback>turn_limit))
    //while (feedback)
      {
        // ros::spinOnce();

        ROS_INFO_STREAM(feedback);
        if (stop_flag==0){
        msg.linear.x = 8;
        msg.linear.y = 0;
        msg.linear.z = 0;

        msg.angular.x = 0;
        msg.angular.y = 0;
        msg.angular.z = 0;

        action_msg.data=1;
        action_pub.publish(action_msg);
        ROS_INFO_STREAM("go STRAIGHT");

        
        }
        else{
  msg.linear.x = 0;
          msg.linear.y = 0;
          msg.linear.z = 0;

          msg.angular.x = 0;
          msg.angular.y = 0;
          msg.angular.z = 0;

            action_msg.data=5;
            action_pub.publish(action_msg);
            ROS_INFO_STREAM("STOP");
          
          
        }

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
      
          // pub.publish(msg);

      }   
        
        
          
             
    //}
          
    }
    if(feedback==0){
    if(data_recived==1)
    {
      ROS_INFO_STREAM("feedback = %d"<<feedback);
      // ROS_INFO_STREAM(feedback);
    ROS_INFO_STREAM("we are at first if");
    if(i<array_length_action){
    ROS_INFO_STREAM("we are at sec if");  
   // if(i>0){
    //   ROS_INFO_STREAM("we are at third if");
    // i++;} 
      goal_action = action_data_array[i];
      feedback = distance_data_array[i];//*1000;

      ROS_INFO_STREAM("we came back");
      ROS_INFO_STREAM(feedback);
      ROS_INFO_STREAM(goal_action);
            if (goal_action == "turn-right") 
      {
        ROS_INFO_STREAM("we are at third if");
        right_feedback = 0 ;
     flag_turn=1;
      }

      else if (goal_action == "turn-left")
      {
        left_feedback = 0 ;
         flag_turn=1;
      }
    flag_i=1;
    }
    else{
         std::string next_action = "none";
    data_recived=0;
    }

    }}
    loop_rate.sleep();
    // break;

  }
  return 0;
}