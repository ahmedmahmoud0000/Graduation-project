#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv) {

  ros::init(argc, argv, "velocity_publisher");

  // Create a ROS node handle
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
  double distance =0;
  double speed =5 ;
int flag =10;

  ros::Rate loop_rate(10); 

  while (ros::ok()) {
    geometry_msgs::Twist msg;
    double mov_time = distance/speed;
    if (flag>0)
    {

     msg.linear.x = speed;
     msg.linear.y = 0;
     msg.linear.z = 0;

     msg.angular.x = 0;
     msg.angular.y = 0;
     msg.angular.z = 0;
     flag--;
    }
    else {flag=0;

     msg.linear.x = 0;
     msg.linear.y = 0;
     msg.linear.z = 0;

     msg.angular.x = 0;
     msg.angular.y = 0;
     msg.angular.z = 0;
    }
    pub.publish(msg);

    ROS_INFO_STREAM("move for " << mov_time << "with speed =" << speed);

    loop_rate.sleep();
  }

  return 0;
}
