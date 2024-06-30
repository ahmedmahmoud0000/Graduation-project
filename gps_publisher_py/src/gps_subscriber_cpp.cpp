#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Int16.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <vector>
#include <geometry_msgs/Twist.h>
#include <rospy_tutorials/Floats.h>
#include <std_msgs/ByteMultiArray.h>
#include <sstream>
#include <std_msgs/Float32MultiArray.h>
#include<math.h>


rospy_tutorials::Floats joint_state;

std::string action;
std::string goal_action;
std::string next_action;
std::vector<std::string> action_data_array_vect;
std::vector<std::int32_t> distance_data_array_vect;
std::string action_data_array[10];
std::int32_t distance_data_array[10];
std_msgs::Int16 action_msg;
std::string recieved_encoder_data;

int counter = 0;
int array_length_action = 0,array_length_distance = 0,data_recived = 0,flag_i = 0,flag_turn = 0,stop_flag = 0;
uint8_t buf[2] = { 0, 0 },send_data=0,stop=0;
float STD_range_front,Half1_STD_range_front,Half2_STD_range_front,STD_range_behind,STD_range_right,STD_range_left,STD_avoid_right,STD_avoid_left;
long feedback = 0;
int turn_limit = 1000,ahead = 10;
double right_feedback = turn_limit + 1;
double left_feedback = turn_limit + 1;
double right_avoid_feedback = turn_limit + 1;
double left_avoid_feedback = turn_limit + 1;
int i = 0,avoid=0;
int speed=90,dir=1;




void encodercallback(const std_msgs::String& encoder_msg) {

  recieved_encoder_data = encoder_msg.data;

  // std::istringstream iss(recieved_encoder_data);
  int Left_Encoder, Right_Encoder;

  // if (iss >> Left_Encoder >> Right_Encoder) {

  //   if (Right_Encoder < 0) {
  //     Right_Encoder *= -1;
  //   }

  //   if (Left_Encoder < 0) {
  //     Left_Encoder *= -1;
  //   }
  // }
  int positions[3] = {-1, -1, -1}; // Array to store the positions
  int count = 0; // Counter for the number of found character
    for (size_t i = 0; i < recieved_encoder_data.length() && count < 3; ++i) {
          if (recieved_encoder_data[i] == ' ') {
            positions[0] = i;
            count++;
        } else if (recieved_encoder_data[i] == '\r') {
            positions[1] = i;
            count++;
        } else if (recieved_encoder_data[i] == '\n') {
            positions[2] = i;
            count++;
        }
    }
      if ((count == 3)) {
       if(positions[0]!=0){
        std::string left_encoder_str=recieved_encoder_data.substr(0,positions[0]);
        std::string right_encoder_str=recieved_encoder_data.substr(positions[0]+1,positions[1]);
       
       Left_Encoder=stoi(left_encoder_str);
       Right_Encoder=stoi(right_encoder_str);
      //  ROS_INFO_STREAM("left encoder="<<Left_Encoder);
      //  ROS_INFO_STREAM("right encoder="<<Right_Encoder);
        // ROS_INFO_STREAM("Space found at position " << positions[0]);
        // ROS_INFO_STREAM("Carriage return found at position " << positions[1]) ;
        // ROS_INFO_STREAM("Line feed found at position " << positions[2]);
    } }else {
      Left_Encoder=0;
      Right_Encoder=0;
        // ROS_INFO_STREAM("Not all three characters were found");
    }

  ROS_INFO_STREAM(recieved_encoder_data.length());
  std::cout << "Left Encoder: " << Left_Encoder << std::endl;
  std::cout << "Right Encoder: " << Right_Encoder << std::endl;
    // if (iss >> Left_Encoder >> Right_Encoder) {

    if (Right_Encoder < 0) {
      Right_Encoder *= -1;
    }

    if (Left_Encoder < 0) {
      Left_Encoder *= -1;
    }
  
  
  // Right_Encoder *= -1;
  // Left_Encoder *= 1;
   if ( Left_Encoder< 20 && Right_Encoder<20 )
  {
  if (goal_action == "straight") {
    if (feedback >= Right_Encoder) {
      feedback -= Right_Encoder;
    } else {
      feedback = 0;
      // ROS_INFO("nnjn");
      // ROS_INFO_STREAM(i);
    }
    if ((feedback == 0) && (flag_i == 1)) {
      i++;
      flag_i = 0;
    }
  } else if (goal_action == "turn-right") {

    right_feedback += Right_Encoder;
    if ((right_feedback > turn_limit) && (flag_i == 1)) {
      i++;
      flag_i = 0;
    }
  } else if (goal_action == "turn-left") {
    left_feedback += Left_Encoder;
    if ((left_feedback > turn_limit) && (flag_i == 1)) {
      i++;
      flag_i = 0;
    }
  }
  
  else if (goal_action == "avoid_right") {
    right_avoid_feedback += Right_Encoder;}
	
  else if (goal_action == "avoid_left") {
  left_avoid_feedback += Left_Encoder;  }

  counter++;
}
}

