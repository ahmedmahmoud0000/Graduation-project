#ifndef _ROS_virtual_costmap_layer_Circle_h
#define _ROS_virtual_costmap_layer_Circle_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point.h"

namespace virtual_costmap_layer
{

  class Circle : public ros::Msg
  {
    public:
      typedef geometry_msgs::Point _center_type;
      _center_type center;
      typedef float _radius_type;
      _radius_type radius;
      typedef int32_t _nb_points_type;
      _nb_points_type nb_points;

    Circle():
      center(),
      radius(0),
      nb_points(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->center.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_radius;
      u_radius.real = this->radius;
      *(outbuffer + offset + 0) = (u_radius.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_radius.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_radius.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_radius.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->radius);
      union {
        int32_t real;
        uint32_t base;
      } u_nb_points;
      u_nb_points.real = this->nb_points;
      *(outbuffer + offset + 0) = (u_nb_points.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_nb_points.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_nb_points.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_nb_points.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->nb_points);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->center.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_radius;
      u_radius.base = 0;
      u_radius.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_radius.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_radius.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_radius.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->radius = u_radius.real;
      offset += sizeof(this->radius);
      union {
        int32_t real;
        uint32_t base;
      } u_nb_points;
      u_nb_points.base = 0;
      u_nb_points.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_nb_points.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_nb_points.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_nb_points.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->nb_points = u_nb_points.real;
      offset += sizeof(this->nb_points);
     return offset;
    }

    const char * getType(){ return "virtual_costmap_layer/Circle"; };
    const char * getMD5(){ return "65c9c840d52a62271c09db26cc483168"; };

  };

}
#endif
