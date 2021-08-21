#ifndef _ROS_play_motion_builder_msgs_BuildMotionFeedback_h
#define _ROS_play_motion_builder_msgs_BuildMotionFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace play_motion_builder_msgs
{

  class BuildMotionFeedback : public ros::Msg
  {
    public:

    BuildMotionFeedback()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return "play_motion_builder_msgs/BuildMotionFeedback"; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

}
#endif
