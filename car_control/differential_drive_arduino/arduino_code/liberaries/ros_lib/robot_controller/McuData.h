#ifndef _ROS_robot_controller_McuData_h
#define _ROS_robot_controller_McuData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robot_controller
{

  class McuData : public ros::Msg
  {
    public:
      typedef float _RobotPose_x_type;
      _RobotPose_x_type RobotPose_x;
      typedef float _RobotPose_y_type;
      _RobotPose_y_type RobotPose_y;
      typedef float _RobotPose_theta_type;
      _RobotPose_theta_type RobotPose_theta;
      typedef float _RobotLinearVel_type;
      _RobotLinearVel_type RobotLinearVel;
      typedef float _RobotAngularVel_type;
      _RobotAngularVel_type RobotAngularVel;
      typedef float _IMUOrientation_type;
      _IMUOrientation_type IMUOrientation;
      typedef float _IMUAngularVel_type;
      _IMUAngularVel_type IMUAngularVel;
      typedef float _IMULinearAcc_type;
      _IMULinearAcc_type IMULinearAcc;

    McuData():
      RobotPose_x(0),
      RobotPose_y(0),
      RobotPose_theta(0),
      RobotLinearVel(0),
      RobotAngularVel(0),
      IMUOrientation(0),
      IMUAngularVel(0),
      IMULinearAcc(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->RobotPose_x);
      offset += serializeAvrFloat64(outbuffer + offset, this->RobotPose_y);
      offset += serializeAvrFloat64(outbuffer + offset, this->RobotPose_theta);
      offset += serializeAvrFloat64(outbuffer + offset, this->RobotLinearVel);
      offset += serializeAvrFloat64(outbuffer + offset, this->RobotAngularVel);
      offset += serializeAvrFloat64(outbuffer + offset, this->IMUOrientation);
      offset += serializeAvrFloat64(outbuffer + offset, this->IMUAngularVel);
      offset += serializeAvrFloat64(outbuffer + offset, this->IMULinearAcc);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->RobotPose_x));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->RobotPose_y));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->RobotPose_theta));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->RobotLinearVel));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->RobotAngularVel));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->IMUOrientation));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->IMUAngularVel));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->IMULinearAcc));
     return offset;
    }

    const char * getType(){ return "robot_controller/McuData"; };
    const char * getMD5(){ return "707c69cb979d3f4bb2b95ee1ee531d99"; };

  };

}
#endif
