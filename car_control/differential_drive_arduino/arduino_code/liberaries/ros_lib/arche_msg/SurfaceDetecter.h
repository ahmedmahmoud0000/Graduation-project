#ifndef _ROS_SERVICE_SurfaceDetecter_h
#define _ROS_SERVICE_SurfaceDetecter_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"

namespace arche_msg
{

static const char SURFACEDETECTER[] = "arche_msg/SurfaceDetecter";

  class SurfaceDetecterRequest : public ros::Msg
  {
    public:
      typedef bool _flag_type;
      _flag_type flag;

    SurfaceDetecterRequest():
      flag(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_flag;
      u_flag.real = this->flag;
      *(outbuffer + offset + 0) = (u_flag.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->flag);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_flag;
      u_flag.base = 0;
      u_flag.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->flag = u_flag.real;
      offset += sizeof(this->flag);
     return offset;
    }

    const char * getType(){ return SURFACEDETECTER; };
    const char * getMD5(){ return "24842bc754e0f5cc982338eca1269251"; };

  };

  class SurfaceDetecterResponse : public ros::Msg
  {
    public:
      typedef geometry_msgs::Pose _pose_type;
      _pose_type pose;
      typedef const char* _info_type;
      _info_type info;

    SurfaceDetecterResponse():
      pose(),
      info("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pose.serialize(outbuffer + offset);
      uint32_t length_info = strlen(this->info);
      varToArr(outbuffer + offset, length_info);
      offset += 4;
      memcpy(outbuffer + offset, this->info, length_info);
      offset += length_info;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
      uint32_t length_info;
      arrToVar(length_info, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_info; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_info-1]=0;
      this->info = (char *)(inbuffer + offset-1);
      offset += length_info;
     return offset;
    }

    const char * getType(){ return SURFACEDETECTER; };
    const char * getMD5(){ return "7c4d1427872b26b29446e2720081d58f"; };

  };

  class SurfaceDetecter {
    public:
    typedef SurfaceDetecterRequest Request;
    typedef SurfaceDetecterResponse Response;
  };

}
#endif
