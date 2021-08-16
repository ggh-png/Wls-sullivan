#ifndef _ROS_play_motion_msgs_PlayMotionGoal_h
#define _ROS_play_motion_msgs_PlayMotionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace play_motion_msgs
{

  class PlayMotionGoal : public ros::Msg
  {
    public:
      typedef const char* _motion_name_type;
      _motion_name_type motion_name;
      typedef bool _skip_planning_type;
      _skip_planning_type skip_planning;
      typedef int32_t _priority_type;
      _priority_type priority;

    PlayMotionGoal():
      motion_name(""),
      skip_planning(0),
      priority(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_motion_name = strlen(this->motion_name);
      varToArr(outbuffer + offset, length_motion_name);
      offset += 4;
      memcpy(outbuffer + offset, this->motion_name, length_motion_name);
      offset += length_motion_name;
      union {
        bool real;
        uint8_t base;
      } u_skip_planning;
      u_skip_planning.real = this->skip_planning;
      *(outbuffer + offset + 0) = (u_skip_planning.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->skip_planning);
      union {
        int32_t real;
        uint32_t base;
      } u_priority;
      u_priority.real = this->priority;
      *(outbuffer + offset + 0) = (u_priority.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_priority.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_priority.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_priority.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->priority);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_motion_name;
      arrToVar(length_motion_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_motion_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_motion_name-1]=0;
      this->motion_name = (char *)(inbuffer + offset-1);
      offset += length_motion_name;
      union {
        bool real;
        uint8_t base;
      } u_skip_planning;
      u_skip_planning.base = 0;
      u_skip_planning.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->skip_planning = u_skip_planning.real;
      offset += sizeof(this->skip_planning);
      union {
        int32_t real;
        uint32_t base;
      } u_priority;
      u_priority.base = 0;
      u_priority.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_priority.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_priority.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_priority.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->priority = u_priority.real;
      offset += sizeof(this->priority);
     return offset;
    }

    const char * getType(){ return "play_motion_msgs/PlayMotionGoal"; };
    const char * getMD5(){ return "803175b562438759e071140087987d02"; };

  };

}
#endif