void actionCallback(const std_msgs::String::ConstPtr& msg) {

  std::string action_data_str(msg->data.c_str());
  if (action_data_str != "done") {
    action_data_array[array_length_action] = action_data_str;
    array_length_action++;
  } else {
    data_recived = 1;
    ROS_INFO_STREAM("done");
  }
}

void distanceCallback(const std_msgs::Int32::ConstPtr& msg) {
  std::int32_t distance_data_int(msg->data);
  distance_data_array[array_length_distance] = distance_data_int;
  array_length_distance++;
}

void lidarCallback(const std_msgs::Float32MultiArray::ConstPtr& msg) {

    ROS_INFO_STREAM("Received lidar data: ["
                    "front "<< msg->data[0] << ", "
                    "behind"<< msg->data[1] << ", "
                    "right"<< msg->data[2] << ", "
                    "left"<< msg->data[3] << ", "
                    << msg->data[4] << ", "
                    << msg->data[5] << "]");
    STD_range_front=msg->data[0];
    STD_range_behind=msg->data[1];
    STD_range_right=msg->data[2];
    STD_range_left=msg->data[3];
    STD_avoid_right=msg->data[4];
    STD_avoid_left=msg->data[5];

}

void cameracallback(const std_msgs::Int8::ConstPtr msg)
{
  int data=msg->data;
  std::string str = std::to_string(data);
ROS_INFO_STREAM("camera_reciever : "<<str);
if (str=="1")
{
ROS_INFO_STREAM("camera_reciever : GREEN LIGHT ");
dir=1;
send_data=1;
}else if (str=="2")
{
ROS_INFO_STREAM("camera_reciever : RED LIGHT  ");
dir=5;
send_data=1;
}else if (str=="3")
{
ROS_INFO_STREAM("camera_reciever : SPEED 20 ");
speed=20;
send_data=1;
}else if (str=="4")
{
ROS_INFO_STREAM("camera_reciever : SPEED 40 ");
speed=40;
send_data=1;
}else if (str=="5")
{
ROS_INFO_STREAM("camera_reciever : SPEED 60");
speed=60;
send_data=1;
}else if (str=="6")
{
ROS_INFO_STREAM("camera_reciever : STOP ");

}
}

// void avoid_left(ros::Publisher action_pub) {
// left_avoid_feedback=0;
// 	goal_action="avoid_left";
//   uint16_t masg=0;
//   ROS_INFO_STREAM("left_avoid_feedback: " << left_avoid_feedback);
//         buf[1] = 4;
//         buf[0] = 125;
//         masg = buf[0] | buf[1] << 8;
//         action_msg.data = masg;
//         action_pub.publish(action_msg);
// while (left_avoid_feedback < turn_limit)
//       {
        
//         ROS_INFO_STREAM("Turn LEFT");
//       }
// 	  buf[1] = 1;
//         buf[0] = 125;
//        masg = buf[0] | buf[1] << 8;
//         action_msg.data = masg;
//         action_pub.publish(action_msg);
// 		while(STD_range_right<1){
// 			  buf[1] = 1;
//         buf[0] = 125;
//         masg = buf[0] | buf[1] << 8;
//         action_msg.data = masg;
//         //action_pub.publish(action_msg);
// 		}
// 		right_avoid_feedback=0;
// 		goal_action="avoid_right";
//      ROS_INFO_STREAM("right_avoid_feedback: " << right_avoid_feedback);
//         ROS_INFO_STREAM(goal_action);
//         buf[1] = 3;
//         buf[0] = 150;
//        masg = buf[0] | buf[1] << 8;
//         action_msg.data = masg;
//         action_pub.publish(action_msg);
// 	      while (right_avoid_feedback < turn_limit)
//       {
       
