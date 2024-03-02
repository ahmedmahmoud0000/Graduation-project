#ifndef _ROS_arche_msg_Demography_array_h
#define _ROS_arche_msg_Demography_array_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "arche_msg/Demography.h"

namespace arche_msg
{

  class Demography_array : public ros::Msg
  {
    public:
      uint32_t demographies_length;
      typedef arche_msg::Demography _demographies_type;
      _demographies_type st_demographies;
      _demographies_type * demographies;

    Demography_array():
      demographies_length(0), demographies(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->demographies_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->demographies_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->demographies_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->demographies_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->demographies_length);
      for( uint32_t i = 0; i < demographies_length; i++){
      offset += this->demographies[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t demographies_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      demographies_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      demographies_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      demographies_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->demographies_length);
      if(demographies_lengthT > demographies_length)
        this->demographies = (arche_msg::Demography*)realloc(this->demographies, demographies_lengthT * sizeof(arche_msg::Demography));
      demographies_length = demographies_lengthT;
      for( uint32_t i = 0; i < demographies_length; i++){
      offset += this->st_demographies.deserialize(inbuffer + offset);
        memcpy( &(this->demographies[i]), &(this->st_demographies), sizeof(arche_msg::Demography));
      }
     return offset;
    }

    const char * getType(){ return "arche_msg/Demography_array"; };
    const char * getMD5(){ return "bb9d2056fbbe4dd8a496a2cd32aad3b8"; };

  };

}
#endif
