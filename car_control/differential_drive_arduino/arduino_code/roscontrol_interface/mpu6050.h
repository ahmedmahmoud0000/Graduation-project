#define USE_MPU6050_IMU
#define IMU_PUBLISH_RATE 70 //hz
//#include "lino_base_config.h"
#include "ros_node.h"

#include "Imu.h"

void publishIMU()
{
    //pass accelerometer data to imu object
    raw_imu_msg.linear_acceleration = readAccelerometer();

    //pass gyroscope data to imu object
    raw_imu_msg.angular_velocity = readGyroscope();

    //pass accelerometer data to imu object
    raw_imu_msg.magnetic_field = readMagnetometer();

    //publish raw_imu_msg
    raw_imu_pub.publish(&raw_imu_msg);
}
