#ifndef _ROS_pura_execution_McuCmdData_h
#define _ROS_pura_execution_McuCmdData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace pura_execution
{

  class McuCmdData : public ros::Msg
  {
    public:
      typedef uint8_t _id_type;
      _id_type id;
      typedef uint8_t _data_type;
      _data_type data;
      enum { ID_FAN_1 =  1 };
      enum { ID_FAN_2 =  2 };

    McuCmdData():
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

    const char * getType(){ return "pura_execution/McuCmdData"; };
    const char * getMD5(){ return "79192a4c3cdd20ef57676b44784ce621"; };

  };

}
#endif
