#ifndef _ROS_SERVICE_AddElement_h
#define _ROS_SERVICE_AddElement_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "virtual_costmap_layer/Form.h"

namespace virtual_costmap_layer
{

static const char ADDELEMENT[] = "virtual_costmap_layer/AddElement";

  class AddElementRequest : public ros::Msg
  {
    public:
      typedef virtual_costmap_layer::Form _form_type;
      _form_type form;

    AddElementRequest():
      form()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->form.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->form.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return ADDELEMENT; };
    const char * getMD5(){ return "c4d4e70c162e4371e2b09fd25bfd3f30"; };

  };

  class AddElementResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;
      typedef const char* _message_type;
      _message_type message;
      typedef const char* _uuid_type;
      _uuid_type uuid;

    AddElementResponse():
      success(0),
      message(""),
      uuid("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      uint32_t length_message = strlen(this->message);
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      uint32_t length_uuid = strlen(this->uuid);
      varToArr(outbuffer + offset, length_uuid);
      offset += 4;
      memcpy(outbuffer + offset, this->uuid, length_uuid);
      offset += length_uuid;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
      uint32_t length_message;
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
      uint32_t length_uuid;
      arrToVar(length_uuid, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_uuid; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_uuid-1]=0;
      this->uuid = (char *)(inbuffer + offset-1);
      offset += length_uuid;
     return offset;
    }

    const char * getType(){ return ADDELEMENT; };
    const char * getMD5(){ return "c31b7f64d3105bed5dfc74586f0e522d"; };

  };

  class AddElement {
    public:
    typedef AddElementRequest Request;
    typedef AddElementResponse Response;
  };

}
#endif
