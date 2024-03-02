#ifndef _ROS_SERVICE_DemographyDetecter_h
#define _ROS_SERVICE_DemographyDetecter_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace arche_msg
{

static const char DEMOGRAPHYDETECTER[] = "arche_msg/DemographyDetecter";

  class DemographyDetecterRequest : public ros::Msg
  {
    public:
      typedef bool _flag_type;
      _flag_type flag;

    DemographyDetecterRequest():
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

    const char * getType(){ return DEMOGRAPHYDETECTER; };
    const char * getMD5(){ return "24842bc754e0f5cc982338eca1269251"; };

  };

  class DemographyDetecterResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;

    DemographyDetecterResponse():
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

    const char * getType(){ return DEMOGRAPHYDETECTER; };
    const char * getMD5(){ return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class DemographyDetecter {
    public:
    typedef DemographyDetecterRequest Request;
    typedef DemographyDetecterResponse Response;
  };

}
#endif
