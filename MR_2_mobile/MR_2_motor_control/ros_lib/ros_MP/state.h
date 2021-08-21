#ifndef _ROS_ros_MP_state_h
#define _ROS_ros_MP_state_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ros_MP
{

  class state : public ros::Msg
  {
    public:
      typedef bool _hungry_type;
      _hungry_type hungry;
      typedef bool _toilet_type;
      _toilet_type toilet;
      typedef bool _tirsty_type;
      _tirsty_type tirsty;

    state():
      hungry(0),
      toilet(0),
      tirsty(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_hungry;
      u_hungry.real = this->hungry;
      *(outbuffer + offset + 0) = (u_hungry.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->hungry);
      union {
        bool real;
        uint8_t base;
      } u_toilet;
      u_toilet.real = this->toilet;
      *(outbuffer + offset + 0) = (u_toilet.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->toilet);
      union {
        bool real;
        uint8_t base;
      } u_tirsty;
      u_tirsty.real = this->tirsty;
      *(outbuffer + offset + 0) = (u_tirsty.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->tirsty);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_hungry;
      u_hungry.base = 0;
      u_hungry.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->hungry = u_hungry.real;
      offset += sizeof(this->hungry);
      union {
        bool real;
        uint8_t base;
      } u_toilet;
      u_toilet.base = 0;
      u_toilet.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->toilet = u_toilet.real;
      offset += sizeof(this->toilet);
      union {
        bool real;
        uint8_t base;
      } u_tirsty;
      u_tirsty.base = 0;
      u_tirsty.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->tirsty = u_tirsty.real;
      offset += sizeof(this->tirsty);
     return offset;
    }

    const char * getType(){ return "ros_MP/state"; };
    const char * getMD5(){ return "ec369daa1c070711bc0e45d3ab2b77e2"; };

  };

}
#endif
