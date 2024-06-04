#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <rospy_tutorials/Floats.h>
#include <sstream>


float STD_range_front,Half1_STD_range_front,Half2_STD_range_front,STD_range_behind,STD_range_right,STD_range_left,STD_avoid_right,STD_avoid_left,ahead = 1;
std_msgs::Float32MultiArray STD_ARRAY;


void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg)
{
  float sum1_range_front = 0;
  float sum2_range_front = 0;

  for (int i = 0; i < 5; i++) { //for (int i = 180; i < 540; i++) {

    if (isinf(scan_msg->ranges[i]))
    {
      sum1_range_front = sum1_range_front + 1.1;
    }
   else  {
   sum1_range_front = sum1_range_front + scan_msg->ranges[i];
   }
  }
  Half1_STD_range_front = sum1_range_front / 5;

  for (int i = 1143; i < 1148; i++) {//for (int i = 180; i < 540; i++) {
    if (isinf(scan_msg->ranges[i]))
    {
      sum2_range_front = sum2_range_front + 1.1;
    }
   else  {
   sum2_range_front = sum2_range_front + scan_msg->ranges[i];
   }
  }
  Half2_STD_range_front = sum2_range_front / 5;
  
  STD_range_front=(Half1_STD_range_front+Half2_STD_range_front)/2;
  STD_ARRAY.data[0]=STD_range_front;


  // if (STD_range_front > 100) {

  //   stop_flag = 0;
  // } else {
  //   stop_flag = 1;
  // }

  float sum_range_behind = 0;
  for (int i = 569; i < 579; i++) {
     if (isinf(scan_msg->ranges[i]))
    {
      sum_range_behind = sum_range_behind + 1.1;
    }
   else  {
    sum_range_behind = sum_range_behind + scan_msg->ranges[i];
  }}
  STD_range_behind = sum_range_behind / 10;
  STD_ARRAY.data[1]=STD_range_behind;

  float sum_range_right = 0;
  for (int i = 856; i < 866; i++) { //for (int i = 0; i < 180; i++) {

         if (isinf(scan_msg->ranges[i]))
    {
      sum_range_right = sum_range_right + 1.1;
    }
   else  {
    sum_range_right = sum_range_right + scan_msg->ranges[i];
  }
  }
  STD_range_right = sum_range_right / 10;
  STD_ARRAY.data[2]=STD_range_right;
  

  float sum_range_left = 0;
  for (int i = 282; i < 292; i++) {
             if (isinf(scan_msg->ranges[i]))
    {
      sum_range_left = sum_range_left + 1.1;
    }
   else  {
    sum_range_left = sum_range_left + scan_msg->ranges[i];
  }
  }
  STD_range_left = sum_range_left / 10;
  STD_ARRAY.data[3]=STD_range_left;


  float sum_avoid_right = 0;
  for (int i = 999; i < 1009; i++) {
    sum_avoid_right = sum_avoid_right + scan_msg->ranges[i];
  }
  STD_avoid_right = sum_avoid_right / 10;
  STD_ARRAY.data[4]=STD_avoid_right;

  float sum_avoid_left = 0;
  for (int i = 138; i < 148; i++) {
    sum_avoid_left = sum_avoid_left + scan_msg->ranges[i];
  }
  STD_avoid_left = sum_avoid_left / 10;
  STD_ARRAY.data[5]=STD_avoid_left;

  ROS_INFO_STREAM("STD_range_front: " << STD_range_front<<"  "<<"STD_range_behind: " << STD_range_behind<<"  "<<"STD_range_right: " << STD_range_right<<"  "<<"STD_range_left: " << STD_range_left);
  // ROS_INFO_STREAM(" STD_range_behind  : " << STD_range_behind);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "lidar_scan");

  ros::NodeHandle n;
  ros::Rate loop_rate(20);  

  ros::Publisher range_pub ;



  range_pub= n.advertise<std_msgs::Float32MultiArray>("lidar_data", 50);


  ros::Subscriber sub = n.subscribe("scan", 1000, chatterCallback);


 while (ros::ok()) {

    // lidar_msg.data=STD_ARRAY[] ;

    range_pub.publish(STD_ARRAY);
    ROS_INFO_STREAM("STD_ARRAY : "<<STD_ARRAY);
    
    
  ros::spinOnce();
  loop_rate.sleep();
 }
  return 0;
  
}