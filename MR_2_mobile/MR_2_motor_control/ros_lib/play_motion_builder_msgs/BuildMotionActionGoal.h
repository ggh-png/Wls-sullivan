#ifndef _ROS_play_motion_builder_msgs_BuildMotionActionGoal_h
#define _ROS_play_motion_builder_msgs_BuildMotionActionGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalID.h"
#include "play_motion_builder_msgs/BuildMotionGoal.h"

namespace play_motion_builder_msgs
{

  class BuildMotionActionGoal : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef actionlib_msgs::GoalID _goal_id_type;
      _goal_id_type goal_id;
      typedef play_motion_builder_msgs::BuildMotionGoal _goal_type;
      _goal_type goal;

    BuildMotionActionGoal():
      header(),
      goal_id(),
      goal()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->goal_id.serialize(outbuffer + offset);
      offset += this->goal.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->goal_id.deserialize(inbuffer + offset);
      offset += this->goal.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "play_motion_builder_msgs/BuildMotionActionGoal"; };
    const char * getMD5(){ return "157ed3a8787d99d1a11d0ce8a596f3b7"; };

  };

}
#endif
