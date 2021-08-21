#ifndef _ROS_play_motion_builder_msgs_Motion_h
#define _ROS_play_motion_builder_msgs_Motion_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "play_motion_builder_msgs/Frame.h"

namespace play_motion_builder_msgs
{

  class Motion : public ros::Msg
  {
    public:
      uint32_t joints_length;
      typedef char* _joints_type;
      _joints_type st_joints;
      _joints_type * joints;
      uint32_t keyframes_length;
      typedef play_motion_builder_msgs::Frame _keyframes_type;
      _keyframes_type st_keyframes;
      _keyframes_type * keyframes;
      typedef const char* _used_group_type;
      _used_group_type used_group;

    Motion():
      joints_length(0), joints(NULL),
      keyframes_length(0), keyframes(NULL),
      used_group("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->joints_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->joints_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->joints_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->joints_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->joints_length);
      for( uint32_t i = 0; i < joints_length; i++){
      uint32_t length_jointsi = strlen(this->joints[i]);
      varToArr(outbuffer + offset, length_jointsi);
      offset += 4;
      memcpy(outbuffer + offset, this->joints[i], length_jointsi);
      offset += length_jointsi;
      }
      *(outbuffer + offset + 0) = (this->keyframes_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->keyframes_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->keyframes_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->keyframes_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->keyframes_length);
      for( uint32_t i = 0; i < keyframes_length; i++){
      offset += this->keyframes[i].serialize(outbuffer + offset);
      }
      uint32_t length_used_group = strlen(this->used_group);
      varToArr(outbuffer + offset, length_used_group);
      offset += 4;
      memcpy(outbuffer + offset, this->used_group, length_used_group);
      offset += length_used_group;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t joints_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      joints_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      joints_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      joints_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->joints_length);
      if(joints_lengthT > joints_length)
        this->joints = (char**)realloc(this->joints, joints_lengthT * sizeof(char*));
      joints_length = joints_lengthT;
      for( uint32_t i = 0; i < joints_length; i++){
      uint32_t length_st_joints;
      arrToVar(length_st_joints, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_joints; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_joints-1]=0;
      this->st_joints = (char *)(inbuffer + offset-1);
      offset += length_st_joints;
        memcpy( &(this->joints[i]), &(this->st_joints), sizeof(char*));
      }
      uint32_t keyframes_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      keyframes_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      keyframes_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      keyframes_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->keyframes_length);
      if(keyframes_lengthT > keyframes_length)
        this->keyframes = (play_motion_builder_msgs::Frame*)realloc(this->keyframes, keyframes_lengthT * sizeof(play_motion_builder_msgs::Frame));
      keyframes_length = keyframes_lengthT;
      for( uint32_t i = 0; i < keyframes_length; i++){
      offset += this->st_keyframes.deserialize(inbuffer + offset);
        memcpy( &(this->keyframes[i]), &(this->st_keyframes), sizeof(play_motion_builder_msgs::Frame));
      }
      uint32_t length_used_group;
      arrToVar(length_used_group, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_used_group; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_used_group-1]=0;
      this->used_group = (char *)(inbuffer + offset-1);
      offset += length_used_group;
     return offset;
    }

    const char * getType(){ return "play_motion_builder_msgs/Motion"; };
    const char * getMD5(){ return "0cd6cb21dc200c52ee3c8d281eccf636"; };

  };

}
#endif
