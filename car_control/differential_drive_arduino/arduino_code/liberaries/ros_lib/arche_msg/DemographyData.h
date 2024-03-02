#ifndef _ROS_SERVICE_DemographyData_h
#define _ROS_SERVICE_DemographyData_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "arche_msg/Demography.h"

namespace arche_msg
{

static const char DEMOGRAPHYDATA[] = "arche_msg/DemographyData";

  class DemographyDataRequest : public ros::Msg
  {
    public:
      uint32_t demographies_length;
      typedef arche_msg::Demography _demographies_type;
      _demographies_type st_demographies;
      _demographies_type * demographies;

    DemographyDataRequest():
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

    const char * getType(){ return DEMOGRAPHYDATA; };
    const char * getMD5(){ return "bb9d2056fbbe4dd8a496a2cd32aad3b8"; };

  };

  class DemographyDataResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;

    DemographyDataResponse():
      result(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.real = this->result;
      *(outbuffer + offset + 0) = (u_result.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.base = 0;
      u_result.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->result = u_result.real;
      offset += sizeof(this->result);
     return offset;
    }

    const char * getType(){ return DEMOGRAPHYDATA; };
    const char * getMD5(){ return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class DemographyData {
    public:
    typedef DemographyDataRequest Request;
    typedef DemographyDataResponse Response;
  };

}
#endif
