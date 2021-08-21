#ifndef _ROS_play_motion_builder_msgs_Meta_h
#define _ROS_play_motion_builder_msgs_Meta_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace play_motion_builder_msgs
{

  class Meta : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef const char* _usage_type;
      _usage_type usage;
      typedef const char* _description_type;
      _description_type description;

    Meta():
      name(""),
      usage(""),
      description("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      uint32_t length_usage = strlen(this->usage);
      varToArr(outbuffer + offset, length_usage);
      offset += 4;
      memcpy(outbuffer + offset, this->usage, length_usage);
      offset += length_usage;
      uint32_t length_description = strlen(this->description);
      varToArr(outbuffer + offset, length_description);
      offset += 4;
      memcpy(outbuffer + offset, this->description, length_description);
      offset += length_description;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      uint32_t length_usage;
      arrToVar(length_usage, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_usage; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_usage-1]=0;
      this->usage = (char *)(inbuffer + offset-1);
      offset += length_usage;
      uint32_t length_description;
      arrToVar(length_description, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_description; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_description-1]=0;
      this->description = (char *)(inbuffer + offset-1);
      offset += length_description;
     return offset;
    }

    const char * getType(){ return "play_motion_builder_msgs/Meta"; };
    const char * getMD5(){ return "3d2fb11fee090a7161bc0fcadb79cc50"; };

  };

}
#endif
