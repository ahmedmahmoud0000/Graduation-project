#ifndef _ROS_SERVICE_GetElements_h
#define _ROS_SERVICE_GetElements_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "virtual_costmap_layer/Form.h"

namespace virtual_costmap_layer
{

static const char GETELEMENTS[] = "virtual_costmap_layer/GetElements";

  class GetElementsRequest : public ros::Msg
  {
    public:

    GetElementsRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return GETELEMENTS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetElementsResponse : public ros::Msg
  {
    public:
      uint32_t forms_length;
      typedef virtual_costmap_layer::Form _forms_type;
      _forms_type st_forms;
      _forms_type * forms;

    GetElementsResponse():
      forms_length(0), forms(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->forms_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->forms_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->forms_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->forms_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->forms_length);
      for( uint32_t i = 0; i < forms_length; i++){
      offset += this->forms[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t forms_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      forms_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      forms_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      forms_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->forms_length);
      if(forms_lengthT > forms_length)
        this->forms = (virtual_costmap_layer::Form*)realloc(this->forms, forms_lengthT * sizeof(virtual_costmap_layer::Form));
      forms_length = forms_lengthT;
      for( uint32_t i = 0; i < forms_length; i++){
      offset += this->st_forms.deserialize(inbuffer + offset);
        memcpy( &(this->forms[i]), &(this->st_forms), sizeof(virtual_costmap_layer::Form));
      }
     return offset;
    }

    const char * getType(){ return GETELEMENTS; };
    const char * getMD5(){ return "0b1b07edc21b6c086450c04cf5858e40"; };

  };

  class GetElements {
    public:
    typedef GetElementsRequest Request;
    typedef GetElementsResponse Response;
  };

}
#endif
