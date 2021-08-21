#ifndef _ROS_play_motion_msgs_PlayMotionFeedback_h
#define _ROS_play_motion_msgs_PlayMotionFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace play_motion_msgs
{

  class PlayMotionFeedback : public ros::Msg
  {
    public:

    PlayMotionFeedback()
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

    const char * getType(){ return "play_motion_msgs/PlayMotionFeedback"; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

}
#endif
