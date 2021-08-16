#ifndef _ROS_play_motion_builder_msgs_RunMotionGoal_h
#define _ROS_play_motion_builder_msgs_RunMotionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace play_motion_builder_msgs
{

  class RunMotionGoal : public ros::Msg
  {
    public:
      typedef uint8_t _run_mode_type;
      _run_mode_type run_mode;
      typedef float _downshift_type;
      _downshift_type downshift;
      typedef uint16_t _step_id_type;
      _step_id_type step_id;
      enum { RUN_MOTION = 0 };
      enum { GO_TO_STEP = 1 };

    RunMotionGoal():
      run_mode(0),
      downshift(0),
      step_id(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->run_mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->run_mode);
      union {
        float real;
        uint32_t base;
      } u_downshift;
      u_downshift.real = this->downshift;
      *(outbuffer + offset + 0) = (u_downshift.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_downshift.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_downshift.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_downshift.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->downshift);
      *(outbuffer + offset + 0) = (this->step_id >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->step_id >> (8 * 1)) & 0xFF;
      offset += sizeof(this->step_id);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->run_mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->run_mode);
      union {
        float real;
        uint32_t base;
      } u_downshift;
      u_downshift.base = 0;
      u_downshift.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_downshift.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_downshift.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_downshift.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->downshift = u_downshift.real;
      offset += sizeof(this->downshift);
      this->step_id =  ((uint16_t) (*(inbuffer + offset)));
      this->step_id |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->step_id);
     return offset;
    }

    const char * getType(){ return "play_motion_builder_msgs/RunMotionGoal"; };
    const char * getMD5(){ return "93fd2cd7e64669cfb4a792f5ad9e13ef"; };

  };

}
#endif
