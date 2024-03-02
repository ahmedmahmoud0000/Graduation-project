#ifndef _ROS_pura_execution_Human_h
#define _ROS_pura_execution_Human_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"

namespace pura_execution
{

  class Human : public ros::Msg
  {
    public:
      typedef const char* _human_detect_type;
      _human_detect_type human_detect;
      typedef int32_t _human_count_type;
      _human_count_type human_count;
      typedef geometry_msgs::Pose _pose_type;
      _pose_type pose;

    Human():
      human_detect(""),
      human_count(0),
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_human_detect = strlen(this->human_detect);
      varToArr(outbuffer + offset, length_human_detect);
      offset += 4;
      memcpy(outbuffer + offset, this->human_detect, length_human_detect);
      offset += length_human_detect;
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
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_human_detect;
      arrToVar(length_human_detect, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_human_detect; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_human_detect-1]=0;
      this->human_detect = (char *)(inbuffer + offset-1);
      offset += length_human_detect;
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
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "pura_execution/Human"; };
    const char * getMD5(){ return "cf4ddcee0278e09e0453382f1b239c60"; };

  };

}
#endif
