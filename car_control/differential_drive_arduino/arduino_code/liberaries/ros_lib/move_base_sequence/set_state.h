#ifndef _ROS_SERVICE_set_state_h
#define _ROS_SERVICE_set_state_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace move_base_sequence
{

static const char SET_STATE[] = "move_base_sequence/set_state";

  class set_stateRequest : public ros::Msg
  {
    public:
      typedef bool _state_type;
      _state_type state;

    set_stateRequest():
      state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_state;
      u_state.real = this->state;
      *(outbuffer + offset + 0) = (u_state.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_state;
      u_state.base = 0;
      u_state.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->state = u_state.real;
      offset += sizeof(this->state);
     return offset;
    }

    const char * getType(){ return SET_STATE; };
    const char * getMD5(){ return "001fde3cab9e313a150416ff09c08ee4"; };

  };

  class set_stateResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    set_stateResponse():
      success(0)
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
     return offset;
    }

    const char * getType(){ return SET_STATE; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class set_state {
    public:
    typedef set_stateRequest Request;
    typedef set_stateResponse Response;
  };

}
#endif
