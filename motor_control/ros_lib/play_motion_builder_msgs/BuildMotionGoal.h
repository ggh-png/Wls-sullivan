#ifndef _ROS_play_motion_builder_msgs_BuildMotionGoal_h
#define _ROS_play_motion_builder_msgs_BuildMotionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace play_motion_builder_msgs
{

  class BuildMotionGoal : public ros::Msg
  {
    public:
      typedef const char* _motion_type;
      _motion_type motion;

    BuildMotionGoal():
      motion("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_motion = strlen(this->motion);
      varToArr(outbuffer + offset, length_motion);
      offset += 4;
      memcpy(outbuffer + offset, this->motion, length_motion);
      offset += length_motion;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_motion;
      arrToVar(length_motion, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_motion; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_motion-1]=0;
      this->motion = (char *)(inbuffer + offset-1);
      offset += length_motion;
     return offset;
    }

    const char * getType(){ return "play_motion_builder_msgs/BuildMotionGoal"; };
    const char * getMD5(){ return "56c5b2babfc4b27e5a596091bb964bc2"; };

  };

}
#endif
