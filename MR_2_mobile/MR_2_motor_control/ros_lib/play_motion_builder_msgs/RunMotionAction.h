#ifndef _ROS_play_motion_builder_msgs_RunMotionAction_h
#define _ROS_play_motion_builder_msgs_RunMotionAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "play_motion_builder_msgs/RunMotionActionGoal.h"
#include "play_motion_builder_msgs/RunMotionActionResult.h"
#include "play_motion_builder_msgs/RunMotionActionFeedback.h"

namespace play_motion_builder_msgs
{

  class RunMotionAction : public ros::Msg
  {
    public:
      typedef play_motion_builder_msgs::RunMotionActionGoal _action_goal_type;
      _action_goal_type action_goal;
      typedef play_motion_builder_msgs::RunMotionActionResult _action_result_type;
      _action_result_type action_result;
      typedef play_motion_builder_msgs::RunMotionActionFeedback _action_feedback_type;
      _action_feedback_type action_feedback;

    RunMotionAction():
      action_goal(),
      action_result(),
      action_feedback()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->action_goal.serialize(outbuffer + offset);
      offset += this->action_result.serialize(outbuffer + offset);
      offset += this->action_feedback.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->action_goal.deserialize(inbuffer + offset);
      offset += this->action_result.deserialize(inbuffer + offset);
      offset += this->action_feedback.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "play_motion_builder_msgs/RunMotionAction"; };
    const char * getMD5(){ return "57a10b77720536607404de3a23075f21"; };

  };

}
#endif
