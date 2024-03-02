#ifndef _ROS_terasillic_PH12_h
#define _ROS_terasillic_PH12_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace terasillic
{

  class PH12 : public ros::Msg
  {
    public:
      typedef const char* _sensor_name_type;
      _sensor_name_type sensor_name;
      typedef int32_t _angle_type;
      _angle_type angle;
      typedef int32_t _vrms_type;
      _vrms_type vrms;
      typedef int32_t _distance_type;
      _distance_type distance;
      typedef int32_t _velocity_type;
      _velocity_type velocity;

    PH12():
      sensor_name(""),
      angle(0),
      vrms(0),
      distance(0),
      velocity(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_sensor_name = strlen(this->sensor_name);
      varToArr(outbuffer + offset, length_sensor_name);
      offset += 4;
      memcpy(outbuffer + offset, this->sensor_name, length_sensor_name);
      offset += length_sensor_name;
      union {
        int32_t real;
        uint32_t base;
      } u_angle;
      u_angle.real = this->angle;
      *(outbuffer + offset + 0) = (u_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle);
      union {
        int32_t real;
        uint32_t base;
      } u_vrms;
      u_vrms.real = this->vrms;
      *(outbuffer + offset + 0) = (u_vrms.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_vrms.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_vrms.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_vrms.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vrms);
      union {
        int32_t real;
        uint32_t base;
      } u_distance;
      u_distance.real = this->distance;
      *(outbuffer + offset + 0) = (u_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distance.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance);
      union {
        int32_t real;
        uint32_t base;
      } u_velocity;
      u_velocity.real = this->velocity;
      *(outbuffer + offset + 0) = (u_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_velocity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_velocity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_velocity.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->velocity);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_sensor_name;
      arrToVar(length_sensor_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_sensor_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_sensor_name-1]=0;
      this->sensor_name = (char *)(inbuffer + offset-1);
      offset += length_sensor_name;
      union {
        int32_t real;
        uint32_t base;
      } u_angle;
      u_angle.base = 0;
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angle = u_angle.real;
      offset += sizeof(this->angle);
      union {
        int32_t real;
        uint32_t base;
      } u_vrms;
      u_vrms.base = 0;
      u_vrms.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_vrms.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_vrms.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_vrms.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->vrms = u_vrms.real;
      offset += sizeof(this->vrms);
      union {
        int32_t real;
        uint32_t base;
      } u_distance;
      u_distance.base = 0;
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->distance = u_distance.real;
      offset += sizeof(this->distance);
      union {
        int32_t real;
        uint32_t base;
      } u_velocity;
      u_velocity.base = 0;
      u_velocity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_velocity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_velocity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_velocity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->velocity = u_velocity.real;
      offset += sizeof(this->velocity);
     return offset;
    }

    const char * getType(){ return "terasillic/PH12"; };
    const char * getMD5(){ return "d3e3a953e77975b862e054b34a1cf330"; };

  };

}
#endif
