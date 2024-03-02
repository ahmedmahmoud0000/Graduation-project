#ifndef _ROS_SERVICE_McuCmd_h
#define _ROS_SERVICE_McuCmd_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace pura_execution
{

static const char MCUCMD[] = "pura_execution/McuCmd";

  class McuCmdRequest : public ros::Msg
  {
    public:
      typedef uint8_t _id_type;
      _id_type id;
      typedef uint8_t _data_type;
      _data_type data;
      enum { ID_FAN_1 =  1 };
      enum { ID_FAN_2 =  2 };

    McuCmdRequest():
      id(0),
      data(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      *(outbuffer + offset + 0) = (this->data >> (8 * 0)) & 0xFF;
      offset += sizeof(this->data);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
      this->data =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->data);
     return offset;
    }

    const char * getType(){ return MCUCMD; };
    const char * getMD5(){ return "79192a4c3cdd20ef57676b44784ce621"; };

  };

  class McuCmdResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;
      typedef uint8_t _error_code_type;
      _error_code_type error_code;

    McuCmdResponse():
      result(0),
      error_code(0)
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
      *(outbuffer + offset + 0) = (this->error_code >> (8 * 0)) & 0xFF;
      offset += sizeof(this->error_code);
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
      this->error_code =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->error_code);
     return offset;
    }

    const char * getType(){ return MCUCMD; };
    const char * getMD5(){ return "2b7b221388561ff574c25bb2c7cb1c0f"; };

  };

  class McuCmd {
    public:
    typedef McuCmdRequest Request;
    typedef McuCmdResponse Response;
  };

}
#endif
