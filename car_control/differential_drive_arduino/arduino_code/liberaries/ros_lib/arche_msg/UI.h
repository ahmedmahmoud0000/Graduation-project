#ifndef _ROS_arche_msg_UI_h
#define _ROS_arche_msg_UI_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace arche_msg
{

  class UI : public ros::Msg
  {
    public:
      typedef const char* _gender_type;
      _gender_type gender;
      typedef uint32_t _g_conf_type;
      _g_conf_type g_conf;
      typedef const char* _determined_gender_type;
      _determined_gender_type determined_gender;
      typedef uint32_t _age_type;
      _age_type age;
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
      typedef const char* _determined_emotion_type;
      _determined_emotion_type determined_emotion;
      typedef const char* _ad_name_type;
      _ad_name_type ad_name;
      typedef const char* _qr_name_type;
      _qr_name_type qr_name;

    UI():
      gender(""),
      g_conf(0),
      determined_gender(""),
      age(0),
      happiness(0),
      neutral(0),
      surprize(0),
      sadness(0),
      anger(0),
      determined_emotion(""),
      ad_name(""),
      qr_name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_gender = strlen(this->gender);
      varToArr(outbuffer + offset, length_gender);
      offset += 4;
      memcpy(outbuffer + offset, this->gender, length_gender);
      offset += length_gender;
      *(outbuffer + offset + 0) = (this->g_conf >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->g_conf >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->g_conf >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->g_conf >> (8 * 3)) & 0xFF;
      offset += sizeof(this->g_conf);
      uint32_t length_determined_gender = strlen(this->determined_gender);
      varToArr(outbuffer + offset, length_determined_gender);
      offset += 4;
      memcpy(outbuffer + offset, this->determined_gender, length_determined_gender);
      offset += length_determined_gender;
      *(outbuffer + offset + 0) = (this->age >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->age >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->age >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->age >> (8 * 3)) & 0xFF;
      offset += sizeof(this->age);
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
      uint32_t length_determined_emotion = strlen(this->determined_emotion);
      varToArr(outbuffer + offset, length_determined_emotion);
      offset += 4;
      memcpy(outbuffer + offset, this->determined_emotion, length_determined_emotion);
      offset += length_determined_emotion;
      uint32_t length_ad_name = strlen(this->ad_name);
      varToArr(outbuffer + offset, length_ad_name);
      offset += 4;
      memcpy(outbuffer + offset, this->ad_name, length_ad_name);
      offset += length_ad_name;
      uint32_t length_qr_name = strlen(this->qr_name);
      varToArr(outbuffer + offset, length_qr_name);
      offset += 4;
      memcpy(outbuffer + offset, this->qr_name, length_qr_name);
      offset += length_qr_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_gender;
      arrToVar(length_gender, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_gender; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_gender-1]=0;
      this->gender = (char *)(inbuffer + offset-1);
      offset += length_gender;
      this->g_conf =  ((uint32_t) (*(inbuffer + offset)));
      this->g_conf |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->g_conf |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->g_conf |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->g_conf);
      uint32_t length_determined_gender;
      arrToVar(length_determined_gender, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_determined_gender; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_determined_gender-1]=0;
      this->determined_gender = (char *)(inbuffer + offset-1);
      offset += length_determined_gender;
      this->age =  ((uint32_t) (*(inbuffer + offset)));
      this->age |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->age |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->age |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->age);
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
      uint32_t length_determined_emotion;
      arrToVar(length_determined_emotion, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_determined_emotion; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_determined_emotion-1]=0;
      this->determined_emotion = (char *)(inbuffer + offset-1);
      offset += length_determined_emotion;
      uint32_t length_ad_name;
      arrToVar(length_ad_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_ad_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_ad_name-1]=0;
      this->ad_name = (char *)(inbuffer + offset-1);
      offset += length_ad_name;
      uint32_t length_qr_name;
      arrToVar(length_qr_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_qr_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_qr_name-1]=0;
      this->qr_name = (char *)(inbuffer + offset-1);
      offset += length_qr_name;
     return offset;
    }

    const char * getType(){ return "arche_msg/UI"; };
    const char * getMD5(){ return "b8f47e80ee00f1e555f7a185658c8c17"; };

  };

}
#endif