//         ROS_INFO_STREAM("Turn right");
//       }
//       dir = 5;
// 	  buf[1] = 1;
//         buf[0] = 150;
//         masg = buf[0] | buf[1] << 8;
//         action_msg.data = masg;
//         action_pub.publish(action_msg);
// 	  goal_action = "straight";
// }

// void avoid_right(ros::Publisher action_pub) {
  
// 	right_avoid_feedback=0;
// 	goal_action="avoid_right";
//   uint16_t masg=0;
//   ROS_INFO_STREAM("right_avoid_feedback: " << right_avoid_feedback);
//   dir = 3;
//         buf[1] = 3;
//         buf[0] = 125;
//         masg = buf[0] | buf[1] << 8;
//         action_msg.data = masg;
//         action_pub.publish(action_msg);
// while (right_avoid_feedback < turn_limit)
//       {
//         ROS_INFO_STREAM("Turn RIGHT");
//       }
// 	  buf[1] = 1;
//         buf[0] = 125;
//         masg = buf[0] | buf[1] << 8;
//         action_msg.data = masg;
//         action_pub.publish(action_msg);
// 		while(STD_range_left<1){
// 			  buf[1] = 1;
//         buf[0] = 125;
//         masg = buf[0] | buf[1] << 8;
//         action_msg.data = masg;
//         //action_pub.publish(action_msg);
// 		}
// 		left_avoid_feedback=0;
// 		goal_action="avoid_left";
//      ROS_INFO_STREAM("left_avoid_feedback: " << left_avoid_feedback);
//         ROS_INFO_STREAM(goal_action);
//         dir = 4;
//         buf[1] = 4;
//         buf[0] = 150;
//         masg = buf[0] | buf[1] << 8;
//         action_msg.data = masg;
//         action_pub.publish(action_msg);
// 	      while (left_avoid_feedback < turn_limit)
//       {
//         ROS_INFO_STREAM("Turn LEFT");
//       }
//       dir = 1;
// 	  buf[1] = 1;
//         buf[0] = 150;
//         masg = buf[0] | buf[1] << 8;
//         action_msg.data = masg;
//         action_pub.publish(action_msg);
// 	  goal_action = "straight";
// }
void send_serial(uint8_t buf[2],ros::Publisher action_pub){
  //buf[1] = 3;
        //buf[0] = 125;
        uint16_t masg = buf[0] | buf[1] << 8;
        action_msg.data = masg;
        action_pub.publish(action_msg);
}
void avoid_obstacle(ros::Publisher& action_pub) {
    if (STD_range_front < 50) {
        // Determine the direction to turn
        if (STD_range_right > STD_range_left) {
            right_avoid_feedback = 0;
            goal_action = "avoid_right";
            buf[1] = 3; // Command to turn right
            buf[0] = 125;
            send_serial(buf, action_pub);

            while (right_avoid_feedback < turn_limit) {
                ros::spinOnce();
                ROS_INFO_STREAM("Turning right to avoid obstacle");
            }

            // Move forward until left range is greater than 200
            buf[1] = 1; // Command to move forward
            buf[0] = 125;
            send_serial(buf, action_pub);
           

            while (STD_range_left < 200) {
                ros::spinOnce();
            }

            // Turn back to the left
            left_avoid_feedback = 0;
            goal_action = "avoid_left";
            buf[1] = 4; // Command to turn left
            buf[0] = 125;
            send_serial(buf, action_pub);

            while (left_avoid_feedback < turn_limit) {
                ros::spinOnce();
                ROS_INFO_STREAM("Turning left to resume path");
            }
            // Move forward until left range is greater than 200
            buf[1] = 1; // Command to move forward
            buf[0] = 125;
            send_serial(buf, action_pub);
			 goal_action="straight";
        } else {
            left_avoid_feedback = 0;
            goal_action = "avoid_left";
            buf[1] = 4; // Command to turn left
            buf[0] = 125;
            send_serial(buf, action_pub);

            while (left_avoid_feedback < turn_limit) {
                ros::spinOnce();
                ROS_INFO_STREAM("Turning left to avoid obstacle");
            }

            // Move forward until right range is greater than 200
            buf[1] = 1; // Command to move forward
            buf[0] = 125;
            send_serial(buf, action_pub);

            while (STD_range_right < 200) {
                ros::spinOnce();
            }

            // Turn back to the right
            right_avoid_feedback = 0;
            goal_action = "avoid_right";
            buf[1] = 3; // Command to turn right
            buf[0] = 125;
            send_serial(buf, action_pub);

            while (right_avoid_feedback < turn_limit) {
                ros::spinOnce();
                ROS_INFO_STREAM("Turning right to resume path");
            }
             buf[1] = 1; // Command to move forward
            buf[0] = 125;
            send_serial(buf, action_pub);
			 goal_action="straight";
        }
    }
}




