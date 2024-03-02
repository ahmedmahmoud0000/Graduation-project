
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <robot_controller/McuData.h>
ros::NodeHandle  nh;

float linear_velocity;
float angular_velocity;

void VelmessageCb( const geometry_msgs::Twist& vel_msg) {
  linear_velocity = vel_msg.linear.x;
  angular_velocity = vel_msg.angular.z;
}


ros::Subscriber<geometry_msgs::Twist> VelocitySub("cmd_vel", VelmessageCb );

robot_controller::McuData feedback_msg;
ros::Publisher FeedbackPub("mcu_data", &feedback_msg);

void ROSsetup()
{
  nh.initNode();
  nh.advertise(FeedbackPub);
  nh.subscribe(VelocitySub);
}

void ROSloop(double RobotPose_x, double RobotPose_y, double RobotPose_theta, double RobotLinearVel, double RobotAngularVel)
{

  feedback_msg.RobotPose_x = RobotPose_x;
  feedback_msg.RobotPose_y = RobotPose_y;
  feedback_msg.RobotPose_theta = RobotPose_theta;
  feedback_msg.RobotLinearVel = RobotLinearVel;
  feedback_msg.RobotAngularVel = RobotAngularVel;

  FeedbackPub.publish( &feedback_msg );
  nh.spinOnce();
  //  delay(500);
}
