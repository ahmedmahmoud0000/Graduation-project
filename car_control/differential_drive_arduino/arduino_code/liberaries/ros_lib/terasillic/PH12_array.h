#ifndef _ROS_terasillic_PH12_array_h
#define _ROS_terasillic_PH12_array_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace terasillic
{

  class PH12_array : public ros::Msg
  {
    public:
      typedef const char* _sensor_name_type;
      _sensor_name_type sensor_name;
      uint32_t angle_length;
      typedef int32_t _angle_type;
      _angle_type st_angle;
      _angle_type * angle;
      uint32_t vrms_length;
      typedef int32_t _vrms_type;
      _vrms_type st_vrms;
      _vrms_type * vrms;
      uint32_t distance_length;
      typedef int32_t _distance_type;
      _distance_type st_distance;
      _distance_type * distance;
      uint32_t velocity_length;
      typedef int32_t _velocity_type;
      _velocity_type st_velocity;
      _velocity_type * velocity;

    PH12_array():
      sensor_name(""),
      angle_length(0), angle(NULL),
      vrms_length(0), vrms(NULL),
      distance_length(0), distance(NULL),
      velocity_length(0), velocity(NULL)
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
      *(outbuffer + offset + 0) = (this->angle_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->angle_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->angle_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->angle_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle_length);
      for( uint32_t i = 0; i < angle_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_anglei;
      u_anglei.real = this->angle[i];
      *(outbuffer + offset + 0) = (u_anglei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_anglei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_anglei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_anglei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle[i]);
      }
      *(outbuffer + offset + 0) = (this->vrms_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->vrms_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->vrms_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->vrms_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vrms_length);
      for( uint32_t i = 0; i < vrms_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_vrmsi;
      u_vrmsi.real = this->vrms[i];
      *(outbuffer + offset + 0) = (u_vrmsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_vrmsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_vrmsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_vrmsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->vrms[i]);
      }
      *(outbuffer + offset + 0) = (this->distance_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->distance_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->distance_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->distance_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance_length);
      for( uint32_t i = 0; i < distance_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_distancei;
      u_distancei.real = this->distance[i];
      *(outbuffer + offset + 0) = (u_distancei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distancei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distancei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distancei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance[i]);
      }
      *(outbuffer + offset + 0) = (this->velocity_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->velocity_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->velocity_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->velocity_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->velocity_length);
      for( uint32_t i = 0; i < velocity_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_velocityi;
      u_velocityi.real = this->velocity[i];
      *(outbuffer + offset + 0) = (u_velocityi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_velocityi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_velocityi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_velocityi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->velocity[i]);
      }
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
      uint32_t angle_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      angle_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      angle_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      angle_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->angle_length);
      if(angle_lengthT > angle_length)
        this->angle = (int32_t*)realloc(this->angle, angle_lengthT * sizeof(int32_t));
      angle_length = angle_lengthT;
      for( uint32_t i = 0; i < angle_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_angle;
      u_st_angle.base = 0;
      u_st_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_angle = u_st_angle.real;
      offset += sizeof(this->st_angle);
        memcpy( &(this->angle[i]), &(this->st_angle), sizeof(int32_t));
      }
      uint32_t vrms_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      vrms_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      vrms_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      vrms_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->vrms_length);
      if(vrms_lengthT > vrms_length)
        this->vrms = (int32_t*)realloc(this->vrms, vrms_lengthT * sizeof(int32_t));
      vrms_length = vrms_lengthT;
      for( uint32_t i = 0; i < vrms_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_vrms;
      u_st_vrms.base = 0;
      u_st_vrms.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_vrms.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_vrms.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_vrms.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_vrms = u_st_vrms.real;
      offset += sizeof(this->st_vrms);
        memcpy( &(this->vrms[i]), &(this->st_vrms), sizeof(int32_t));
      }
      uint32_t distance_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      distance_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      distance_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      distance_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->distance_length);
      if(distance_lengthT > distance_length)
        this->distance = (int32_t*)realloc(this->distance, distance_lengthT * sizeof(int32_t));
      distance_length = distance_lengthT;
      for( uint32_t i = 0; i < distance_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_distance;
      u_st_distance.base = 0;
      u_st_distance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_distance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_distance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_distance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_distance = u_st_distance.real;
      offset += sizeof(this->st_distance);
        memcpy( &(this->distance[i]), &(this->st_distance), sizeof(int32_t));
      }
      uint32_t velocity_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      velocity_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      velocity_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      velocity_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->velocity_length);
      if(velocity_lengthT > velocity_length)
        this->velocity = (int32_t*)realloc(this->velocity, velocity_lengthT * sizeof(int32_t));
      velocity_length = velocity_lengthT;
      for( uint32_t i = 0; i < velocity_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_velocity;
      u_st_velocity.base = 0;
      u_st_velocity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_velocity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_velocity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_velocity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_velocity = u_st_velocity.real;
      offset += sizeof(this->st_velocity);
        memcpy( &(this->velocity[i]), &(this->st_velocity), sizeof(int32_t));
      }
     return offset;
    }

    const char * getType(){ return "terasillic/PH12_array"; };
    const char * getMD5(){ return "0228e6b0830333c485b9f88060ce953b"; };

  };

}
#endif
