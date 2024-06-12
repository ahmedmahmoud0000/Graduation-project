#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32MultiArray.h>
#include <cmath>

// Global variable to hold the published data
std_msgs::Float32MultiArray std_array;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg) {
    // Initialize the data array with a fixed size (adjust size as needed)
    std_array.data.resize(6);

    float sum1_range_front = 0;
    float sum2_range_front = 0;

    // Process the front half of the scan data
    for (int i = 0; i < 5; ++i) {
        if (std::isinf(scan_msg->ranges[i])) {
            sum1_range_front += 1.1;
        } else {
            sum1_range_front += scan_msg->ranges[i];
        }
    }
    float half1_std_range_front = sum1_range_front / 5;

    for (int i = 1143; i < 1148; ++i) {
        if (std::isinf(scan_msg->ranges[i])) {
            sum2_range_front += 1.1;
        } else {
            sum2_range_front += scan_msg->ranges[i];
        }
    }
    float half2_std_range_front = sum2_range_front / 5;

    float std_range_front = (half1_std_range_front + half2_std_range_front) / 2;
    std_array.data[0] = std_range_front*100;

    float sum_range_behind = 0;
    for (int i = 569; i < 579; ++i) {
        if (std::isinf(scan_msg->ranges[i])) {
            sum_range_behind += 1.1;
        } else {
            sum_range_behind += scan_msg->ranges[i];
        }
    }
    float std_range_behind = sum_range_behind / 10;
    std_array.data[1] = std_range_behind*100;

    float sum_range_right = 0;
    for (int i = 856; i < 866; ++i) {
        if (std::isinf(scan_msg->ranges[i])) {
            sum_range_right += 1.1;
        } else {
            sum_range_right += scan_msg->ranges[i];
        }
    }
    float std_range_right = sum_range_right / 10;
    std_array.data[2] = std_range_right*100;

    float sum_range_left = 0;
    for (int i = 282; i < 292; ++i) {
        if (std::isinf(scan_msg->ranges[i])) {
            sum_range_left += 1.1;
        } else {
            sum_range_left += scan_msg->ranges[i];
        }
    }
    float std_range_left = sum_range_left / 10;
    std_array.data[3] = std_range_left*100;

    float sum_avoid_right = 0;
    for (int i = 999; i < 1009; ++i) {
        if (std::isinf(scan_msg->ranges[i])) {
            sum_avoid_right += 1.1;
        } else {
            sum_avoid_right += scan_msg->ranges[i];
        }
    }
    float std_avoid_right = sum_avoid_right / 10;
    std_array.data[4] = std_avoid_right*100;

    float sum_avoid_left = 0;
    for (int i = 138; i < 148; ++i) {
        if (std::isinf(scan_msg->ranges[i])) {
            sum_avoid_left += 1.1;
        } else {
            sum_avoid_left += scan_msg->ranges[i];
        }
    }
    float std_avoid_left = sum_avoid_left / 10;
    std_array.data[5] = std_avoid_left*100;

    ROS_INFO_STREAM("STD_array: ["
                    << std_array.data[0] << ", "
                    << std_array.data[1] << ", "
                    << std_array.data[2] << ", "
                    << std_array.data[3] << ", "
                    << std_array.data[4] << ", "
                    << std_array.data[5] << "]");
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "lidar_node");
    ros::NodeHandle n;

    ros::Publisher range_pub = n.advertise<std_msgs::Float32MultiArray>("lidar_data", 50);
    ros::Subscriber sub = n.subscribe("scan", 1000, scanCallback);

    ros::Rate loop_rate(20);
    while (ros::ok()) {
        range_pub.publish(std_array);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
