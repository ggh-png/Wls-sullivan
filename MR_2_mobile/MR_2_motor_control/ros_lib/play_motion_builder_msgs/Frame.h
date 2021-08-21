#ifndef _ROS_play_motion_builder_msgs_Frame_h
#define _ROS_play_motion_builder_msgs_Frame_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace play_motion_builder_msgs
{

  class Frame : public ros::Msg
  {
    public:
      uint32_t pose_length;
      typedef float _pose_type;
      _pose_type st_pose;
      _pose_type * pose;
      typedef float _time_from_last_type;
      _time_from_last_type time_from_last;

    Frame():
      pose_length(0), pose(NULL),
      time_from_last(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->pose_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pose_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pose_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pose_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pose_length);
      for( uint32_t i = 0; i < pose_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->pose[i]);
      }
      union {
        float real;
        uint32_t base;
      } u_time_from_last;
      u_time_from_last.real = this->time_from_last;
      *(outbuffer + offset + 0) = (u_time_from_last.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_time_from_last.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_time_from_last.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_time_from_last.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_from_last);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t pose_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      pose_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      pose_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      pose_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->pose_length);
      if(pose_lengthT > pose_length)
        this->pose = (float*)realloc(this->pose, pose_lengthT * sizeof(float));
      pose_length = pose_lengthT;
      for( uint32_t i = 0; i < pose_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_pose));
        memcpy( &(this->pose[i]), &(this->st_pose), sizeof(float));
      }
      union {
        float real;
        uint32_t base;
      } u_time_from_last;
      u_time_from_last.base = 0;
      u_time_from_last.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_time_from_last.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_time_from_last.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_time_from_last.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->time_from_last = u_time_from_last.real;
      offset += sizeof(this->time_from_last);
     return offset;
    }

    const char * getType(){ return "play_motion_builder_msgs/Frame"; };
    const char * getMD5(){ return "2e413d8203e397a420aef72e551374ab"; };

  };

}
#endif
