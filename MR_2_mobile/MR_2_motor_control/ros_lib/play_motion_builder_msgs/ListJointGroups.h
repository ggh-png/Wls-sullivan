#ifndef _ROS_SERVICE_ListJointGroups_h
#define _ROS_SERVICE_ListJointGroups_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace play_motion_builder_msgs
{

static const char LISTJOINTGROUPS[] = "play_motion_builder_msgs/ListJointGroups";

  class ListJointGroupsRequest : public ros::Msg
  {
    public:

    ListJointGroupsRequest()
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

    const char * getType(){ return LISTJOINTGROUPS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ListJointGroupsResponse : public ros::Msg
  {
    public:
      uint32_t groups_length;
      typedef char* _groups_type;
      _groups_type st_groups;
      _groups_type * groups;
      uint32_t additional_joints_length;
      typedef char* _additional_joints_type;
      _additional_joints_type st_additional_joints;
      _additional_joints_type * additional_joints;
      uint32_t available_joints_length;
      typedef char* _available_joints_type;
      _available_joints_type st_available_joints;
      _available_joints_type * available_joints;

    ListJointGroupsResponse():
      groups_length(0), groups(NULL),
      additional_joints_length(0), additional_joints(NULL),
      available_joints_length(0), available_joints(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->groups_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->groups_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->groups_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->groups_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->groups_length);
      for( uint32_t i = 0; i < groups_length; i++){
      uint32_t length_groupsi = strlen(this->groups[i]);
      varToArr(outbuffer + offset, length_groupsi);
      offset += 4;
      memcpy(outbuffer + offset, this->groups[i], length_groupsi);
      offset += length_groupsi;
      }
      *(outbuffer + offset + 0) = (this->additional_joints_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->additional_joints_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->additional_joints_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->additional_joints_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->additional_joints_length);
      for( uint32_t i = 0; i < additional_joints_length; i++){
      uint32_t length_additional_jointsi = strlen(this->additional_joints[i]);
      varToArr(outbuffer + offset, length_additional_jointsi);
      offset += 4;
      memcpy(outbuffer + offset, this->additional_joints[i], length_additional_jointsi);
      offset += length_additional_jointsi;
      }
      *(outbuffer + offset + 0) = (this->available_joints_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->available_joints_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->available_joints_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->available_joints_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->available_joints_length);
      for( uint32_t i = 0; i < available_joints_length; i++){
      uint32_t length_available_jointsi = strlen(this->available_joints[i]);
      varToArr(outbuffer + offset, length_available_jointsi);
      offset += 4;
      memcpy(outbuffer + offset, this->available_joints[i], length_available_jointsi);
      offset += length_available_jointsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t groups_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      groups_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      groups_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      groups_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->groups_length);
      if(groups_lengthT > groups_length)
        this->groups = (char**)realloc(this->groups, groups_lengthT * sizeof(char*));
      groups_length = groups_lengthT;
      for( uint32_t i = 0; i < groups_length; i++){
      uint32_t length_st_groups;
      arrToVar(length_st_groups, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_groups; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_groups-1]=0;
      this->st_groups = (char *)(inbuffer + offset-1);
      offset += length_st_groups;
        memcpy( &(this->groups[i]), &(this->st_groups), sizeof(char*));
      }
      uint32_t additional_joints_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      additional_joints_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      additional_joints_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      additional_joints_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->additional_joints_length);
      if(additional_joints_lengthT > additional_joints_length)
        this->additional_joints = (char**)realloc(this->additional_joints, additional_joints_lengthT * sizeof(char*));
      additional_joints_length = additional_joints_lengthT;
      for( uint32_t i = 0; i < additional_joints_length; i++){
      uint32_t length_st_additional_joints;
      arrToVar(length_st_additional_joints, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_additional_joints; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_additional_joints-1]=0;
      this->st_additional_joints = (char *)(inbuffer + offset-1);
      offset += length_st_additional_joints;
        memcpy( &(this->additional_joints[i]), &(this->st_additional_joints), sizeof(char*));
      }
      uint32_t available_joints_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      available_joints_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      available_joints_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      available_joints_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->available_joints_length);
      if(available_joints_lengthT > available_joints_length)
        this->available_joints = (char**)realloc(this->available_joints, available_joints_lengthT * sizeof(char*));
      available_joints_length = available_joints_lengthT;
      for( uint32_t i = 0; i < available_joints_length; i++){
      uint32_t length_st_available_joints;
      arrToVar(length_st_available_joints, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_available_joints; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_available_joints-1]=0;
      this->st_available_joints = (char *)(inbuffer + offset-1);
      offset += length_st_available_joints;
        memcpy( &(this->available_joints[i]), &(this->st_available_joints), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return LISTJOINTGROUPS; };
    const char * getMD5(){ return "9fdaed4e1eb95768801699335d06285a"; };

  };

  class ListJointGroups {
    public:
    typedef ListJointGroupsRequest Request;
    typedef ListJointGroupsResponse Response;
  };

}
#endif
