#ifndef _ROS_arche_msg_Ironyun_h
#define _ROS_arche_msg_Ironyun_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "arche_msg/Metadata.h"

namespace arche_msg
{

  class Ironyun : public ros::Msg
  {
    public:
      typedef const char* _Camera_type;
      _Camera_type Camera;
      typedef const char* _ROI_type;
      _ROI_type ROI;
      typedef const char* _Time_type;
      _Time_type Time;
      typedef const char* _Image_url_type;
      _Image_url_type Image_url;
      typedef const char* _Event_url_type;
      _Event_url_type Event_url;
      uint32_t Datas_length;
      typedef arche_msg::Metadata _Datas_type;
      _Datas_type st_Datas;
      _Datas_type * Datas;

    Ironyun():
      Camera(""),
      ROI(""),
      Time(""),
      Image_url(""),
      Event_url(""),
      Datas_length(0), Datas(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_Camera = strlen(this->Camera);
      varToArr(outbuffer + offset, length_Camera);
      offset += 4;
      memcpy(outbuffer + offset, this->Camera, length_Camera);
      offset += length_Camera;
      uint32_t length_ROI = strlen(this->ROI);
      varToArr(outbuffer + offset, length_ROI);
      offset += 4;
      memcpy(outbuffer + offset, this->ROI, length_ROI);
      offset += length_ROI;
      uint32_t length_Time = strlen(this->Time);
      varToArr(outbuffer + offset, length_Time);
      offset += 4;
      memcpy(outbuffer + offset, this->Time, length_Time);
      offset += length_Time;
      uint32_t length_Image_url = strlen(this->Image_url);
      varToArr(outbuffer + offset, length_Image_url);
      offset += 4;
      memcpy(outbuffer + offset, this->Image_url, length_Image_url);
      offset += length_Image_url;
      uint32_t length_Event_url = strlen(this->Event_url);
      varToArr(outbuffer + offset, length_Event_url);
      offset += 4;
      memcpy(outbuffer + offset, this->Event_url, length_Event_url);
      offset += length_Event_url;
      *(outbuffer + offset + 0) = (this->Datas_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->Datas_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->Datas_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->Datas_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Datas_length);
      for( uint32_t i = 0; i < Datas_length; i++){
      offset += this->Datas[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_Camera;
      arrToVar(length_Camera, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_Camera; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_Camera-1]=0;
      this->Camera = (char *)(inbuffer + offset-1);
      offset += length_Camera;
      uint32_t length_ROI;
      arrToVar(length_ROI, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_ROI; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_ROI-1]=0;
      this->ROI = (char *)(inbuffer + offset-1);
      offset += length_ROI;
      uint32_t length_Time;
      arrToVar(length_Time, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_Time; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_Time-1]=0;
      this->Time = (char *)(inbuffer + offset-1);
      offset += length_Time;
      uint32_t length_Image_url;
      arrToVar(length_Image_url, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_Image_url; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_Image_url-1]=0;
      this->Image_url = (char *)(inbuffer + offset-1);
      offset += length_Image_url;
      uint32_t length_Event_url;
      arrToVar(length_Event_url, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_Event_url; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_Event_url-1]=0;
      this->Event_url = (char *)(inbuffer + offset-1);
      offset += length_Event_url;
      uint32_t Datas_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      Datas_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      Datas_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      Datas_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->Datas_length);
      if(Datas_lengthT > Datas_length)
        this->Datas = (arche_msg::Metadata*)realloc(this->Datas, Datas_lengthT * sizeof(arche_msg::Metadata));
      Datas_length = Datas_lengthT;
      for( uint32_t i = 0; i < Datas_length; i++){
      offset += this->st_Datas.deserialize(inbuffer + offset);
        memcpy( &(this->Datas[i]), &(this->st_Datas), sizeof(arche_msg::Metadata));
      }
     return offset;
    }

    const char * getType(){ return "arche_msg/Ironyun"; };
    const char * getMD5(){ return "256eef1bc24df411bc9fb0599a291bc3"; };

  };

}
#endif
