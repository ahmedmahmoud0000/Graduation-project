#ifndef _ROS_arche_msg_Pixel_h
#define _ROS_arche_msg_Pixel_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace arche_msg
{

  class Pixel : public ros::Msg
  {
    public:
      typedef int32_t _pixel_x_type;
      _pixel_x_type pixel_x;
      typedef int32_t _pixel_y_type;
      _pixel_y_type pixel_y;

    Pixel():
      pixel_x(0),
      pixel_y(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_pixel_x;
      u_pixel_x.real = this->pixel_x;
      *(outbuffer + offset + 0) = (u_pixel_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pixel_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pixel_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pixel_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pixel_x);
      union {
        int32_t real;
        uint32_t base;
      } u_pixel_y;
      u_pixel_y.real = this->pixel_y;
      *(outbuffer + offset + 0) = (u_pixel_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pixel_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pixel_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pixel_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pixel_y);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_pixel_x;
      u_pixel_x.base = 0;
      u_pixel_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pixel_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pixel_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pixel_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pixel_x = u_pixel_x.real;
      offset += sizeof(this->pixel_x);
      union {
        int32_t real;
        uint32_t base;
      } u_pixel_y;
      u_pixel_y.base = 0;
      u_pixel_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pixel_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pixel_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pixel_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pixel_y = u_pixel_y.real;
      offset += sizeof(this->pixel_y);
     return offset;
    }

    const char * getType(){ return "arche_msg/Pixel"; };
    const char * getMD5(){ return "4c8af6213d5d1bfed5439aa1baf4890b"; };

  };

}
#endif
