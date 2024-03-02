#ifndef _ROS_SERVICE_HeatmapCreator_h
#define _ROS_SERVICE_HeatmapCreator_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace arche_msg
{

static const char HEATMAPCREATOR[] = "arche_msg/HeatmapCreator";

  class HeatmapCreatorRequest : public ros::Msg
  {
    public:
      typedef const char* _map_type;
      _map_type map;
      typedef const char* _database_type;
      _database_type database;
      typedef const char* _table_type;
      _table_type table;

    HeatmapCreatorRequest():
      map(""),
      database(""),
      table("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_map = strlen(this->map);
      varToArr(outbuffer + offset, length_map);
      offset += 4;
      memcpy(outbuffer + offset, this->map, length_map);
      offset += length_map;
      uint32_t length_database = strlen(this->database);
      varToArr(outbuffer + offset, length_database);
      offset += 4;
      memcpy(outbuffer + offset, this->database, length_database);
      offset += length_database;
      uint32_t length_table = strlen(this->table);
      varToArr(outbuffer + offset, length_table);
      offset += 4;
      memcpy(outbuffer + offset, this->table, length_table);
      offset += length_table;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_map;
      arrToVar(length_map, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_map; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_map-1]=0;
      this->map = (char *)(inbuffer + offset-1);
      offset += length_map;
      uint32_t length_database;
      arrToVar(length_database, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_database; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_database-1]=0;
      this->database = (char *)(inbuffer + offset-1);
      offset += length_database;
      uint32_t length_table;
      arrToVar(length_table, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_table; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_table-1]=0;
      this->table = (char *)(inbuffer + offset-1);
      offset += length_table;
     return offset;
    }

    const char * getType(){ return HEATMAPCREATOR; };
    const char * getMD5(){ return "98846f1d1f98b2d306487142dabea9a0"; };

  };

  class HeatmapCreatorResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;

    HeatmapCreatorResponse():
      result(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.real = this->result;
      *(outbuffer + offset + 0) = (u_result.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.base = 0;
      u_result.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->result = u_result.real;
      offset += sizeof(this->result);
     return offset;
    }

    const char * getType(){ return HEATMAPCREATOR; };
    const char * getMD5(){ return "eb13ac1f1354ccecb7941ee8fa2192e8"; };

  };

  class HeatmapCreator {
    public:
    typedef HeatmapCreatorRequest Request;
    typedef HeatmapCreatorResponse Response;
  };

}
#endif
