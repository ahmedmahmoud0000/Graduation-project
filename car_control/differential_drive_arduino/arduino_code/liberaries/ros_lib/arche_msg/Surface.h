#ifndef _ROS_arche_msg_Surface_h
#define _ROS_arche_msg_Surface_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"

namespace arche_msg
{

  class Surface : public ros::Msg
  {
    public:
      typedef geometry_msgs::Pose _pose_type;
      _pose_type pose;
      typedef const char* _info_type;
      _info_type info;

    Surface():
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

    const char * getType(){ return "arche_msg/Surface"; };
    const char * getMD5(){ return "7c4d1427872b26b29446e2720081d58f"; };

  };

}
#endif
