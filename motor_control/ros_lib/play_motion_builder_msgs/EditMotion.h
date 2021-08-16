#ifndef _ROS_SERVICE_EditMotion_h
#define _ROS_SERVICE_EditMotion_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "play_motion_builder_msgs/Motion.h"

namespace play_motion_builder_msgs
{

static const char EDITMOTION[] = "play_motion_builder_msgs/EditMotion";

  class EditMotionRequest : public ros::Msg
  {
    public:
      typedef uint16_t _step_id_type;
      _step_id_type step_id;
      typedef uint8_t _action_type;
      _action_type action;
      typedef float _time_type;
      _time_type time;
      enum { LIST = 0 };
      enum { APPEND = 1 };
      enum { EDIT = 2 };
      enum { COPY_AS_NEXT = 3 };
      enum { COPY_AS_LAST = 4 };
      enum { REMOVE = 5 };
      enum { EDIT_TIME = 6 };

    EditMotionRequest():
      step_id(0),
      action(0),
      time(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->step_id >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->step_id >> (8 * 1)) & 0xFF;
      offset += sizeof(this->step_id);
      *(outbuffer + offset + 0) = (this->action >> (8 * 0)) & 0xFF;
      offset += sizeof(this->action);
      union {
        float real;
        uint32_t base;
      } u_time;
      u_time.real = this->time;
      *(outbuffer + offset + 0) = (u_time.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_time.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_time.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_time.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->step_id =  ((uint16_t) (*(inbuffer + offset)));
      this->step_id |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->step_id);
      this->action =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->action);
      union {
        float real;
        uint32_t base;
      } u_time;
      u_time.base = 0;
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->time = u_time.real;
      offset += sizeof(this->time);
     return offset;
    }

    const char * getType(){ return EDITMOTION; };
    const char * getMD5(){ return "994d269af2f608a6b9a823b10da14d7d"; };

  };

  class EditMotionResponse : public ros::Msg
  {
    public:
      typedef bool _ok_type;
      _ok_type ok;
      typedef const char* _message_type;
      _message_type message;
      typedef play_motion_builder_msgs::Motion _motion_type;
      _motion_type motion;

    EditMotionResponse():
      ok(0),
      message(""),
      motion()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_ok;
      u_ok.real = this->ok;
      *(outbuffer + offset + 0) = (u_ok.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ok);
      uint32_t length_message = strlen(this->message);
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      offset += this->motion.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_ok;
      u_ok.base = 0;
      u_ok.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->ok = u_ok.real;
      offset += sizeof(this->ok);
      uint32_t length_message;
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
      offset += this->motion.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return EDITMOTION; };
    const char * getMD5(){ return "b8977f11190208bf644de5781a8adaa9"; };

  };

  class EditMotion {
    public:
    typedef EditMotionRequest Request;
    typedef EditMotionResponse Response;
  };

}
#endif
