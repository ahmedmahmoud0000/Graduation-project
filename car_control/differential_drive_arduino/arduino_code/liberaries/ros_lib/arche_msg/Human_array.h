#ifndef _ROS_arche_msg_Human_array_h
#define _ROS_arche_msg_Human_array_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "arche_msg/Human.h"

namespace arche_msg
{

  class Human_array : public ros::Msg
  {
    public:
      typedef bool _human_detect_type;
      _human_detect_type human_detect;
      typedef int32_t _human_count_type;
      _human_count_type human_count;
      uint32_t pose_arr_length;
      typedef arche_msg::Human _pose_arr_type;
      _pose_arr_type st_pose_arr;
      _pose_arr_type * pose_arr;

    Human_array():
      human_detect(0),
      human_count(0),
      pose_arr_length(0), pose_arr(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_human_detect;
      u_human_detect.real = this->human_detect;
      *(outbuffer + offset + 0) = (u_human_detect.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->human_detect);
      union {
        int32_t real;
        uint32_t base;
      } u_human_count;
      u_human_count.real = this->human_count;
      *(outbuffer + offset + 0) = (u_human_count.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_human_count.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_human_count.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_human_count.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->human_count);
      *(outbuffer + offset + 0) = (this->pose_arr_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pose_arr_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pose_arr_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pose_arr_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pose_arr_length);
      for( uint32_t i = 0; i < pose_arr_length; i++){
      offset += this->pose_arr[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_human_detect;
      u_human_detect.base = 0;
      u_human_detect.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->human_detect = u_human_detect.real;
      offset += sizeof(this->human_detect);
      union {
        int32_t real;
        uint32_t base;
      } u_human_count;
      u_human_count.base = 0;
      u_human_count.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_human_count.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_human_count.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_human_count.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->human_count = u_human_count.real;
      offset += sizeof(this->human_count);
      uint32_t pose_arr_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      pose_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      pose_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      pose_arr_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->pose_arr_length);
      if(pose_arr_lengthT > pose_arr_length)
        this->pose_arr = (arche_msg::Human*)realloc(this->pose_arr, pose_arr_lengthT * sizeof(arche_msg::Human));
      pose_arr_length = pose_arr_lengthT;
      for( uint32_t i = 0; i < pose_arr_length; i++){
      offset += this->st_pose_arr.deserialize(inbuffer + offset);
        memcpy( &(this->pose_arr[i]), &(this->st_pose_arr), sizeof(arche_msg::Human));
      }
     return offset;
    }

    const char * getType(){ return "arche_msg/Human_array"; };
    const char * getMD5(){ return "88167c38de23677fc2b822cefa74cfe8"; };

  };

}
#endif
