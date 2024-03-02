#ifndef _ROS_arche_msg_Human_h
#define _ROS_arche_msg_Human_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point.h"

namespace arche_msg
{

  class Human : public ros::Msg
  {
    public:
      typedef geometry_msgs::Point _pose_type;
      _pose_type pose;

    Human():
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "arche_msg/Human"; };
    const char * getMD5(){ return "d562f95ca92089ed9ca118a23535a58f"; };

  };

}
#endif
