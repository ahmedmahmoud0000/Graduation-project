#ifndef _ROS_SERVICE_McuSensData_h
#define _ROS_SERVICE_McuSensData_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace pura_execution
{

static const char MCUSENSDATA[] = "pura_execution/McuSensData";

  class McuSensDataRequest : public ros::Msg
  {
    public:
      typedef uint8_t _id_type;
      _id_type id;
      enum { ID_SENSOR_AIRQUALITY =  1 };

    McuSensDataRequest():
      id(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
     return offset;
    }

    const char * getType(){ return MCUSENSDATA; };
    const char * getMD5(){ return "ce438f64cde31e9a7eaffb2763b0092f"; };

  };

  class McuSensDataResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;
      typedef uint8_t _id_type;
      _id_type id;
      typedef uint8_t _data_type;
      _data_type data;
      typedef uint8_t _error_code_type;
      _error_code_type error_code;

    McuSensDataResponse():
      result(0),
      id(0),
      data(0),
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
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      *(outbuffer + offset + 0) = (this->data >> (8 * 0)) & 0xFF;
      offset += sizeof(this->data);
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
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
      this->data =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->data);
      this->error_code =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->error_code);
     return offset;
    }

    const char * getType(){ return MCUSENSDATA; };
    const char * getMD5(){ return "ea9ad58fc81f7efb9a902b747f7662ac"; };

  };

  class McuSensData {
    public:
    typedef McuSensDataRequest Request;
    typedef McuSensDataResponse Response;
  };

}
#endif
