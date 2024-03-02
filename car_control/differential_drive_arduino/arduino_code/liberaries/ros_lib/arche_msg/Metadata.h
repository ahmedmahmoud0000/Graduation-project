#ifndef _ROS_arche_msg_Metadata_h
#define _ROS_arche_msg_Metadata_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace arche_msg
{

  class Metadata : public ros::Msg
  {
    public:
      typedef const char* _Type_type;
      _Type_type Type;
      typedef float _Confidence_type;
      _Confidence_type Confidence;

    Metadata():
      Type(""),
      Confidence(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_Type = strlen(this->Type);
      varToArr(outbuffer + offset, length_Type);
      offset += 4;
      memcpy(outbuffer + offset, this->Type, length_Type);
      offset += length_Type;
      union {
        float real;
        uint32_t base;
      } u_Confidence;
      u_Confidence.real = this->Confidence;
      *(outbuffer + offset + 0) = (u_Confidence.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Confidence.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Confidence.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Confidence.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Confidence);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_Type;
      arrToVar(length_Type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_Type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_Type-1]=0;
      this->Type = (char *)(inbuffer + offset-1);
      offset += length_Type;
      union {
        float real;
        uint32_t base;
      } u_Confidence;
      u_Confidence.base = 0;
      u_Confidence.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Confidence.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Confidence.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Confidence.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Confidence = u_Confidence.real;
      offset += sizeof(this->Confidence);
     return offset;
    }

    const char * getType(){ return "arche_msg/Metadata"; };
    const char * getMD5(){ return "38a54dc2b9987a0cd506f675d7f0c5ff"; };

  };

}
#endif
