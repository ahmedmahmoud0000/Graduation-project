#ifndef _ROS_arche_msg_Demography_h
#define _ROS_arche_msg_Demography_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace arche_msg
{

  class Demography : public ros::Msg
  {
    public:
      typedef uint32_t _pos_x_type;
      _pos_x_type pos_x;
      typedef uint32_t _pos_y_type;
      _pos_y_type pos_y;
      typedef uint32_t _size_type;
      _size_type size;
      typedef uint32_t _f_conf_type;
      _f_conf_type f_conf;
      typedef const char* _gend_type;
      _gend_type gend;
      typedef uint32_t _g_conf_type;
      _g_conf_type g_conf;
      typedef uint32_t _age_type;
      _age_type age;
      typedef uint32_t _a_conf_type;
      _a_conf_type a_conf;
      typedef uint32_t _happiness_type;
      _happiness_type happiness;
      typedef uint32_t _neutral_type;
      _neutral_type neutral;
      typedef uint32_t _surprize_type;
      _surprize_type surprize;
      typedef uint32_t _sadness_type;
      _sadness_type sadness;
      typedef uint32_t _anger_type;
      _anger_type anger;

    Demography():
      pos_x(0),
      pos_y(0),
      size(0),
      f_conf(0),
      gend(""),
      g_conf(0),
      age(0),
      a_conf(0),
      happiness(0),
      neutral(0),
      surprize(0),
      sadness(0),
      anger(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->pos_x >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pos_x >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pos_x >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pos_x >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos_x);
      *(outbuffer + offset + 0) = (this->pos_y >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pos_y >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pos_y >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pos_y >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos_y);
      *(outbuffer + offset + 0) = (this->size >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->size >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->size >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->size >> (8 * 3)) & 0xFF;
      offset += sizeof(this->size);
      *(outbuffer + offset + 0) = (this->f_conf >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->f_conf >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->f_conf >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->f_conf >> (8 * 3)) & 0xFF;
      offset += sizeof(this->f_conf);
      uint32_t length_gend = strlen(this->gend);
      varToArr(outbuffer + offset, length_gend);
      offset += 4;
      memcpy(outbuffer + offset, this->gend, length_gend);
      offset += length_gend;
      *(outbuffer + offset + 0) = (this->g_conf >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->g_conf >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->g_conf >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->g_conf >> (8 * 3)) & 0xFF;
      offset += sizeof(this->g_conf);
      *(outbuffer + offset + 0) = (this->age >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->age >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->age >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->age >> (8 * 3)) & 0xFF;
      offset += sizeof(this->age);
      *(outbuffer + offset + 0) = (this->a_conf >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->a_conf >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->a_conf >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->a_conf >> (8 * 3)) & 0xFF;
      offset += sizeof(this->a_conf);
      *(outbuffer + offset + 0) = (this->happiness >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->happiness >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->happiness >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->happiness >> (8 * 3)) & 0xFF;
      offset += sizeof(this->happiness);
      *(outbuffer + offset + 0) = (this->neutral >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->neutral >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->neutral >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->neutral >> (8 * 3)) & 0xFF;
      offset += sizeof(this->neutral);
      *(outbuffer + offset + 0) = (this->surprize >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->surprize >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->surprize >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->surprize >> (8 * 3)) & 0xFF;
      offset += sizeof(this->surprize);
      *(outbuffer + offset + 0) = (this->sadness >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->sadness >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->sadness >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->sadness >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sadness);
      *(outbuffer + offset + 0) = (this->anger >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->anger >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->anger >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->anger >> (8 * 3)) & 0xFF;
      offset += sizeof(this->anger);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->pos_x =  ((uint32_t) (*(inbuffer + offset)));
      this->pos_x |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->pos_x |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->pos_x |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->pos_x);
      this->pos_y =  ((uint32_t) (*(inbuffer + offset)));
      this->pos_y |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->pos_y |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->pos_y |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->pos_y);
      this->size =  ((uint32_t) (*(inbuffer + offset)));
      this->size |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->size |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->size |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->size);
      this->f_conf =  ((uint32_t) (*(inbuffer + offset)));
      this->f_conf |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->f_conf |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->f_conf |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->f_conf);
      uint32_t length_gend;
      arrToVar(length_gend, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_gend; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_gend-1]=0;
      this->gend = (char *)(inbuffer + offset-1);
      offset += length_gend;
      this->g_conf =  ((uint32_t) (*(inbuffer + offset)));
      this->g_conf |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->g_conf |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->g_conf |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->g_conf);
      this->age =  ((uint32_t) (*(inbuffer + offset)));
      this->age |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->age |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->age |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->age);
      this->a_conf =  ((uint32_t) (*(inbuffer + offset)));
      this->a_conf |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->a_conf |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->a_conf |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->a_conf);
      this->happiness =  ((uint32_t) (*(inbuffer + offset)));
      this->happiness |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->happiness |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->happiness |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->happiness);
      this->neutral =  ((uint32_t) (*(inbuffer + offset)));
      this->neutral |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->neutral |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->neutral |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->neutral);
      this->surprize =  ((uint32_t) (*(inbuffer + offset)));
      this->surprize |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->surprize |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->surprize |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->surprize);
      this->sadness =  ((uint32_t) (*(inbuffer + offset)));
      this->sadness |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->sadness |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->sadness |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->sadness);
      this->anger =  ((uint32_t) (*(inbuffer + offset)));
      this->anger |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->anger |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->anger |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->anger);
     return offset;
    }

    const char * getType(){ return "arche_msg/Demography"; };
    const char * getMD5(){ return "a9e452427592f8dae9e9a7603112a74b"; };

  };

}
#endif
