#ifndef _ROS_robot_msgs_Motor_h
#define _ROS_robot_msgs_Motor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Float32.h"

namespace robot_msgs
{

  class Motor : public ros::Msg
  {
    public:
      typedef std_msgs::Float32 _left_motor_type;
      _left_motor_type left_motor;
      typedef std_msgs::Float32 _right_motor_type;
      _right_motor_type right_motor;

    Motor():
      left_motor(),
      right_motor()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->left_motor.serialize(outbuffer + offset);
      offset += this->right_motor.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->left_motor.deserialize(inbuffer + offset);
      offset += this->right_motor.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "robot_msgs/Motor"; };
    const char * getMD5(){ return "f1833020ad39d618c71c9444e16c3a94"; };

  };

}
#endif
