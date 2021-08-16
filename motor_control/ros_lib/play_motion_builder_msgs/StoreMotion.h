#ifndef _ROS_SERVICE_StoreMotion_h
#define _ROS_SERVICE_StoreMotion_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "play_motion_builder_msgs/Meta.h"

namespace play_motion_builder_msgs
{

static const char STOREMOTION[] = "play_motion_builder_msgs/StoreMotion";

  class StoreMotionRequest : public ros::Msg
  {
    public:
      typedef const char* _file_path_type;
      _file_path_type file_path;
      typedef const char* _ros_name_type;
      _ros_name_type ros_name;
      typedef play_motion_builder_msgs::Meta _meta_type;
      _meta_type meta;

    StoreMotionRequest():
      file_path(""),
      ros_name(""),
      meta()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_file_path = strlen(this->file_path);
      varToArr(outbuffer + offset, length_file_path);
      offset += 4;
      memcpy(outbuffer + offset, this->file_path, length_file_path);
      offset += length_file_path;
      uint32_t length_ros_name = strlen(this->ros_name);
      varToArr(outbuffer + offset, length_ros_name);
      offset += 4;
      memcpy(outbuffer + offset, this->ros_name, length_ros_name);
      offset += length_ros_name;
      offset += this->meta.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_file_path;
      arrToVar(length_file_path, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_file_path; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_file_path-1]=0;
      this->file_path = (char *)(inbuffer + offset-1);
      offset += length_file_path;
      uint32_t length_ros_name;
      arrToVar(length_ros_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_ros_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_ros_name-1]=0;
      this->ros_name = (char *)(inbuffer + offset-1);
      offset += length_ros_name;
      offset += this->meta.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return STOREMOTION; };
    const char * getMD5(){ return "e011623bacdee6d99901579b964c8623"; };

  };

  class StoreMotionResponse : public ros::Msg
  {
    public:
      typedef bool _ok_type;
      _ok_type ok;
      typedef const char* _message_type;
      _message_type message;

    StoreMotionResponse():
      ok(0),
      message("")
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
     return offset;
    }

    const char * getType(){ return STOREMOTION; };
    const char * getMD5(){ return "f6fcb3b1ed8c7743c7fb7d5bcca28513"; };

  };

  class StoreMotion {
    public:
    typedef StoreMotionRequest Request;
    typedef StoreMotionResponse Response;
  };

}
#endif
