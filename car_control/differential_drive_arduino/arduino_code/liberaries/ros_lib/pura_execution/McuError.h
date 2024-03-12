#ifndef _ROS_pura_execution_McuError_h
#define _ROS_pura_execution_McuError_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace pura_execution
{

  class McuError : public ros::Msg
  {
    public:
      typedef uint8_t _id_type;
      _id_type id;
      typedef uint8_t _error_code_type;
      _error_code_type error_code;

    McuError():
      id(0),
      error_code(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      *(outbuffer + offset + 0) = (this->error_code >> (8 * 0)) & 0xFF;
      offset += sizeof(this->error_code);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
      this->error_code =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->error_code);
     return offset;
    }

    const char * getType(){ return "pura_execution/McuError"; };
    const char * getMD5(){ return "34b452370c3a3ac2b86f3dd2cae260ef"; };

  };

}
#endif
