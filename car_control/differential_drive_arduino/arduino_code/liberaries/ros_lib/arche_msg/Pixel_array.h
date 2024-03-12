#ifndef _ROS_arche_msg_Pixel_array_h
#define _ROS_arche_msg_Pixel_array_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "arche_msg/Pixel.h"

namespace arche_msg
{

  class Pixel_array : public ros::Msg
  {
    public:
      typedef int32_t _pixel_count_type;
      _pixel_count_type pixel_count;
      uint32_t pixel_arr_length;
      typedef arche_msg::Pixel _pixel_arr_type;
      _pixel_arr_type st_pixel_arr;
      _pixel_arr_type * pixel_arr;

    Pixel_array():
      pixel_count(0),
      pixel_arr_length(0), pixel_arr(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_pixel_count;
      u_pixel_count.real = this->pixel_count;
      *(outbuffer + offset + 0) = (u_pixel_count.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pixel_count.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pixel_count.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pixel_count.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pixel_count);
      *(outbuffer + offset + 0) = (this->pixel_arr_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pixel_arr_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pixel_arr_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pixel_arr_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pixel_arr_length);
      for( uint32_t i = 0; i < pixel_arr_length; i++){
      offset += this->pixel_arr[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_pixel_count;
      u_pixel_count.base = 0;
      u_pixel_count.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pixel_count.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pixel_count.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pixel_count.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pixel_count = u_pixel_count.real;
      offset += sizeof(this->pixel_count);
      uint32_t pixel_arr_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      pixel_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      pixel_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      pixel_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->pixel_arr_length);
      if(pixel_arr_lengthT > pixel_arr_length)
        this->pixel_arr = (arche_msg::Pixel*)realloc(this->pixel_arr, pixel_arr_lengthT * sizeof(arche_msg::Pixel));
      pixel_arr_length = pixel_arr_lengthT;
      for( uint32_t i = 0; i < pixel_arr_length; i++){
      offset += this->st_pixel_arr.deserialize(inbuffer + offset);
        memcpy( &(this->pixel_arr[i]), &(this->st_pixel_arr), sizeof(arche_msg::Pixel));
      }
     return offset;
    }

    const char * getType(){ return "arche_msg/Pixel_array"; };
    const char * getMD5(){ return "ab44fff896f088ae0d3c8616666b99a1"; };

  };

}
#endif
