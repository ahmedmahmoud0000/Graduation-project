#ifndef _ROS_mcu_communication_McuEncoder_h
#define _ROS_mcu_communication_McuEncoder_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace mcu_communication
{

  class McuEncoder : public ros::Msg
  {
    public:
      typedef float _rpm_left_type;
      _rpm_left_type rpm_left;
      typedef float _rpm_right_type;
      _rpm_right_type rpm_right;

    McuEncoder():
      rpm_left(0),
      rpm_right(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_rpm_left;
      u_rpm_left.real = this->rpm_left;
      *(outbuffer + offset + 0) = (u_rpm_left.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rpm_left.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rpm_left.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rpm_left.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rpm_left);
      union {
        float real;
        uint32_t base;
      } u_rpm_right;
      u_rpm_right.real = this->rpm_right;
      *(outbuffer + offset + 0) = (u_rpm_right.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rpm_right.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_rpm_right.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_rpm_right.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rpm_right);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_rpm_left;
      u_rpm_left.base = 0;
      u_rpm_left.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rpm_left.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rpm_left.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rpm_left.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rpm_left = u_rpm_left.real;
      offset += sizeof(this->rpm_left);
      union {
        float real;
        uint32_t base;
      } u_rpm_right;
      u_rpm_right.base = 0;
      u_rpm_right.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rpm_right.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_rpm_right.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_rpm_right.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->rpm_right = u_rpm_right.real;
      offset += sizeof(this->rpm_right);
     return offset;
    }

    const char * getType(){ return "mcu_communication/McuEncoder"; };
    const char * getMD5(){ return "811f89cd5e54718d6b2167dcea919c32"; };

  };

}
#endif
