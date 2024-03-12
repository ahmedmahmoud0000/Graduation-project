#ifndef _ROS_virtual_costmap_layer_Form_h
#define _ROS_virtual_costmap_layer_Form_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/duration.h"

namespace virtual_costmap_layer
{

  class Form : public ros::Msg
  {
    public:
      typedef uint8_t _type_type;
      _type_type type;
      typedef const char* _description_type;
      _description_type description;
      typedef const char* _uuid_type;
      _uuid_type uuid;
      typedef const char* _data_type;
      _data_type data;
      typedef ros::Duration _lifetime_type;
      _lifetime_type lifetime;
      enum { TYPE_CIRCLE = 0 };
      enum { TYPE_LINESTRING = 1 };
      enum { TYPE_RING = 2 };
      enum { TYPE_POLYGON = 3 };

    Form():
      type(0),
      description(""),
      uuid(""),
      data(""),
      lifetime()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->type >> (8 * 0)) & 0xFF;
      offset += sizeof(this->type);
      uint32_t length_description = strlen(this->description);
      varToArr(outbuffer + offset, length_description);
      offset += 4;
      memcpy(outbuffer + offset, this->description, length_description);
      offset += length_description;
      uint32_t length_uuid = strlen(this->uuid);
      varToArr(outbuffer + offset, length_uuid);
      offset += 4;
      memcpy(outbuffer + offset, this->uuid, length_uuid);
      offset += length_uuid;
      uint32_t length_data = strlen(this->data);
      varToArr(outbuffer + offset, length_data);
      offset += 4;
      memcpy(outbuffer + offset, this->data, length_data);
      offset += length_data;
      *(outbuffer + offset + 0) = (this->lifetime.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->lifetime.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->lifetime.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->lifetime.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lifetime.sec);
      *(outbuffer + offset + 0) = (this->lifetime.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->lifetime.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->lifetime.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->lifetime.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lifetime.nsec);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->type =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->type);
      uint32_t length_description;
      arrToVar(length_description, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_description; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_description-1]=0;
      this->description = (char *)(inbuffer + offset-1);
      offset += length_description;
      uint32_t length_uuid;
      arrToVar(length_uuid, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_uuid; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_uuid-1]=0;
      this->uuid = (char *)(inbuffer + offset-1);
      offset += length_uuid;
      uint32_t length_data;
      arrToVar(length_data, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_data; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_data-1]=0;
      this->data = (char *)(inbuffer + offset-1);
      offset += length_data;
      this->lifetime.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->lifetime.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->lifetime.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->lifetime.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->lifetime.sec);
      this->lifetime.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->lifetime.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->lifetime.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->lifetime.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->lifetime.nsec);
     return offset;
    }

    const char * getType(){ return "virtual_costmap_layer/Form"; };
    const char * getMD5(){ return "1eb9d3e4ecf50c9483cf17c319ac0a0d"; };

  };

}
#endif