int main(int argc, char** argv) {

  ros::init(argc, argv, "gps_subscriber_cpp");
  
  ros::NodeHandle nh;

  ros::Subscriber encoder_data = nh.subscribe("encoder_data", 10, encodercallback);
  ros::Subscriber sub_action = nh.subscribe("gps_action", 10, actionCallback);
  ros::Subscriber sub_distance = nh.subscribe("gps_distance", 10, distanceCallback);
  ros::Subscriber camera_sub = nh.subscribe("camera_data", 1000, cameracallback);
  ros::Subscriber sub = nh.subscribe("lidar_data", 1000, lidarCallback);
  ros::Publisher action_pub = nh.advertise<std_msgs::Int16>("/integer_topic", 10);



  while (ros::ok()) {

    unsigned int microsecond = 10000;
    usleep(15 * microsecond);
    

    ros::spinOnce();  
    ros::Rate loop_rate(10);

if((send_data==1)&&(stop==1)){
            ROS_INFO_STREAM("Goal finished");
          send_serial(buf,action_pub);
          ROS_INFO_STREAM("Goal finished");
          send_data=0;
          stop=0;}

    if (data_recived == 1) {
      if (i <= array_length_action) {
        int d = i;
        d++;
        std::string next_action = action_data_array[d];
      } else {
	  continue;}
	  // STD_range_left
	  // STD_range_front
	  
	  // STD_range_right

// int buf_float = STD_range_front * 10 ;
// ROS_INFO_STREAM(buf_float);
// ROS_INFO_STREAM(avoid);
// 	   if ((buf_float<ahead)&&(avoid==0)){//)&&(avoid==0)
      
//       ROS_INFO_STREAM("Start avoidance ");
// 	  goal_action="avoid";
// 	  if (STD_avoid_right > STD_avoid_left){
//       ROS_INFO_STREAM("avoidance right ");
//       right_avoid_feedback=0;
// 	goal_action="avoid_right";
//   flag_right=1;
// 	buf[1] = 3;
//         buf[0] = 125;
//           send_serial(buf,action_pub);
//           }
// 	  else{
//       		left_avoid_feedback=0;
// 		goal_action="avoid_left";
//     flag_left=1;
// 	buf[1] = 4;
//         buf[0] = 125;
//           send_serial(buf,action_pub);
//           }
//      }

// if((right_avoid_feedback >= turn_limit)&&(left_avoid_feedback >= turn_limit)&&(flag_right==1)){
//   	buf[1] = 1;
//         buf[0] = 125;
//           send_serial(buf,action_pub);
//           flag_right+=1;
// } 

// if((left_avoid_feedback >= turn_limit)&&(right_avoid_feedback >= turn_limit)&&(flag_left==1)){
//   	buf[1] = 1;
//         buf[0] = 125;
//           send_serial(buf,action_pub);
//           flag_left+=1;
// } 
// int buf_left = STD_range_left *10;
// if((flag_right==2)&&(buf_left>20)){

//         		left_avoid_feedback=0;
// 		goal_action="avoid_left";
// 	buf[1] = 4;
//         buf[0] = 125;
//           send_serial(buf,action_pub);
//           flag_left=1;
//           flag_right=0;
// }

// int buf_right = STD_range_right *10;
// if((flag_left==2)&&(buf_right>2)){

//         		right_avoid_feedback=0;
// 		goal_action="avoid_right";
// 	buf[1] = 3;
//         buf[0] = 125;
//           send_serial(buf,action_pub);
//           flag_right=1;
// }

// if(avoid==4){
//   avoid=0;
//   	goal_action="straight";
// 	buf[1] = 1;
//         buf[0] = 125;
//           send_serial(buf,action_pub);
// }
avoid_obstacle(action_pub);
if(send_data==1){
  buf[1] = dir;
          buf[0] = speed;
          send_serial(buf,action_pub);
          // send_data=0;
          }

if ((feedback <15000)&&(next_action=="turn-right")){
  ROS_INFO_STREAM("feedback: less and right" << feedback);
int buf_right = STD_range_right *10;
if (buf_right>20){
  feedback=0;
  i++;
}
}

if ((feedback <15000)&&(next_action=="turn-left")){
  ROS_INFO_STREAM("feedback: less and left" << feedback);
int buf_left = STD_range_left *10;
if (buf_left>20){
  feedback=0;
  i++;
}
}

      if (right_feedback < turn_limit)
      {
        ROS_INFO_STREAM("Right_feedback: " << right_feedback);
        dir = 3;
        buf[1] = 3;
        buf[0] = speed;
        if(send_data==1){
          send_serial(buf,action_pub);
          send_data=0;}
        // uint16_t masg = buf[0] | buf[1] << 8;
        // action_msg.data = masg;
        // action_pub.publish(action_msg);
        ROS_INFO_STREAM("Turn RIGHT");
      }
	  else if ((left_feedback >= turn_limit) && (right_feedback >= turn_limit) && (flag_turn == 1)) {
        flag_turn = 0;		
        goal_action = "straight";
        send_data=1;
        ROS_INFO_STREAM("edit here");
      }
      if (left_feedback < turn_limit)
      {
        ROS_INFO_STREAM("Left_Feedback: " << left_feedback);
        ROS_INFO_STREAM(goal_action);
        dir = 4;
        buf[1] = 4;
        buf[0] = speed;
        if(send_data==1){
          send_serial(buf,action_pub);
          send_data=0;}
        // uint16_t masg = buf[0] | buf[1] << 8;
        // action_msg.data = masg;
        // action_pub.publish(action_msg);
        ROS_INFO_STREAM("Turn LEFT");
      } else if ((left_feedback >= turn_limit) && (right_feedback >= turn_limit) && (flag_turn == 1)) {
        flag_turn = 0;
        goal_action = "straight";
        send_data=1;
        ROS_INFO_STREAM("or here");
      }
      if ((feedback > 0) && (right_feedback > turn_limit) && (left_feedback > turn_limit)) {
        ROS_INFO_STREAM(feedback);
        // if (stop_flag == 0) {
          dir = 1;
          buf[1] = 1;
          buf[0] = speed;
          if(send_data==1){
          send_serial(buf,action_pub);
          send_data=0;}
          // uint16_t masg = buf[0] | buf[1] << 8;
          // action_msg.data = masg;
          // action_pub.publish(action_msg);
          ROS_INFO_STREAM("Go STRAIGHT");
        } 
        // else {
        //   buf[1] = 5;
        //   buf[0] = 0;
        //   uint16_t masg = buf[0] | buf[1] << 8;
        //   action_msg.data = masg;
        //   action_pub.publish(action_msg);
        //   ROS_INFO_STREAM("STOP");
        // }
      // }
    }
    if (feedback == 0) {
      if (data_recived == 1) {
        ROS_INFO_STREAM("feedback = " << feedback);
        if (i < array_length_action) {
          goal_action = action_data_array[i];
          if (goal_action!="done")
          {
          next_action= action_data_array[i+1];
          ROS_INFO_STREAM("NEXT_ACTOIN = "<<next_action);
          }
          send_data=1;
          feedback = distance_data_array[i];  //*1000;
          ROS_INFO_STREAM("Goal Number " << i);
          ROS_INFO_STREAM("Action : " << goal_action);
          ROS_INFO_STREAM("Remain Distance = " << feedback);
          if (goal_action == "turn-right") {
            ROS_INFO_STREAM("Action : " << goal_action);
            right_feedback = 0;
            flag_turn = 1;
          }
          else if (goal_action == "turn-left") {
            ROS_INFO_STREAM("Action : " << goal_action);
            left_feedback = 0;
            flag_turn = 1;
          }
          flag_i = 1;
        } else {
          send_data=1;
          std::string next_action = "none";
          data_recived = 0;
          dir = 5;
          buf[1] = 5;
          buf[0] = speed;
          stop=1;
          // uint16_t masg = buf[0] | buf[1] << 8;
          // action_msg.data = masg;
          // action_pub.publish(action_msg);
          //ROS_INFO_STREAM("Goal finished");
          //break;
        }
      }
    }
    loop_rate.sleep();
  }
  return 0;
}