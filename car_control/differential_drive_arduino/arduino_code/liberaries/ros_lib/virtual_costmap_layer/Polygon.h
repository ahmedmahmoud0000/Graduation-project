#ifndef _ROS_virtual_costmap_layer_Polygon_h
#define _ROS_virtual_costmap_layer_Polygon_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "virtual_costmap_layer/Ring.h"

namespace virtual_costmap_layer
{

  class Polygon : public ros::Msg
  {
    public:
      typedef virtual_costmap_layer::Ring _outer_type;
      _outer_type outer;
      uint32_t inners_length;
      typedef virtual_costmap_layer::Ring _inners_type;
      _inners_type st_inners;
      _inners_type * inners;

    Polygon():
      outer(),
      inners_length(0), inners(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->outer.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->inners_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->inners_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->inners_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->inners_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->inners_length);
      for( uint32_t i = 0; i < inners_length; i++){
      offset += this->inners[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->outer.deserialize(inbuffer + offset);
      uint32_t inners_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      inners_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      inners_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      inners_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->inners_length);
      if(inners_lengthT > inners_length)
        this->inners = (virtual_costmap_layer::Ring*)realloc(this->inners, inners_lengthT * sizeof(virtual_costmap_layer::Ring));
      inners_length = inners_lengthT;
      for( uint32_t i = 0; i < inners_length; i++){
      offset += this->st_inners.deserialize(inbuffer + offset);
        memcpy( &(this->inners[i]), &(this->st_inners), sizeof(virtual_costmap_layer::Ring));
      }
     return offset;
    }

    const char * getType(){ return "virtual_costmap_layer/Polygon"; };
    const char * getMD5(){ return "41f87f04c4bb75ebe736b4082170f60f"; };

  };

}
#endif
