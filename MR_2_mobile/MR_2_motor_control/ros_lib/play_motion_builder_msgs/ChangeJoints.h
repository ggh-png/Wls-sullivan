#ifndef _ROS_SERVICE_ChangeJoints_h
#define _ROS_SERVICE_ChangeJoints_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace play_motion_builder_msgs
{

static const char CHANGEJOINTS[] = "play_motion_builder_msgs/ChangeJoints";

  class ChangeJointsRequest : public ros::Msg
  {
    public:
      typedef const char* _group_type;
      _group_type group;
      uint32_t joints_to_remove_length;
      typedef char* _joints_to_remove_type;
      _joints_to_remove_type st_joints_to_remove;
      _joints_to_remove_type * joints_to_remove;
      uint32_t joints_to_add_length;
      typedef char* _joints_to_add_type;
      _joints_to_add_type st_joints_to_add;
      _joints_to_add_type * joints_to_add;

    ChangeJointsRequest():
      group(""),
      joints_to_remove_length(0), joints_to_remove(NULL),
      joints_to_add_length(0), joints_to_add(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_group = strlen(this->group);
      varToArr(outbuffer + offset, length_group);
      offset += 4;
      memcpy(outbuffer + offset, this->group, length_group);
      offset += length_group;
      *(outbuffer + offset + 0) = (this->joints_to_remove_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->joints_to_remove_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->joints_to_remove_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->joints_to_remove_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->joints_to_remove_length);
      for( uint32_t i = 0; i < joints_to_remove_length; i++){
      uint32_t length_joints_to_removei = strlen(this->joints_to_remove[i]);
      varToArr(outbuffer + offset, length_joints_to_removei);
      offset += 4;
      memcpy(outbuffer + offset, this->joints_to_remove[i], length_joints_to_removei);
      offset += length_joints_to_removei;
      }
      *(outbuffer + offset + 0) = (this->joints_to_add_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->joints_to_add_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->joints_to_add_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->joints_to_add_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->joints_to_add_length);
      for( uint32_t i = 0; i < joints_to_add_length; i++){
      uint32_t length_joints_to_addi = strlen(this->joints_to_add[i]);
      varToArr(outbuffer + offset, length_joints_to_addi);
      offset += 4;
      memcpy(outbuffer + offset, this->joints_to_add[i], length_joints_to_addi);
      offset += length_joints_to_addi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_group;
      arrToVar(length_group, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_group; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_group-1]=0;
      this->group = (char *)(inbuffer + offset-1);
      offset += length_group;
      uint32_t joints_to_remove_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      joints_to_remove_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      joints_to_remove_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      joints_to_remove_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->joints_to_remove_length);
      if(joints_to_remove_lengthT > joints_to_remove_length)
        this->joints_to_remove = (char**)realloc(this->joints_to_remove, joints_to_remove_lengthT * sizeof(char*));
      joints_to_remove_length = joints_to_remove_lengthT;
      for( uint32_t i = 0; i < joints_to_remove_length; i++){
      uint32_t length_st_joints_to_remove;
      arrToVar(length_st_joints_to_remove, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_joints_to_remove; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_joints_to_remove-1]=0;
      this->st_joints_to_remove = (char *)(inbuffer + offset-1);
      offset += length_st_joints_to_remove;
        memcpy( &(this->joints_to_remove[i]), &(this->st_joints_to_remove), sizeof(char*));
      }
      uint32_t joints_to_add_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      joints_to_add_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      joints_to_add_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      joints_to_add_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->joints_to_add_length);
      if(joints_to_add_lengthT > joints_to_add_length)
        this->joints_to_add = (char**)realloc(this->joints_to_add, joints_to_add_lengthT * sizeof(char*));
      joints_to_add_length = joints_to_add_lengthT;
      for( uint32_t i = 0; i < joints_to_add_length; i++){
      uint32_t length_st_joints_to_add;
      arrToVar(length_st_joints_to_add, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_joints_to_add; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_joints_to_add-1]=0;
      this->st_joints_to_add = (char *)(inbuffer + offset-1);
      offset += length_st_joints_to_add;
        memcpy( &(this->joints_to_add[i]), &(this->st_joints_to_add), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return CHANGEJOINTS; };
    const char * getMD5(){ return "973a28a7a5f5fe66851191cc72cc5580"; };

  };

  class ChangeJointsResponse : public ros::Msg
  {
    public:
      typedef bool _ok_type;
      _ok_type ok;
      typedef const char* _message_type;
      _message_type message;
      typedef const char* _current_group_type;
      _current_group_type current_group;
      uint32_t used_joints_length;
      typedef char* _used_joints_type;
      _used_joints_type st_used_joints;
      _used_joints_type * used_joints;

    ChangeJointsResponse():
      ok(0),
      message(""),
      current_group(""),
      used_joints_length(0), used_joints(NULL)
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
      uint32_t length_current_group = strlen(this->current_group);
      varToArr(outbuffer + offset, length_current_group);
      offset += 4;
      memcpy(outbuffer + offset, this->current_group, length_current_group);
      offset += length_current_group;
      *(outbuffer + offset + 0) = (this->used_joints_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->used_joints_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->used_joints_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->used_joints_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->used_joints_length);
      for( uint32_t i = 0; i < used_joints_length; i++){
      uint32_t length_used_jointsi = strlen(this->used_joints[i]);
      varToArr(outbuffer + offset, length_used_jointsi);
      offset += 4;
      memcpy(outbuffer + offset, this->used_joints[i], length_used_jointsi);
      offset += length_used_jointsi;
      }
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
      uint32_t length_current_group;
      arrToVar(length_current_group, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_current_group; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_current_group-1]=0;
      this->current_group = (char *)(inbuffer + offset-1);
      offset += length_current_group;
      uint32_t used_joints_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      used_joints_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      used_joints_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      used_joints_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->used_joints_length);
      if(used_joints_lengthT > used_joints_length)
        this->used_joints = (char**)realloc(this->used_joints, used_joints_lengthT * sizeof(char*));
      used_joints_length = used_joints_lengthT;
      for( uint32_t i = 0; i < used_joints_length; i++){
      uint32_t length_st_used_joints;
      arrToVar(length_st_used_joints, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_used_joints; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_used_joints-1]=0;
      this->st_used_joints = (char *)(inbuffer + offset-1);
      offset += length_st_used_joints;
        memcpy( &(this->used_joints[i]), &(this->st_used_joints), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return CHANGEJOINTS; };
    const char * getMD5(){ return "84aa9b65e836172877daea91a88d9de9"; };

  };

  class ChangeJoints {
    public:
    typedef ChangeJointsRequest Request;
    typedef ChangeJointsResponse Response;
  };

}
#endif
